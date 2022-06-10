# postman使用

[[toc]]

# 参考资料

* [接口测试之Postman使用全指南](https://blog.csdn.net/zbj18314469395/article/details/106693615)
* [Postman中文文档](https://honye.gitbooks.io/postman/content/launching_postman/sending_the_first_request.html)

> Postman是一个可扩展的API开发和测试协同平台工具，可以快速集成到CI/CD管道中。旨在简化测试和开发中的API工作流。

# Postman优势

* 简单易用 - 要使用Postman，你只需登录自己的账户，只要在电脑上安装了Postman应用程序，就可以方便地随时随地访问文件。
* 使用集合 - Postman允许用户为他们的API调用创建集合。每个集合可以创建子文件夹和多个请求。这有助于组织测试结构。
* 多人协作 - 可以导入或导出集合和环境，从而方便共享文件。直接使用链接还可以用于共享集合。
* 创建环境 - 创建多个环境有助于减少测试重复(DEV/QA/STG/UAT/PROD)，因为可以为不同的环境使用相同的集合。这是参数化发生的地方，将在后续介绍。
* 创建测试 - 测试检查点(如验证HTTP响应状态是否成功)可以添加到每个API调用中，这有助于确保测试覆盖率。
* 自动化测试 - 通过使用集合Runner或Newman，可以在多个迭代中运行测试，节省了重复测试的时间。
* 调试 - Postman控制台有助于检查已检索到的数据，从而易于调试测试。
* 持续集成——通过其支持持续集成的能力，可以维护开发实践。

# 功能模块介绍

1. New，在这里创建新的请求、集合或环境；还可以创建更高级的文档、Mock Server 和 Monitor以及API。
2. Import，这用于导入集合或环境。有一些选项，例如从文件，文件夹导入，链接或粘贴原始文本。
3. Runner，可以通过Collection Runner执行自动化测试。后续介绍。
4. Open New，打开一个新的标签，Postman窗口或Runner窗口。
5. My Workspace - 可以单独或以团队的形式创建新的工作区。
6. Invite - 通过邀请团队成员在工作空间上进行协同工作。
7. History - 所有请求的历史记录，这样可以很容易地跟踪你所做的操作。
8. Collections - 通过创建集合来组织你的测试套件。每个集合可能有子文件夹和多个请求。请求或文件夹也可以被复制。
9. Request tab - 这将显示您正在处理的请求的标题。默认对于没有标题的请求会显示“Untitled Request”。
10. HTTP Request - 单击它将显示不同请求的下拉列表，例如 GET, POST, COPY, DELETE, etc. 在测试中，最常用的请求是GET和POST。
11. Request URL - 也称为端点，显示API的URL。.
12. Save - 如果对请求进行了更改，必须单击save，这样新更改才不会丢失或覆盖。
13. Params - 在这里将编写请求所需的参数，比如Key - Value。
14. Authorization - 为了访问api，需要适当的授权。它可以是Username、Password、Token等形式。
15. Headers - 请求头信息
16. Body - 请求体信息，一般在POST中才会使用到
17. Pre-request Script - 请求之前 先执行脚本，使用设置环境的预请求脚本来确保在正确的环境中运行测试。
18. Tests - 这些脚本是在请求期间执行的。进行测试非常重要，因为它设置检查点来验证响应状态是否正常、检索的数据是否符合预期以及其他测试。
19. Settings - 最新版本的有设置，一般用不到。

![base_use](/_images/test/postman/base_use.png)

# 基础使用方法

## GET请求

在Postman的工作区中：
1. 选择HTTP请求方式为GET
2. 在URL区域输入 `www.baidu.com` 链接
3. 点击 “Send”按钮
4. 你将看到下方返回200状态码
5. 返回对应请求的结构。

![get请求](/_images/test/postman/get请求.png)

# 创建测试集合

> 集合在组织测试套件中扮演着重要的角色。它可以被导入和导出，使得在团队之间共享集合变得很容易。

利用 Collection 创建测试集合，以 `用户中心` 接口测试为例:

![usercenter_Collection](/_images/test/postman/usercenter_Collection.png)

Collection Runner 运行集合：

![usercenter_Collection_Runner](/_images/test/postman/usercenter_Collection_Runner.png)

运行结果：

![usercenter_Collection_Runner_Result](/_images/test/postman/usercenter_Collection_Runner_Result.png)

对应的 Collection 和 运行结果 见：

```bash
用户中心接口测试.postman_collection.json
用户中心接口测试.postman_test_run.json
```