# C++函数 - 闭包

[[toc]]


```cpp
void OnRecvSessionGracefullyShutdownNotify(WORD32 index)
{
    handleConnByIndex(index, [&](shared_ptr<http2_connection> conn)
    {
        conn->on_recv_session_gracefully_shutdown_notify();
    });
}

void handleConnByIndex(WORD32 index, std::function<void> vistor)
{
    if(cur_thread())
    {
        vistor(conn);
    }
}
```

```cpp
#include <iostream>
#include <functional>

using namespace std;
        
void handleIndex(int index, std::function<void()> vistor)
{
    if(index == 1)
    {
        vistor();
    }
}
void OnHandleIndex(int index)
{
    handleIndex(index, [&]()
    {
        cout<< "deal" <<endl;
        return;
    });
}

int main()
{
 
  OnHandleIndex(0);
  OnHandleIndex(1);
  return 0;
}
```