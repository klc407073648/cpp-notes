# 测试工具 -RobotFramework使用

# 参考资料

[**RobotFramework创建目录和实现界面操作**](https://zhuanlan.zhihu.com/p/199263251)

# 基本使用

## 目录创建

### 关系梳理

　　在Robotframework中完成之后，在使用之前需要进行对整个目录进行规划，在一定程度上可以做到“事半功倍”，尽量在后续脚本的编写过程中减少目录的调整。在RobotFramework中主要分为**project、directory、TestSuite、TestCase**四个中类型。robtfreamework是以project作为单位进行管理的。在一般的编写过程中，个人更喜欢将整个平台或者项目project开始进行编写。其中Test Suite 分为Dir Test Suite和File Test Suite两种类型，而在Dir Test Suite下面可以再建File Test Suite，但是在File Test Suite下面只能Testcase，主要关系如下图所示：

 ![img](https://pica.zhimg.com/v2-214c5a5b7aafb635c140b7ff33c70a3e_720w.jpg?source=3af55fa1)

### 例子说明

　　以教学管理管理平台为例：

　　1.在创建目录的时候可以以“教学管理平台”创建一个“project”类型的根目录；

　　2.在整个教学管理平台会涉及到教师管理、学生管理、课程管理、成绩管理等功能模块，而这些功能模块创建的时候可以以“Dir Test Suite”或者“Directory”的形式创建；

　　3.在功能模块下往往存在新增、编辑、查询、删除等子模块，而这些模块则可以以“File Test Suite”的形式进行目录创建；

　　4.在功能模块创建成功之后，在功能模块下创建用例，用例的格式则以“Test Case”的形式进行创建；

 ![img](https://pica.zhimg.com/v2-94cdbecce1b057a68b3c01de0e0b1317_720w.jpg?source=3af55fa1)

　　根据上述目录的形式进行创建，在视觉上很直观的可以看出模块的组成结构，保证在用例设计时，不会导致主要功能模块的缺失，最重要的是可以保证各个模块之间用例的独立性，确保在运行的时候不会相互影响，确保在运行时做到“谁写谁维护”，保证在运行的时候可以第一时间对运行失败的脚本进行问题定位以及排查，在功能模块上做到“最低”准则，即以最小功能的名称来创建“Test Suite”。

## 界面操作

　　整个Robotframework脚本编写，主要以Ride来这支撑，主要包括编辑、运行以及预览等模块，在日常操作中最主要用到的是编辑以及运行两个模块，本次文章中主要分享编辑以及运行两个模块。

### 编辑

#### Settings 

　　编辑区域主要包含Settings、import、Variable、MetaData三个子模块。

　　一般settings是隐藏的，点击settings按钮，则会显示。

**·**Documentation：文档，每一项都有。可以给当前的对象加入文档说明（一般情况下写脚本变更记录、包括变更的操作（add、update、delete）、修改时间、修改内容、修改人信息，确保后续可以正常查询变更记录）；

　　-Suite Setup： 指的是测试套件启动的时候就执行某个关键字。(例如在执行的时候可以将测试套件中公用的内容放到这个地方，比如平台登录、连接数据库)

　　-Suite Teardown： 指的是测试套件结束的时候就执行某个关键字（例如在测试套件执行结束之后，平台退出以及断开数据连接）

　　-Test Setup： 指的就是案例启动的时候执行某个关键字。

　　-Test Teardown： 指的就是案例结束的时候执行某个关键字。

　　-Test Template：测试模版，这是可以指定某个关键字为这个测试套件下所有TestCase的模版，这样所有的TestCase就只需要设置这个关键字的传入参数即可。

**·**Test Timeout：设置每一个测试案例的超时时间，只要超过这个时间就会失败，并停止案例运行。这是防止某些情况导致案例一直卡住不动，也不停止也不失败。

**·**Force Tags：在文件型Suite这里还可以继续给子元素增加Force Tags，但是不能删除父元素设置的tags。

**·**Default Tags：默认标记，其实和Force Tags没什么区别的。

![img](https://pic2.zhimg.com/v2-4021e088315d13c12f37f49a258638cc_720w.jpg?source=3af55fa1)

　**2.1.2 Import**

　　**2.1.2.1 Library**

　　说完Settings部分，接下来就说下Import、Variable、Metadata的部分。在import部分最常用的是Library以及Recourse两个部分；

　　其中Library指的是Python中的第三方库或者由个人封装的库；

　　在导入Library的时候需要写对库的名称，否则会导入失败，如下图展示的“红色”字体，导入成功情况的情况下，会以“黑色”字体展示：

![img](https://pic2.zhimg.com/v2-c5f5c2707f40a70699af49593f77675f_720w.jpg?source=3af55fa1)![img](https://pic2.zhimg.com/80/v2-c5f5c2707f40a70699af49593f77675f_720w.jpg?source=3af55fa1)

　　在导入失败的情况下，可以在ride界面查看对应导入失败日志，具体的路径为“Tool->View RIDE log ”，如下图所示

![img](https://pic1.zhimg.com/v2-39eb7b608254f04991e7a3d8e8e6cc8d_720w.jpg?source=3af55fa1)

**2.1.2.2 Resource**

　　导入Resource在日常测试过程中最常用的是导入用户自定义关键字，具体的操作步骤是在某个目录下右击“New Resource”创建Resource，选择的类型为TXT类型：

![img](https://pic2.zhimg.com/v2-86ec9b0534a2bb9bffeb8c7b31766705_720w.jpg?source=3af55fa1)

　　创建完Resource目录之后，需要进行自定义用户关键字的创建，选择已创建Resource的目录右击“New User Keyword”创建自定义用户关键字，如下图，创建的是一个登陆的自定义关键字，在创建完成之后，则可以进行引用，避免重复脚本的编写。

　　创建成功之后的自定义关键字如下图所示：

![img](https://pic3.zhimg.com/v2-677d8817d9332e8aaba530e3e6cc520b_720w.jpg?source=3af55fa1)

　　在创建成功之后，则可以在某个测试套件进行引用：

![img](https://pic2.zhimg.com/v2-3cb4ab4c8d471de9bb0ada2efc36ba1c_720w.jpg?source=3af55fa1)

　**2.1.2.3 Variables**

　　Variables主要包含Scalar、List、Dict三种数据类型，在这里添加的是变量主要为公共变量，主要为平台地址、平台端口、数据信息等公用的数据；这样做目的是可以确保脚本复用、确保在修改脚本时成本最小化。

　　例如教学管理平台从A服务器迁移至B服务器，则可以使用脚本进行冒烟测试，在调用脚本的时候，只需修改该部分公用的变量即可，尽量减少脚本的改动，提高脚本的复用率。

![img](https://pic1.zhimg.com/v2-f7ce88b614e2a66ed92ea34bda54c251_720w.jpg?source=3af55fa1)

**2.2 运行**

　　相比编辑模块的功能，运行模块的功能相对比较简单，点击上方Run菜单，切换至运行界面，

**·**运行用例：若是需要进行用例执行，只需勾选需要执行的用例，点击“Start”按钮即可，需要注意的是，如果未勾选任何用例，点击“Start”按钮，执行的是整个Project；

![img](https://pic1.zhimg.com/v2-61f296c92c369ffd86c738a7b9228eeb_720w.jpg?source=3af55fa1)

**·**查看报告：在用例执行完成之后，可以点击Report或者log查看用例执行情况，在查看报告的时候，可以很清晰看见用例执行的情况，包含执行总数、失败数、成功数；

**·**定位原因：若是用例存在执行失败的情况，在报告中可以很清晰定位到具体的某一行脚本的失败原因。

![img](https://pic3.zhimg.com/v2-e85272852df37cc7d9b9558f3187e355_720w.jpg?source=3af55fa1)

**·**选择执行用例：在用例执行的情况下只需要进行筛选部分用例即可，如全量测试、冒烟测试等；RobotFramework中支持用例的筛选，支持只执行该标签或者跳过该标签的，如下图在用例设计的时候，打的标签是“冒烟测试”：

![img](https://pic2.zhimg.com/v2-a26505aff4a68a1748d6832858c4b04e_720w.jpg?source=3af55fa1)

　　如下图的测试用例，在编写的时候，打的标签是“冒烟测试”，若只需要执行冒烟测试用例的话，只需要在测试套件勾选“Only run test with these tags ”：

![img](https://pic2.zhimg.com/v2-c067155719e45ea785cb192b7041269f_720w.jpg?source=3af55fa1)![img](https://pic2.zhimg.com/80/v2-c067155719e45ea785cb192b7041269f_720w.jpg?source=3af55fa1)

　　若不需要执行冒烟的话，只需在测试套件勾选“Skip tests with these tags ”即可。

![img](https://pic2.zhimg.com/v2-92b1d3487761862fdc8f0f49710f2924_720w.jpg?source=3af55fa1)![img](https://pic2.zhimg.com/80/v2-92b1d3487761862fdc8f0f49710f2924_720w.jpg?source=3af55fa1)

**2.3 常用快捷键**http://robotframework.org/Selenium2Library/Selenium2Library.html)

