# hmdp - 短信登录

# 短信登录

## 导入黑马点评项目

目录结构如下：

```bash
D:\CODE\klc\JavaStudy\project\md\src>ls -al
-rw-r--r-- 1 Jason 197121   68633 Jul 26 21:50 hm-dianping.zip	--- 后端代码
-rw-r--r-- 1 Jason 197121  153224 Jul 26 21:50 hmdp.sql		    --- SQL脚本
-rw-r--r-- 1 Jason 197121 9923790 Jul 26 21:50 nginx-1.18.0.zip --- 前端代码
```

表结构设计：

```
tb_user：用户表
tb_user_info：用户详情表
tb_shop：商户信息表
tb_shop_type：商户类型表
tb_blog：用户日记表（达人探店日记）
tb_follow：用户关注表
tb_voucher：优惠券表
tb_voucher_order：优惠券的订单表
```

整体架构图：

![整体架构图](/_images/project/opensource/hmdp/msglogin/整体架构图.png)

业务流程：

1. 移动端和PC端，发送请求通过nginx服务器，通过负载均衡分流，将请求分发到tomcat集群
2. tomcat服务器向Redis缓存集群请求业务数据，如不命中，将请求转至MySQL集群
3. MySQL集群查到业务数据，返回给tomcat，同时向Redis缓存中写入缓存数据

### 后端项目

后端项目启动， 直接用Idea软件打开 `hm-dianping` 工程，在 `application.yaml` 里配置的**MySQL和Redis实地址信息**

* 启动项目后，在浏览器访问 [http://localhost:8081/shop-type/list](http://localhost:8081/shop-type/list), 如果可以看到查询数据，即运行正常

后台shop_type查询结果.：

![后台shop_type查询结果](/_images/project/opensource/hmdp/msglogin/后台shop_type查询结果.png)

### 前端工程

前端项目启动， 直接在文件路径下，启动 cmd.exe

* 输入 start nginx.exe

![启动前端项目](/_images/project/opensource/hmdp/msglogin/启动前端项目.png)

在浏览器访问 [http://localhost:8080](http://localhost:8080)，前端界面效果：

![前端界面效果](/_images/project/opensource/hmdp/msglogin/前端界面效果.png)

## 基于Session实现登录

基于Seesion实现登录的流程，包含以下三个步骤：

**1. 发送验证码：**

1. 用户在提交手机号后，会校验手机号是否合法，如果不合法，则要求用户重新输入手机号；
2. 如果手机号合法，后台此时生成对应的验证码，同时将验证码进行保存；
2. 最后再通过短信的方式将验证码发送给用户。

**2. 短信验证码登录、注册：**

1. 用户将验证码和手机号进行输入，后台从session中拿到当前验证码，然后与用户输入的验证码进行校验，如果不一致，则无法通过校验；
2. 如果一致，则后台根据手机号查询用户，如果用户不存在，则为用户创建账号信息，保存到数据库；
3. 无论是否存在，都会将用户信息保存到session中，方便后续获得当前登录信息。

**3. 校验登录状态:**

1. 用户在请求时候，会从cookie中携带者JsessionId到后台，后台通过JsessionId从session中拿到用户信息；
2. 如果没有session信息，则进行拦截，如果有session信息，则将用户信息保存到threadLocal中，并且放行。

![基于Session实现登录流程](/_images/project/opensource/hmdp/msglogin/基于Session实现登录流程.png)

### 发送短信验证码

**页面流程**

![发送短信验证码](/_images/project/opensource/hmdp/msglogin/发送短信验证码.png)

### 短信验证码登录

![短信验证码登录](/_images/project/opensource/hmdp/msglogin/短信验证码登录.png)

### 登录验证

![登录验证](/_images/project/opensource/hmdp/msglogin/登录验证.png)

### 具体代码

根据上文发送验证码的流程图，编写实现具体代码。

* 发送验证码

```java
    @Override
    public Result sendCode(String phone, HttpSession session) {
        // 1.校验手机号
        if (RegexUtils.isPhoneInvalid(phone)) {
            // 2.如果不符合，返回错误信息
            return Result.fail("手机号格式错误！");
        }
        // 3.符合，生成验证码
        String code = RandomUtil.randomNumbers(6);

        // 4.保存验证码到 session
        session.setAttribute("code",code);
        // 5.发送验证码
        log.debug("发送短信验证码成功，验证码：{}", code);
        // 返回ok
        return Result.ok();
    }
```

* 登录

```java
    @Override
    public Result login(LoginFormDTO loginForm, HttpSession session) {
        // 1.校验手机号
        String phone = loginForm.getPhone();
        if (RegexUtils.isPhoneInvalid(phone)) {
            // 2.如果不符合，返回错误信息
            return Result.fail("手机号格式错误！");
        }
        // 3.校验验证码
        Object cacheCode = session.getAttribute("code");
        String code = loginForm.getCode();
        if(cacheCode == null || !cacheCode.toString().equals(code)){
             //3.不一致，报错
            return Result.fail("验证码错误");
        }
        //一致，根据手机号查询用户
        User user = query().eq("phone", phone).one();

        //5.判断用户是否存在
        if(user == null){
            //不存在，则创建
            user =  createUserWithPhone(phone);
        }
        //7.保存用户信息到session中
        session.setAttribute("user",user);

        return Result.ok();
    }
```

### 登录拦截

**tomcat的运行原理**

![tomcat的运行原理](/_images/project/opensource/hmdp/msglogin/tomcat的运行原理.png)

1. 当用户发起请求时，**会访问tomcat注册的端口，任何程序想要运行，都需要有一个线程对当前端口号进行监听**，tomcat也不例外；
2. 当tomcat监听线程知道用户想要和tomcat进行连接时，就会**由监听线程创建socket连接**，socket都是成对出现的；
3. 用户通过socket互相传递数据，当tomcat端的socket接受到数据后，此时监听线程会从tomcat的**工作线程池**中取出一个线程执行用户请求；
4. 当服务部署到tomcat后，**线程会找到用户想要访问的工程，然后用这个线程转发到工程中的controller，service，dao中**，并且访问对应的DB；
5. 在用户执行完请求后，再统一返回，再找到tomcat端的socket，再将数据写回到用户端的socket，完成请求和响应。

通过以上流程，我们可以得知 每个用户其实对应都是去找tomcat线程池中的一个线程来完成工作的， 使用完成后再进行回收，既然每个请求都是独立的，所以在每个用户去访问我们的工程时，可以使用**threadlocal来做到线程隔离，每个线程操作自己的一份数据**。

**温馨小贴士：关于threadlocal**

如果小伙伴们看过threadLocal的源码，你会发现在threadLocal中，无论是他的put方法和他的get方法， 都是先从获得当前用户的线程，然后从线程中取出线程的成员变量map，只要线程不一样，map就不一样，所以可以通过这种方式来做到线程隔离。

**登录验证功能**

![登录验证功能](/_images/project/opensource/hmdp/msglogin/登录验证功能.png)

拦截器代码

```Java
public class LoginInterceptor implements HandlerInterceptor {

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
       //1.获取session
        HttpSession session = request.getSession();
        //2.获取session中的用户
        Object user = session.getAttribute("user");
        //3.判断用户是否存在
        if(user == null){
              //4.不存在，拦截，返回401状态码
              response.setStatus(401);
              return false;
        }
        //5.存在，保存用户信息到Threadlocal
        UserHolder.saveUser((User)user);
        //6.放行
        return true;
    }
}
```

让拦截器生效

```java
@Configuration
public class MvcConfig implements WebMvcConfigurer {

    @Resource
    private StringRedisTemplate stringRedisTemplate;

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        // 登录拦截器
        registry.addInterceptor(new LoginInterceptor())
                .excludePathPatterns(
                        "/shop/**",
                        "/voucher/**",
                        "/shop-type/**",
                        "/upload/**",
                        "/blog/hot",
                        "/user/code",
                        "/user/login"
                ).order(1);
        // token刷新的拦截器
        registry.addInterceptor(new RefreshTokenInterceptor(stringRedisTemplate)).addPathPatterns("/**").order(0);
    }
}
```

### 隐藏用户敏感信息

通过浏览器观察到此时用户的全部信息都在，这样极为不靠谱，所以我们应当在返回用户信息之前，将用户的敏感信息进行隐藏脱密处理，采用的核心思路就是书写一个UserDto对象，这个UserDto对象就没有敏感信息了。在返回前，我们将有用户敏感信息的User对象转化成没有敏感信息的UserDto对象，那么就能够避免这个问题了。

**在登录方法处修改**

```java
//7.保存用户信息到session中
session.setAttribute("user", BeanUtils.copyProperties(user,UserDTO.class));
```

**在拦截器处：**

```java
//5.存在，保存用户信息到Threadlocal
UserHolder.saveUser((UserDTO) user);
```

**在UserHolder处：将user对象换成UserDTO**

```java
public class UserHolder {
    private static final ThreadLocal<UserDTO> tl = new ThreadLocal<>();

    public static void saveUser(UserDTO user){
        tl.set(user);
    }

    public static UserDTO getUser(){
        return tl.get();
    }

    public static void removeUser(){
        tl.remove();
    }
}
```

## 集群的session共享问题

**核心思路分析：**

每个tomcat中都有一份属于自己的session,假设用户第一次访问第一台tomcat，并且把自己的信息存放到第一台服务器的session中，但是第二次这个用户访问到了第二台tomcat，那么在第二台服务器上，肯定没有第一台服务器存放的session，所以此时 整个登录拦截功能就会出现问题。

——我们能如何解决这个问题呢？早期的方案是session拷贝，就是说虽然每个tomcat上都有不同的session，但是每当任意一台服务器的session修改时，都会同步给其他的Tomcat服务器的session，这样的话，就可以实现session的共享了。

但是这种方案具有两个大问题

1. 每台服务器中都有完整的一份session数据，服务器压力过大。

2. session拷贝数据时，可能会出现延迟

**session共享问题：多台Tomcat并不共享session存储空间，当请求切换到不同tomcat服务时导致数据丢失的问题**。

session的替代方案应该满足：

* 数据共享

* 内存存储

* key、value结构

考虑采用redis替代session的方案，因为redis数据本身就是共享的，就可以避免session共享的问题了。

![Redis替代方案](/_images/project/opensource/hmdp/msglogin/Redis替代方案.png)

## 基于Redis实现共享session登录

### 设计key的结构

利用redis来存储数据，到底使用哪种结构呢？

——由于存入的数据比较简单，我们可以考虑使用String，或者是使用哈希，如下图，如果使用String，它的value会多占用一点空间；如果使用哈希，则它的value中只会存储他数据本身，如果不是特别在意内存，其实使用String也可以。

* 保存登录的用户信息，可以使用String结构，以JSON字符串来保存，比较直观：

 ![String结构](/_images/project/opensource/hmdp/msglogin/String结构.png)

* Hash结构可以将对象中的每个字段独立存储，可以针对单个字段做CRUD，并且内存占用更少：

 ![String结构](/_images/project/opensource/hmdp/msglogin/Hash结构.png)

### 设计key的具体细节

可以使用String结构，就是一个简单的 (key，value) 键值对的方式，但是关于key的处理，session他是每个用户都有自己的session，但是redis的key是共享的，咱们就不能使用code了

在设计这个key的时候，我们之前讲过需要满足两点

1. key要具有唯一性

2. key要方便携带

如果我们采用phone：手机号这个的数据来存储当然是可以的，但是如果把这样的敏感数据存储到redis中并且从页面中带过来毕竟不太合适，所以我们在后台生成一个随机串token，然后让前端带来这个token就能完成我们的整体逻辑了。

### 整体访问流程

具体步骤

1. 当注册完成后，用户去登录会去校验用户提交的手机号和验证码，是否一致；
2. 如果一致，则根据手机号查询用户信息，不存在则新建；
3. 最后将用户数据保存到redis，并且生成token作为redis的key；
4. 当校验用户是否登录时，会去携带着token进行访问，从redis中取出token对应的value，判断是否存在这个数据；
5. 如果没有则拦截，如果存在则将其保存到threadLocal中，并且放行。

![基于Redis实现共享session登录](/_images/project/opensource/hmdp/msglogin/基于Redis实现共享session登录_整体访问流程.png)

###  具体代码

**UserServiceImpl代码**

```java
@Override
public Result login(LoginFormDTO loginForm, HttpSession session) {
    // 1.校验手机号
    String phone = loginForm.getPhone();
    if (RegexUtils.isPhoneInvalid(phone)) {
        // 2.如果不符合，返回错误信息
        return Result.fail("手机号格式错误！");
    }
    // 3.从redis获取验证码并校验
    String cacheCode = stringRedisTemplate.opsForValue().get(LOGIN_CODE_KEY + phone);
    String code = loginForm.getCode();
    if (cacheCode == null || !cacheCode.equals(code)) {
        // 不一致，报错
        return Result.fail("验证码错误");
    }

    // 4.一致，根据手机号查询用户 select * from tb_user where phone = ?
    User user = query().eq("phone", phone).one();

    // 5.判断用户是否存在
    if (user == null) {
        // 6.不存在，创建新用户并保存
        user = createUserWithPhone(phone);
    }

    // 7.保存用户信息到 redis中
    // 7.1.随机生成token，作为登录令牌
    String token = UUID.randomUUID().toString(true);
    // 7.2.将User对象转为HashMap存储
    UserDTO userDTO = BeanUtil.copyProperties(user, UserDTO.class);
    Map<String, Object> userMap = BeanUtil.beanToMap(userDTO, new HashMap<>(),
            CopyOptions.create()
                    .setIgnoreNullValue(true)
                    .setFieldValueEditor((fieldName, fieldValue) -> fieldValue.toString()));
    // 7.3.存储
    String tokenKey = LOGIN_USER_KEY + token;
    stringRedisTemplate.opsForHash().putAll(tokenKey, userMap);
    // 7.4.设置token有效期
    stringRedisTemplate.expire(tokenKey, LOGIN_USER_TTL, TimeUnit.MINUTES);

    // 8.返回token
    return Result.ok(token);
}
```

###  解决状态登录刷新问题

#### 初始方案思路总结

在这个方案中，他确实可以使用对应路径的拦截，同时刷新登录token令牌的存活时间，但是现在这个拦截器他只是拦截需要被拦截的路径，假设当前用户访问了一些不需要拦截的路径，那么这个拦截器就不会生效，所以此时令牌刷新的动作实际上就不会执行。

**所以这个方案他是存在问题的**。

![登录拦截器](/_images/project/opensource/hmdp/msglogin/登录拦截器.png)

#### 优化方案

既然之前的拦截器无法对不需要拦截的路径生效。

—— 那么我们可以添加一个拦截器：

* 第一个拦截器：负责拦截所有的路径，且获取用户信息保存到ThreadLocal，同时刷新token有效时长；
* 第二个拦截器：只需要判断拦截器只需要完成ThreadLocal中用户的查询，不存在，则拦截，存在，则放行。

![登录拦截器的优化](/_images/project/opensource/hmdp/msglogin/登录拦截器的优化.png)

#### 代码 

**RefreshTokenInterceptor**

```java
public class RefreshTokenInterceptor implements HandlerInterceptor {

    private StringRedisTemplate stringRedisTemplate;

    public RefreshTokenInterceptor(StringRedisTemplate stringRedisTemplate) {
        this.stringRedisTemplate = stringRedisTemplate;
    }

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        // 1.获取请求头中的token
        String token = request.getHeader("authorization");
        if (StrUtil.isBlank(token)) {
            return true;
        }
        // 2.基于TOKEN获取redis中的用户
        String key  = LOGIN_USER_KEY + token;
        Map<Object, Object> userMap = stringRedisTemplate.opsForHash().entries(key);
        // 3.判断用户是否存在
        if (userMap.isEmpty()) {
            return true;
        }
        // 5.将查询到的hash数据转为UserDTO
        UserDTO userDTO = BeanUtil.fillBeanWithMap(userMap, new UserDTO(), false);
        // 6.存在，保存用户信息到 ThreadLocal
        UserHolder.saveUser(userDTO);
        // 7.刷新token有效期
        stringRedisTemplate.expire(key, LOGIN_USER_TTL, TimeUnit.MINUTES);
        // 8.放行
        return true;
    }

    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
        // 移除用户
        UserHolder.removeUser();
    }
}
	
```

**LoginInterceptor**

```java
public class LoginInterceptor implements HandlerInterceptor {

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        // 1.判断是否需要拦截（ThreadLocal中是否有用户）
        if (UserHolder.getUser() == null) {
            // 没有，需要拦截，设置状态码
            response.setStatus(401);
            // 拦截
            return false;
        }
        // 有用户，则放行
        return true;
    }
}
```