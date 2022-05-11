# Linux的shell命令使用技巧

## 参考资料

* Shell中的${}，##和%%的使用
* 查找指令


## Shell中的${}，##和%%的使用

```
假设我们定义了一个变量为：
file=/dir1/dir2/dir3/my.file.txt

可以用${ }分别替换得到不同的值：
${file#*/}：删掉第一个/ 及其左边的字符串：dir1/dir2/dir3/my.file.txt
${file##*/}：删掉最后一个/  及其左边的字符串：my.file.txt
${file#*.}：删掉第一个.  及其左边的字符串：file.txt
${file##*.}：删掉最后一个.  及其左边的字符串：txt
${file%/*}：删掉最后一个 /  及其右边的字符串：/dir1/dir2/dir3
${file%%/*}：删掉第一个/  及其右边的字符串：(空值)
${file%.*}：删掉最后一个 .  及其右边的字符串：/dir1/dir2/dir3/my.file
${file%%.*}：删掉第一个 .   及其右边的字符串：/dir1/dir2/dir3/my

记忆的方法为：
# 是去掉左边（键盘上#在 $ 的左边）
% 是去掉右边（键盘上% 在$ 的右边）
单一符号是最小匹配；两个符号是最大匹配

${file:0:5}：提取最左边的5 个字节：/dir1
${file:5:5}：提取第5 个字节右边的连续5个字节：/dir2

也可以对变量值里的字符串作替换：
${file/dir/path}：将第一个dir 替换为path：/path1/dir2/dir3/my.file.txt
${file//dir/path}：将全部dir 替换为path：/path1/path2/path3/my.file.txt

利用${ } 还可针对不同的变数状态赋值(没设定、空值、非空值)： 
${file-my.file.txt} ：假如$file 没有设定，则使用my.file.txt 作传回值。(空值及非空值时不作处理) 
${file:-my.file.txt} ：假如$file 没有设定或为空值，则使用my.file.txt 作传回值。(非空值时不作处理)
${file+my.file.txt} ：假如$file 设为空值或非空值，均使用my.file.txt 作传回值。(没设定时不作处理)
${file:+my.file.txt} ：若$file 为非空值，则使用my.file.txt 作传回值。(没设定及空值时不作处理)
${file=my.file.txt} ：若$file 没设定，则使用my.file.txt 作传回值，同时将$file 赋值为my.file.txt 。(空值及非空值时不作处理)
${file:=my.file.txt} ：若$file 没设定或为空值，则使用my.file.txt 作传回值，同时将$file 赋值为my.file.txt 。(非空值时不作处理)
${file?my.file.txt} ：若$file 没设定，则将my.file.txt 输出至STDERR。(空值及非空值时不作处理)


${file:?my.file.txt} ：若$file 没设定或为空值，则将my.file.txt 输出至STDERR。(非空值时不作处理)

${#var} 可计算出变量值的长度：

${#file} 可得到27 ，因为/dir1/dir2/dir3/my.file.txt 是27个字节
```

## 查找指令

```
find / -type -f -name '*abc.xml' | xargs grep 'Hello'
grep -rn "hello" ./

```

## Linux中运行有时间限制的命令

```
语法格式：
timeout [OPTION] DURATION COMMAND [ARG]...

在下面的示例中，timeout命令运行一分钟，如果命令没有结束，将在10秒后终止命令：

[root@localhost ~]# timeout -k 10s 1m sh test.sh
```

## make命令加速
```
#让make允许4个编译命令同时执行
make -j4  
```


## C++输出cout（bool类型）
```
C++输出cout（bool类型）
cout<<boolalpha<<y<<endl;
```


