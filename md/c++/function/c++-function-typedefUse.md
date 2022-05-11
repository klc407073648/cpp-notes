# typedef 语句的使用

## 使用typedef定义数组类型

### 一维数组类型的定义格式

typedef <元素类型关键字><数组类型名>[<常量表达式>];
例如: 
1. typedef int intArr[10];
2. typedef std::string stringArr[20];
3. typedef int array[N];

### 二维数组类型的定义格式

typedef <元素类型关键字><数组类型名>[<常量表达式1>][<常量表达式2>];
例如: 
1. typedef int matrix[5][5];
2. typedef char nameTable[10][NN];
3. typedef double DD[M+1][N+1];

### 对已有类型定义别名

利用typedef语句不仅能够定义数组类型，而且能够对已有类型定义出另一个类型名，以此作为原类型的一个别名。如: 
1. typedef int inData;
2. typedef char chData;
3. typedef char* chPointer;

例子:
[main.cpp](./src/typedefUse/main.cpp)

执行结果:
```
[root@localhost typedef]# ./main
0th mIntArr is 1
1th mIntArr is 2
0th mStrArr is hello
1th mStrArr is world
————————————————————————————————————————
mMat[0][0]:1
mMat[0][1]:2
mMat[0][2]:3
mMat[0][3]:4
mMat[0][4]:5
mMat[1][0]:6
mMat[1][1]:7
mMat[1][2]:8
mMat[1][3]:9
mMat[1][4]:10
mMat[2][0]:11
mMat[2][1]:12
mMat[2][2]:13
mNameTable[0][0]:a
mNameTable[0][1]:b
mNameTable[0][2]:c
mNameTable[1][0]:d
mNameTable[1][1]:e
mNameTable[1][2]:f
mNameTable[2][0]:g
mNameTable[2][1]:h
mNameTable[2][2]:
————————————————————————————————————————
m_int is 100
m_char is Z

```