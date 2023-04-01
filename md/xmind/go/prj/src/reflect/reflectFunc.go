package main

import (
    "fmt"
    "reflect"
)

// 普通函数
func add(a, b int) int {

    return a + b
}

func main() {

    // 将函数包装为反射值对象
    funcValue := reflect.ValueOf(add)

    // 构造函数参数, 传入两个整型值
    paramList := []reflect.Value{reflect.ValueOf(10), reflect.ValueOf(20)}

    // 反射调用函数
    retList := funcValue.Call(paramList)

    // 获取第一个返回值, 取整数值
    fmt.Println(retList[0].Int())
}