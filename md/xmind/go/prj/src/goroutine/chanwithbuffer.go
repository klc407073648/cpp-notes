package main

import "fmt"

func main() {

	// 创建一个3个元素缓冲大小的整型通道
	ch := make(chan int, 3)

	// 查看当前通道的大小
	fmt.Println(len(ch))

	// 发送3个整型元素到通道
	ch <- 1
	ch <- 2
	ch <- 3

	// 查看当前通道的大小
	fmt.Println(len(ch))
}
