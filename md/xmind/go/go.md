# go语言学习记录

用于记录go语言学习的内容。

# go命令

```
[root@VM-0-10-centos prj]# export GOPATH=/home/go/my/prj
[root@VM-0-10-centos prj]# cd ./src/cmd/

##测试go build会生成gofmt可执行文件
[root@VM-0-10-centos cmd]# go build gofmt.go 

[root@VM-0-10-centos cmd]# ./gofmt
3

##测试go clean会清除gofmt的可执行文件
[root@VM-0-10-centos cmd]# go clean

##编译并运行，不会生成中间文件
[root@VM-0-10-centos cmd]# go run gogenerate.go 
http://c.biancheng.net/golang/

##格式化go文件
[root@VM-0-10-centos cmd]# gofmt -w -r "a + b -> b + a" gofmt.go 

##编译并安装,在./bin/下生成main可执行文件
[root@VM-0-10-centos prj]# go install 

##在编译前自动化生成某类代码
##//go:generate go run gofmt.go
##//go:generate go version
[root@VM-0-10-centos prj]# go generate ./src/cmd/gogenerate.go 
3
go version go1.16.6 linux/amd64

##go语言测试命令
[root@VM-0-10-centos prj]# go test ./src/gotest/helloworld_test.go 
ok      command-line-arguments  (cached)
[root@VM-0-10-centos prj]# go test -v ./src/gotest/helloworld_test.go 
=== RUN   TestHelloWorld
    helloworld_test.go:6: hello world
--- PASS: TestHelloWorld (0.00s)
PASS
ok      command-line-arguments  (cached)
[root@VM-0-10-centos prj]# go test -v TestA ./src/gotest/select_test.go 
named files must be .go files: TestA
[root@VM-0-10-centos prj]# go test -v -run TestA ./src/gotest/select_test.go 
=== RUN   TestA
    select_test.go:6: A
--- PASS: TestA (0.00s)
=== RUN   TestAK
    select_test.go:9: AK
--- PASS: TestAK (0.00s)
PASS
ok      command-line-arguments  (cached)
```

# 带命令行参数解析的程序

```
echo "defalut:go run flag.go"
go run flag.go

echo "with paras:go run flag.go -name 小明 --age 18 -married=false -d=1h30m"
go run flag.go -name 小明 --age 18 -married=false -d=1h30m a b c d

echo "help:"
go run flag.go  -help
```
