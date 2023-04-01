# 编码规范 - 编程风格

# 类成员函数声明，需要与定义分开。

* 不要直接将类函数定义写在头文件中，一是暴露具体实现，而是导致头文件内容过大。

备注：模板或内联函数或简单逻辑除外

# 禁止接口有多个返回值，需采用闭包、访问者模式实现

```cpp
void queryPathAndResult(string& path,string& res)
```

# 类的声明格式

```cpp
class Test{
    //公有函数
    public:

    //私有函数
    private:

    //保护成员
    protected:

    //私有成员
    private:

}

```

# 类成员，不超过10个

* Clean Code 角度

# 类方法，不超过30个

* Clean Code 角度

# 不将成员变量，直接作为接口参数

* 不规范

# 宏定义禁止包含复杂判断，以规避复杂度检查

* 避免引入错误

# 非冒号表达式的循环，固定上界保护

```cpp
//正例
for(int i=0;i<maxNum;i++){
    ...
}

// 反例,无限制导致死循环
for(int i=0; ;i++){
    ...
}
```

# list容器禁止使用size方法，如果需要用其它容器替换

* list容器的size方法是遍历得到大小，O(N)复杂度