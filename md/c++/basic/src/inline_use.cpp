// 声明1（加 inline，建议使用）
inline int funName(int first, int second,...);

// 声明2（不加 inline）
int funName(int first, int second,...);

// 定义
inline int funName(int first, int second,...) {/****/};

// 类内定义，隐式内联
class A {
    int doA() { return 0; }         // 隐式内联
}

// 类外定义，需要显式内联
class A {
    int doA();
}
inline int A::doA() { return 0; }   // 需要显式内联