# 常用开发库 - CppUnit

# 参考文章

* [HowToUseCppUnit](https://github.com/niceSimon7/HowToUseCppUnit)
* [CppUnit快速入门](https://blog.csdn.net/wyyy2088511/article/details/80107131)
* [cppunit使用详解](https://www.cnblogs.com/zhoug2020/p/4515729.html)

# 概述

> CppUnit 是个基于 LGPL 的开源项目，最初版本移植自 JUnit，是一个非常优秀的开源测试框架。CppUnit 和 JUnit 一样主要思想来源于极限编程(XProgramming)。主要功能就是对**单元测试**进行管理，并可进行自动化测试。

> 单元测试是开发者编写的一小段代码，用于检验被测代码的一个很小的、很明确的功能是否正确。

## 核心内容

CppUnit核心内容主要包括六个方面，

1. 测试对象(Test，TestFixture，TestSuite,...)：用于开发测试用例，以及对测试用例进行组织管理。
    * TestCase：测试用例。通过继承它来实现测试用例。
    * TestFixture：测试固件。用来建立测试基准或构建测试用例的先决条件。
    * TestSuite：测试套具。用来整合测试用例。

2. 测试结果(TestResult)：处理测试用例执行结果。TestResult与下面的TestListener采用的是观察者模式。

3. 测试结果监听者(TestListener)：TestListener作为TestResult的观察者，担任实际的结果处理角色。

4. 结果输出(Outputter)：将结果进行输出，可以制定不同的输出格式。

5. 对象工厂(TestFactory)：用于创建测试对象，对测试用例进行自动化管理。

6. 测试执行体(TestRunner)：用于运行一个测试。

以上各模块的主要类继承结构如下：

```
         Test              TestFixture      TestResult          TestListener     
        _______|_________            |                                    |          
        |               |            |                           TestSuccessListener
    TestComposite   TestLeaf         |                                    |          
        |               |____________|                           TestResultCollector          
    TestSuit                  |
                           TestCase                     
                              |
                      TestCaller<Fixture>
                      
                        Outputter                                    TestFactory                    TestRunner
        ____________________|_________________                            |
        |                   |                |                   TestFactoryRegistry
    CompilerOutputter  TextOutputter    XmlOutputter                      |
                                                             TestSuiteFactory<TestCaseType>
```

## 编译

```
cd /home/tools/cppunit/
tar  -zxf cppunit-1.12.1.tar.gz
cd ./cppunit-1.12.1/
./configure
make
make install
```

# examples下的demo使用

路径: build_lib\examples\examples\3partlib\cppunit

```
[root@5d4b980baaa2 build]# cd /home/stibel/examples/deploy/3partlib/
[root@5d4b980baaa2 3partlib]# ./cppunit/SimpleTest
.F.


!!!FAILURES!!!
Test Results:
Run:  2   Failures: 1   Errors: 0


1) test: testString (F) line: 13 /home/stibel/examples/examples/3partlib/cppunit/source/SimpleTest.cpp
equality assertion failed
- Expected: hello
- Actual  : world


<RETURN> to continue
```
