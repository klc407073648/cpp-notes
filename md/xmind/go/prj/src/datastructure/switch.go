package main

import "fmt"

func test1() {
    var s = "hello"
    switch {
    case s == "hello":
        fmt.Println("hello")
    case s != "world":
        fmt.Println("world")
    }
}

func test2() {
    var a int = 15
    switch {
    case a>0 && a<10:
        fmt.Printf("a is Number,value is %d\n",a)
    case a>10 && a<20:
        fmt.Printf("a is Number,value is %d\n",a)
    default:
        fmt.Printf("default\n")
    }
}

func test3() {
    var a = "hello"
    switch a {
    case "hello":
        fmt.Println(1)
    case "world":
        fmt.Println(2)
    default:
        fmt.Println(0)
    }
}

func main() {
    test1()
    test2()
    test3()
}