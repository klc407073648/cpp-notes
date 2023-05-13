
# 快捷键 - vim

[[toc]]

# Vim的几种模式

* 正常模式：可以使用快捷键命令，或按:输入命令行。
* 插入模式：可以输入文本，在正常模式下，按i、a、o等都可以进入插入模式。
* 可视模式：正常模式下按v可以进入可视模式， 在可视模式下，移动光标可以选择文本。按V进入可视行模式， 总是整行整行的选中。ctrl+v进入可视块模式。
* 替换模式：正常模式下，按R进入。

# 光标的移动

```
nG: 到文件第n行
H: 把光标移到屏幕最顶端一行。
M: 把光标移到屏幕中间一行。
L: 把光标移到屏幕最底端一行。
gg: 到文件头部。
G: 到文件尾部。
:set nu 点击回车可显示行号
```

# 翻屏

```
Ctrl + F: 下翻一屏。
Ctrl + B: 上翻一屏。
Ctrl + D: 下翻半屏。
Ctrl + U: 上翻半屏。
Ctrl + E: 向下滚动一行。
Ctrl + Y: 向上滚动一行。
```
# 查找与替换

## 查找

```
/something: 在后面的文本中查找something。
?something: 在前面的文本中查找something。
/pattern/+number: 将光标停在包含pattern的行后面第number行上。
/pattern/-number: 将光标停在包含pattern的行前面第number行上。
n: 向后查找下一个。
N: 向前查找下一个。
```

## 替换

```
:s/old/new - 用new替换当前行第一个old。
:s/old/new/g - 用new替换当前行所有的old。
:n1,n2s/old/new/g - 用new替换文件n1行到n2行所有的old。
:%s/old/new/g - 用new替换文件中所有的old。
:%s/^/xxx/g - 在每一行的行首插入xxx，^表示行首。
:%s/表示行尾。
所有替换命令末尾加上c，每个替换都将需要用户确认。 如：%s/old/new/gc，加上i则忽略大小写(ignore)。
```