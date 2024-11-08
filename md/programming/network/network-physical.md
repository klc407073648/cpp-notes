# 计算机网络 - 物理层

[[toc]]

## 参考资料

* [从零开始的计网学习——物理层](https://blog.csdn.net/Nimrod__/article/details/113271631)
* [学习视频](https://www.bilibili.com/video/BV1c4411d7jb?p=29&spm_id_from=pageDriver)

## 物理层概述

- 物理层是计算机网络的第一层，是整个计算机网络系统的基础，为数据传输提供可靠的环境。

- 物理层要解决的基本问题**：如何在各种传输媒体上传输比特0和1的问题**。进而给数据链路层提供透明传输比特流的服务。

- 物理层**为数据链路层屏蔽了各种传输媒体的差异，使数据链路层只需要考虑如何完成本层的协议和服务，而不必考虑网络具体的传输媒体是什么**。


**物理层协议的主要任务**

定义物理层的四个特性：

 ![1](/_images/programming/network/physical/物理层协议的主要任务.png)

由于传输媒体种类众多（双绞线、光纤等），物理连接方式也很多（点对点连接、广播连接等），因此物理协议有很多种，但是每一种都需要包括以上四个特性。

## 物理层下面的传输媒体

**导引型传输媒体**

在导引型传输媒体中，电磁波被导引沿着固体传播媒体传播。

常见的导引型传播媒体：

- 同轴电缆
- 双绞线
- 光纤
- 电力线

**非导引型传输媒体**

非导引型的传播媒体是自由空间。。

常见的非导引型传播媒体：

![2](/_images/programming/network/physical/电磁波的频谱.png)

电磁波频率过大对人体有害，因此一般使用介于无线电波到红外的频率来进行信息传播。

- 无线电波
  - 无线电波用于**国际广播、海事和航空通讯**等。
  - 无线电波中的低频和中频端主要以地面波形式传播。高频和甚高频主要用电离层的反射传播。
- 微波
  - 微波用于**无线电话、无线网络**、雷达、人造卫星接受等。在数据通信中占有重要地位。
  - 微波在空间中主要以直线传播。
  - 传统的微波通信主要有**地面微波接力通信和卫星通信**。
  - 其传播距离一般只有50公里左右。
- 红外线
  - 利用红外线传输数据，例如电视遥控等。
  - 红外通信属于点对点无线传输。
  - 不能越障，传输距离短，传输速率低。
- 可见光
  - LIFI，可以实现使用可见光通信，但是目前还在实验室阶段。

## 传输方式

串行传输和并行传输：

- 串行传输
  - 数据通过一条线路传输，一个一个比特依次传送，因此只需要一条线路。
  - 数据在进行远距离传输的时候用的是串行传输，不是并行传输。
- 并行传输
  - 数据通过多条线路传输。并行传输的优点是速度为串行传输的n倍。
  - 缺点是成本高。计算机内部数据的传输一般使用并行传输。

同步传输和异步传输：

- 同步传输：
  ![3](/_images/programming/network/physical/同步传输.png)
  - 数据以稳定的比特流形式传输，字节之间没有间隔。
  - 接收端在每个比特信号的中间时刻进行检测，以判别接收到的是比特0还是比特1。
  - 由于不同设备的时钟周期存在差异，不能做到完全相同，在传输大量数据的过程中判别时刻的累计误差会导致接收端对比特信号的判别位置错位。因此需要采取方法使收发双方的始终保持同步。
  - 有两种同步方法：
    - 外同步：在收发双方之间添加一条单独的时钟信号线。发送端在发送数据信号的同时，另外发送一条时钟信号，接收端按照同步信号的节奏来接受数据。
    - 内同步：发送端将时钟同步信号编码到发送数据中一起传输(例如曼切斯特编码)。**传统以太网采用的就是曼彻斯特编码的内同步方式**。
- 异步传输：
  ![4](/_images/programming/network/physical/异步传输.png)
  - 使用异步传输方式时，以子节为独立的传输单位，子节之间的间隔时间不固定的（因此成为异步传输）。
  - 接收端仅在每个字节的**起始处**对子节内的比特实现同步。
  - 为此，通常要在每个子节的前后分别加上起始位和结束位。
  - **异步指的是子节之间异步**。
  - 字节之间的时间间隔不固定。
  - 但是，**字节中的每个比特依旧要同步，各个比特的持续时间要相同**。


**单工、半双工、全双通信**

- 单工通信：通信双方只有一个数据传输方向。
- 半双工通信：通信双方有两个数据传输方向，但是不可以同时通信。
- 全双工通信：通信双方有两个数据传输方向，可以进行同时通信。

## 编码与调制

![5](/_images/programming/network/physical/编码与调制.png)

- 编码：编码就是在**不改变信号性质的情况下仅对数字基带信号的波形进行变换**。编码后产生的信号认为数字信号。可以在信道中传输。
  - 有两种情况：
    - 数字信号转换为另一种数字信号，在数字信道中传输。例如，以太网使用曼彻斯特编码、4B/5B、8B/10B等编码。
    - 模拟信号转换为数字信号，在数字信道中传输。例如，对音频信号进行编码的脉码调制PCM。

- 调制: 将各种数字基带信号转换成适于信道传输的数字调制信号。
  - 把**数据基带信号的频率范围，搬移到较高的频段，并转换为模拟信号**，称为调制。调制后产生模拟信号，在模拟信道中传输。
  - 有两种情况：
    - 数字信号转换为模拟信号，在模拟信道中传输。例如WiFi，采用补码键控CCK/直接序列扩频DSSS/正交频分复用OFDM等调制方式。
    - 模拟信号转换为另一种模拟信号，在模拟信道中传输。例如，语音数据加载到模拟的载波信号中传输。频分复用FDM技术，充分利用带宽资源。
- 解调: 在接收端将收到的数字频带信号还原成数字基带信号。

常用编码：

码元：构成信号的一段波形。

- 不归零编码。
- 归零编码。
- 曼彻斯特编码。
- 差分曼彻斯特编码。

基本调制方法：

![6](/_images/programming/network/physical/基本调制方法.png)


**调幅**：对基带信号的波幅进行调整，例如将上图的1信号波幅进行改变，在接收方读取时有载波输出为1.

**调频**：对基带信号频率进行调整，例如将0信号调制为频率f1，1信号调制为频率f2。

**调相**：对基带信号相位进行调制，例如将0信号的初相位调整为0度，1信号的初相位调整为180度。

但是在以上基本调制方法中，1个码元只能包含1个比特信息。

## 信道的极限容量

概述：

![7](/_images/programming/network/physical/信道传输.png)

在实际传输过程中由于通信质量的问题会导致传输信号被干扰，导致信号波形出现了码元之间的清晰界限，这种现象叫码元串扰。

![8](/_images/programming/network/physical/失真因素.png)

因为以上情况，防止信道数据过大导致码间串扰，因此做出了信号极限容量的预测。其中最著名的就是奈氏准则。

**奈氏准则**

- 奈氏准则：在假定的理想条件下，为了避免码间串扰，码元传输速率时有上限的。

![9](/_images/programming/network/physical/奈氏准则.png)

由于奈氏准则是一种理想环境下的情况，在实际中极限容量要明显小于该值。

**香农公式**

- 香农公式：带宽受限且有高斯白噪声干扰的信道的极限信息传输速率。

![10](/_images/programming/network/physical/香农公式.png)

由于在实际信道中，信号还有收到其他的一些损伤，例如个脉冲干扰等，因此实际信道能达成的信息速率要比计算出来的极限速率还要小。

综合来看：

**在信道带宽一定的情况下，根据奈氏准则和香农公式，想要提高信息的传输速率必须采用多元制或者更好的调制方法，以及努力提高信道中的信噪比。**