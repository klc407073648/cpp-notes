# muduo - Protobuf网络传输和Protobuf编解码器与消息分发器

[[toc]]

# 一种自动反射消息类型的 Google Protobuf 网络传输方案

Google Protocol Buffers (Protobuf) 是一款非常优秀的库，它定义了一种紧凑的可扩展二进制消息格式，特别适合网络数据传输。它为多种语言提供 binding，大大方便了分布式程序的开发，让系统不再局限于用某一种语言来编写。

## 根据 type name 反射自动创建 Message 对象

Protobuf 本身具有很强的反射(reflection)功能，可以根据 type name 创建具体类型的 Message 对象。Protobuf  class diagram 如下：

![protobuf_classdiagram](/_images/book-note/muduo/protobuf_classdiagram.JPG)

大家在使用的时候，通常关心和使用的是图的左半部分：MessageLite、Message、Generated Message Types (Person, AddressBook) 等，而较少注意到图的右半部分：Descriptor, DescriptorPool, MessageFactory。

上图中，其关键作用的是 **Descriptor class**，每个具体 Message Type 对应一个 Descriptor 对象。尽管我们没有直接调用它的函数，但是Descriptor在“根据 type name 创建具体类型的 Message 对象”中扮演了重要的角色，起了桥梁作用。上图的红色箭头描述了根据 type name 创建具体 Message 对象的过程，后文会详细介绍。

Protobuf Message class 采用了 prototype pattern，Message class 定义了 New() 虚函数，用以返回本对象的一份新实体，类型与本对象的真实类型相同。也就是说，拿到 Message* 指针，不用知道它的具体类型，就能创建和它类型一样的具体 Message Type 的对象。

每个具体 Message Type 都有一个 default instance，可以通过 ConcreteMessage::default_instance() 获得，也可以**通过 MessageFactory::GetPrototype(const Descriptor*) 来获得**。所以，现在问题转变为 1. 如何拿到 MessageFactory；2. 如何拿到 Descriptor*。

当然，ConcreteMessage::descriptor() 返回了我们想要的 Descriptor*，但是，在不知道 ConcreteMessage 的时候，如何调用它的静态成员函数呢？我们的英雄是 DescriptorPool，**它可以根据 type name 查到 Descriptor***，只要找到合适的 DescriptorPool，再调用 DescriptorPool::FindMessageTypeByName(const string& type_name) 即可。

## 根据 type name 自动创建 Message 的关键代码

1. 用 DescriptorPool::generated_pool() 找到一个 DescriptorPool 对象，它包含了程序编译的时候所链接的全部 protobuf Message types。
2. 用 DescriptorPool::FindMessageTypeByName() 根据 type name 查找 Descriptor。
3. 再用 MessageFactory::generated_factory() 找到 MessageFactory 对象，它能创建程序编译的时候所链接的全部 protobuf Message types。
4. 然后，用 MessageFactory::GetPrototype() 找到具体 Message Type 的 default instance。
5. 最后，用 prototype->New() 创建对象。

```cpp
//codec.cc中函数
google::protobuf::Message* ProtobufCodec::createMessage(const std::string& typeName)
{
  google::protobuf::Message* message = NULL;
  const google::protobuf::Descriptor* descriptor =
    google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
  if (descriptor)
  {
    const google::protobuf::Message* prototype =
      google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
    if (prototype)
    {
      message = prototype->New();
    }
  }
  return message;
}
```

调用方式：

```cpp
google::protobuf::Message* newQuery = createMessage("muduo.Query");
assert(newQuery != NULL);
assert(typeid(*newQuery) == typeid(muduo::Query::default_instance()));
cout << "createMessage(/"muduo.Query/") = " << newQuery << endl;
```

createMessage() 返回的是动态创建的对象的指针，调用方有责任释放它，不然就会内存泄露。在 muduo 里，我用 shared_ptr 来自动管理 Message 对象的生命期。拿到Message *后，如何调用这个具体消息类型的处理函数，就需要依赖于消息分发器（dispatcher）。

# 在 muduo 中实现 protobuf 编解码器与消息分发器

Protobuf 是经过深思熟虑的消息打包方案，**它的默认序列化格式没有包含消息的长度与类型**，自然有其道理。如果 protobuf 无条件地把长度和类型放到序列化的字节串中，只会浪费网络带宽和存储。用户在使用时，根据应用场景确认是否加入长度和类型到序列化字节中。

## 什么是编解码器 codec?

Codec 是 encoder 和 decoder 的缩写，这是一个到软硬件都在使用的术语，这里我借指“把网络数据和业务消息之间互相转换”的代码。

在最简单的网络编程中，没有消息 message 只有字节流数据，这时候是用不到 codec 的。比如我们前面讲过的 echo server，它只需要把收到的数据原封不动地发送回去，它不必关心消息的边界（也没有“消息”的概念），收多少就发多少，这种情况下它干脆直接使用 muduo::net::Buffer，取到数据再交给 TcpConnection 发送回去，见下图。

![codec-1](/_images/book-note/muduo/codec-1.JPG)

non-trivial 的网络服务程序**通常会以消息为单位来通信，每条消息有明确的长度与界限**。程序每次收到一个完整的消息的时候才开始处理，发送的时候也是把一个完整的消息交给网络库。比如我们前面讲过的 asio chat 服务，它的一条聊天记录就是一条消息，我们设计了一个简单的消息格式，即在聊天记录前面加上 4 字节的 length header，LengthHeaderCodec 代码及解说不详述。

codec 的基本功能之一是做 TCP 分包：确定每条消息的长度，为消息划分界限。在 non-blocking 网络编程中，codec 几乎是必不可少的。如果只收到了半条消息，那么不会触发消息回调，数据会停留在 Buffer 里（数据已经读到 Buffer 中了），等待收到一个完整的消息再通知处理函数。既然这个任务太常见，我们干脆做一个 utility class，避免服务端和客户端程序都要自己处理分包，这就有了 LengthHeaderCodec。这个 codec 的使用有点奇怪，不需要继承，它也没有基类，只要把它当成普通 data member 来用，把 TcpConnection 的数据喂给它，然后向它注册 onXXXMessage() 回调，代码见 asio chat 示例。muduo 里的 codec 都是这样的风格，通过 boost::function 粘合到一起。

codec 是一层间接性，它位于 TcpConnection 和 ChatServer 之间，拦截处理收到的数据，在收到完整的消息之后再调用 CharServer 对应的处理函数，注意 CharServer::onStringMessage() 的参数是 std::string，不再是 muduo::net::Buffer，也就是说 LengthHeaderCodec 把 Buffer 解码成了 string。另外，在发送消息的时候，ChatServer 通过 LengthHeaderCodec::send() 来发送 string，LengthHeaderCodec 负责把它编码成 Buffer。这正是“编解码器”名字的由来。消息流程如图所示：

![codec-2](/_images/book-note/muduo/codec-2.JPG)

Protobuf codec 与此非常类似，**只不过消息类型从 std::string 变成了 protobuf::Message**。对于只接收处理 Query 消息的 QueryServer 来说，用 ProtobufCodec 非常方便，收到 protobuf::Message 之后 down cast 成 Query 来用就行。

![codec-3](/_images/book-note/muduo/codec-3.JPG)

如果要接收处理不止一种消息，ProtobufCodec 恐怕还不能单独完成工作，请继续阅读下文。

# Protobuf传输格式

在muduo库中设计了一个简单的打包格式，包含Protobuf data和其对应的长度和类型信息，消息的末尾还有一个check sum。格式如下图所示，图中方块的宽度是32-bit。

![protobuf传输格式](/_images/book-note/muduo/protobuf传输格式.JPG)

将该格式用C代码描述：

```cpp
 struct ProtobufTransportFormat __attribute__ ((__packed__))
 {
   int32_t  len;
   int32_t  nameLen;
   char     typeName[nameLen];
   char     protobufData[len-nameLen-8];
   int32_t  checkSum; // adler32 of nameLen, typeName and protobufData
 }
```

例子，用这个格式打包一个muduo.Query对象的结果如下：

![protobuf传输格式举例](/_images/book-note/muduo/protobuf传输格式举例.JPG)

以下作者在设计这个传输格式时的考虑：

* signed int。消息中的长度字段只使用了 signed 32-bit int，而没有使用 unsigned int，这是为了移植性，因为 Java 语言没有 unsigned 类型。另外 Protobuf 一般用于打包小于 1M 的数据，unsigned int 也没用。

* check sum。虽然 TCP 是可靠传输协议，虽然 Ethernet 有 CRC-32 校验，但是网络传输必须要考虑数据损坏的情况，对于关键的网络应用，check sum 是必不可少的。对于 protobuf 这种紧凑的二进制格式而言，肉眼看不出数据有没有问题，需要用 check sum。

* adler32 算法。我没有选用常见的 CRC-32，而是选用 adler32，因为它计算量小、速度比较快，强度和 CRC-32差不多。另外，zlib 和 java.unit.zip 都直接支持这个算法，不用我们自己实现。

* type name 以 '/0' 结束。这是为了方便 troubleshooting，比如通过 tcpdump 抓下来的包可以用肉眼很容易看出 type name，而不用根据 nameLen 去一个个数字节。同时，为了方便接收方处理，加入了 nameLen，节省 strlen()，空间换时间。

* 没有版本号。Protobuf Message 的一个突出优点是用 optional fields 来避免协议的版本号，让通信双方的程序能各自升级，便于系统演化。

# 实现 ProtobufCodec

编码算法很直截了当，按照前文定义的消息格式一路打包下来，最后更新一下首部的长度即可。函数ProtobufCodec::fillEmptyBuffer实现如下：

```cpp
void ProtobufCodec::fillEmptyBuffer(Buffer* buf, const google::protobuf::Message& message)
{
  // buf->retrieveAll();
  assert(buf->readableBytes() == 0);

  const std::string& typeName = message.GetTypeName();
  int32_t nameLen = static_cast<int32_t>(typeName.size()+1);
  buf->appendInt32(nameLen);
  buf->append(typeName.c_str(), nameLen);

  // code copied from MessageLite::SerializeToArray() and MessageLite::SerializePartialToArray().
  GOOGLE_DCHECK(message.IsInitialized()) << InitializationErrorMessage("serialize", message);

  #if GOOGLE_PROTOBUF_VERSION > 3009002
    int byte_size = google::protobuf::internal::ToIntSize(message.ByteSizeLong());
  #else
    int byte_size = message.ByteSize();
  #endif
  buf->ensureWritableBytes(byte_size);

  uint8_t* start = reinterpret_cast<uint8_t*>(buf->beginWrite());
  uint8_t* end = message.SerializeWithCachedSizesToArray(start);
  if (end - start != byte_size)
  {
    #if GOOGLE_PROTOBUF_VERSION > 3009002
      ByteSizeConsistencyError(byte_size, google::protobuf::internal::ToIntSize(message.ByteSizeLong()), static_cast<int>(end - start));
    #else
      ByteSizeConsistencyError(byte_size, message.ByteSize(), static_cast<int>(end - start));
    #endif
  }
  buf->hasWritten(byte_size);

  int32_t checkSum = static_cast<int32_t>(
      ::adler32(1,
                reinterpret_cast<const Bytef*>(buf->peek()),
                static_cast<int>(buf->readableBytes())));
  buf->appendInt32(checkSum);
  assert(buf->readableBytes() == sizeof nameLen + nameLen + byte_size + sizeof checkSum);
  int32_t len = sockets::hostToNetwork32(static_cast<int32_t>(buf->readableBytes()));
  buf->prepend(&len, sizeof len);
}
```

解码算法ProtobufCodec::onMessage函数有几个要点:

* protobuf::Message是new出来的对象，它的生命期在muduo中采用shared_ptr<Message>来自动管理对象生命期

* 出错如何处理？比方说长度超出范围、check sum不正确、message type name不能识别、message parse出错等等。ProtobufCodec定义了ErrorCallback，用户可以注册这个回调。如果不注册，默认的处理是断开连接，让客户重连重试，codec的单元测试里模拟了各种出错情况。

```cpp
void ProtobufCodec::onMessage(const TcpConnectionPtr& conn,
                              Buffer* buf,
                              Timestamp receiveTime)
{
  while (buf->readableBytes() >= kMinMessageLen + kHeaderLen)
  {
    const int32_t len = buf->peekInt32();
    if (len > kMaxMessageLen || len < kMinMessageLen)
    {
      errorCallback_(conn, buf, receiveTime, kInvalidLength);
      break;
    }
    else if (buf->readableBytes() >= implicit_cast<size_t>(len + kHeaderLen))
    {
      ErrorCode errorCode = kNoError;
      MessagePtr message = parse(buf->peek()+kHeaderLen, len, &errorCode);
      //先检查校验码，再根据type name创建相应的prototype，再调用MessageLite::ParseFormArray，解析二进制格式的数据。
      if (errorCode == kNoError && message)
      {
        messageCallback_(conn, message, receiveTime);
        buf->retrieve(kHeaderLen+len);
      }
      else
      {
        errorCallback_(conn, buf, receiveTime, errorCode);
        break;
      }
    }
    else
    {
      break;
    }
  }
}
```

ProtobufCodec 在实际使用中有明显的不足：它只负责把 muduo::net::Buffer 转换为具体类型的 protobuf::Message，应用程序拿到 Message 之后还有再根据其具体类型做一次分发。我们可以考虑做一个简单通用的分发器 dispatcher，以简化客户代码。

# 消息分发器 dispatcher 有什么用？

前面提到，在使用 TCP 长连接，且在一个连接上传递不止一种 protobuf 消息的情况下，客户代码需要对收到的消息按类型做分发。比方说，收到 Logon 消息就交给 QueryServer::onLogon() 去处理，收到 Query 消息就交给 QueryServer::onQuery() 去处理。这个消息分派机制可以做得稍微有点通用性，让所有 muduo+protobuf 程序收益，而且不增加复杂性。

换句话说，又是一层间接性，ProtobufCodec 拦截了 TcpConnection 的数据，把它转换为 Message，ProtobufDispatcher 拦截了 ProtobufCodec 的 callback，按消息具体类型把它分派给多个 callbacks。处理过程如下所示：

![ProtobufDispatcer处理逻辑](/_images/book-note/muduo/ProtobufDispatcer处理逻辑.JPG)

## ProtobufDispatcher的两种实现

要完成消息分发，其实就是对消息做type-switch，这样做的扩展性不太好，但Protobuf Message的Descriptor没有留下定制点（比如暴露一个boost::any成员），只能这么做了。

ProtobufDispatcherLite的结构很简单，它有一个map<const Descriptor*, ProtobufMessageCallback>成员，客户代码可以以Descriptor*为键注册回调（每个具体消息类型都有一个全局的Descriptor对象，其地址是不变的）。在收到Protobuf Message之后，在map中找到相应的ProtobufMessageCallback，然后调用它。如果找不到，就调用defaultCallback。

不过，这个设计有小小的缺陷，因为ProtobufMessageCallback的定义为：

```cpp
 typedef std::function<void (const muduo::net::TcpConnectionPtr&,
                                const MessagePtr&,
                                muduo::Timestamp)> ProtobufMessageCallback;
```

这样就限制了客户代码只能接受基类Message，那么客户代码在处理消息时，需要自己做down cast，如下图所示：

![ProtobufDispatcer-1](/_images/book-note/muduo/ProtobufDispatcer-1.JPG)

如果说我们希望down cast交给dispatcher处理，客户代码拿到的就已经是具体类型，其接口如下图所示：

![ProtobufDispatcer-1.5](/_images/book-note/muduo/ProtobufDispatcer-1.5.JPG)

也就是说，我们需要如何将ProtobufDispatcher与多个未知的消息类型合作？可以将多态与模板结合，利用templated derived class来实现。

![ProtobufDispatcer-2](/_images/book-note/muduo/ProtobufDispatcer-2.JPG)

ProtobufDispatcher 有一个模板成员函数，可以接受注册任意消息类型 T 的回调，然后它创建一个模板化的派生类 CallbackT，这样消息的类新信息就保存在了 CallbackT 中，做 down casting 就简单了。比方说，我们有两个具体消息类型 Query 和 Answer 继承自Message，注册回调如下：

```cpp
dispatcher_.registerMessageCallback(
    boost::bind(&QueryServer::onQuery, this, _1, _2, _3));
dispatcher_.registerMessageCallback(
    boost::bind(&QueryServer::onAnswer, this, _1, _2, _3));
```

这样会具现化 (instantiation) 出两个 CallbackT 实体，如下：

![ProtobufDispatcer-3](/_images/book-note/muduo/ProtobufDispatcer-3.JPG)

## ProtobufDispatcherLite和ProtobufDispatcher代码比较

ProtobufDispatcherLite主要代码：

```cpp
typedef std::shared_ptr<google::protobuf::Message> MessagePtr;

class ProtobufDispatcherLite : muduo::noncopyable
{
 public:
  typedef std::function<void (const muduo::net::TcpConnectionPtr&,
                                const MessagePtr&,
                                muduo::Timestamp)> ProtobufMessageCallback;

  explicit ProtobufDispatcherLite(const ProtobufMessageCallback& defaultCb)
    : defaultCallback_(defaultCb)
  {
  }

  void onProtobufMessage(const muduo::net::TcpConnectionPtr& conn,
                         const MessagePtr& message,
                         muduo::Timestamp receiveTime) const
  {
    CallbackMap::const_iterator it = callbacks_.find(message->GetDescriptor());
    if (it != callbacks_.end())
    {
      it->second(conn, message, receiveTime);
    }
    else
    {
      defaultCallback_(conn, message, receiveTime);
    }
  }

  void registerMessageCallback(const google::protobuf::Descriptor* desc,
                               const ProtobufMessageCallback& callback)
  {
    callbacks_[desc] = callback;
  }

 private:
  
  typedef std::map<const google::protobuf::Descriptor*, ProtobufMessageCallback> CallbackMap;
  CallbackMap callbacks_;
  ProtobufMessageCallback defaultCallback_;
};
```

ProtobufDispatcher主要代码：

```cpp
typedef std::shared_ptr<google::protobuf::Message> MessagePtr;

class Callback : muduo::noncopyable
{
 public:
  virtual ~Callback() = default;
  virtual void onMessage(const muduo::net::TcpConnectionPtr&,
                         const MessagePtr& message,
                         muduo::Timestamp) const = 0;
};

template <typename T>
class CallbackT : public Callback
{
  static_assert(std::is_base_of<google::protobuf::Message, T>::value,
                "T must be derived from gpb::Message.");
 public:
  typedef std::function<void (const muduo::net::TcpConnectionPtr&,
                                const std::shared_ptr<T>& message,
                                muduo::Timestamp)> ProtobufMessageTCallback;

  CallbackT(const ProtobufMessageTCallback& callback)
    : callback_(callback)
  {
  }

  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 const MessagePtr& message,
                 muduo::Timestamp receiveTime) const override
  {
    std::shared_ptr<T> concrete = muduo::down_pointer_cast<T>(message);
    assert(concrete != NULL);
    callback_(conn, concrete, receiveTime);
  }

 private:
  ProtobufMessageTCallback callback_;
};

class ProtobufDispatcher
{
 public:
  typedef std::function<void (const muduo::net::TcpConnectionPtr&,
                                const MessagePtr& message,
                                muduo::Timestamp)> ProtobufMessageCallback;

  explicit ProtobufDispatcher(const ProtobufMessageCallback& defaultCb)
    : defaultCallback_(defaultCb)
  {
  }

  void onProtobufMessage(const muduo::net::TcpConnectionPtr& conn,
                         const MessagePtr& message,
                         muduo::Timestamp receiveTime) const
  {
    CallbackMap::const_iterator it = callbacks_.find(message->GetDescriptor());
    if (it != callbacks_.end())
    {
      it->second->onMessage(conn, message, receiveTime);
    }
    else
    {
      defaultCallback_(conn, message, receiveTime);
    }
  }

  template<typename T>
  void registerMessageCallback(const typename CallbackT<T>::ProtobufMessageTCallback& callback)
  {
    std::shared_ptr<CallbackT<T> > pd(new CallbackT<T>(callback));
    callbacks_[T::descriptor()] = pd;
  }

 private:
  typedef std::map<const google::protobuf::Descriptor*, std::shared_ptr<Callback> > CallbackMap;

  CallbackMap callbacks_;
  ProtobufMessageCallback defaultCallback_;
};
```