package main
import (
    "fmt"
    "time"
)
func main() {
    ch := make(chan int)
    quit := make(chan bool)
    //新开一个协程
    go func() {
        for {
            select {
            case num := <-ch:
                fmt.Println("num = ", num)
            case <-time.After(3 * time.Second):
                fmt.Println("超时")
                quit <- true
            }
        }
    }() //别忘了()
    for i := 0; i < 5; i++ {
        ch <- i
        time.Sleep(time.Second)
    }
    <-quit
    fmt.Println("程序结束")
}