package main

import "container/list"
import "fmt"

func ListPrint(index int , l *list.List) {
    fmt.Printf("%dth list content is:\n",index)
    for i := l.Front(); i != nil; i = i.Next() {
        fmt.Println(i.Value)
    }
}

func main() {
    l := list.New()//var list1 list.List
    // 尾部添加
    l.PushBack("canon")
    ListPrint(1,l)
    // 头部添加
    l.PushFront(67)
    ListPrint(2,l)
    // 尾部添加后保存元素句柄
    element := l.PushBack("fist")
    ListPrint(3,l)
    // 在fist之后添加high
    l.InsertAfter("high", element)
    ListPrint(4,l)
    // 在fist之前添加noon
    l.InsertBefore("noon", element)
    ListPrint(5,l)
    // 使用
    l.Remove(element)
    ListPrint(6,l)
    
    //遍历列表
    fmt.Printf("7th list content is:\n")
    for i := l.Front(); i != nil; i = i.Next() {
        fmt.Println(i.Value)
    }
}