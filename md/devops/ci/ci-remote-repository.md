# CI/CD - 远程仓库CI流程

# github action 

github内置的流水线产品名为github action，只需要在github的仓库中创建一个 .github/workflows/<any>.yaml 文件即可，any可以是任何你喜欢的名称。以下是一个基本的步骤：

* 在github仓库中创建 .github/workflows 文件夹。
* 在 .github/workflows 文件夹中创建一个YAML文件，例如ci.yml。
* 在YAML文件中定义一个工作流程（workflow）并指定触发条件，比如当代码被推送或者有pull request时触发。
* 定义工作流程的各个步骤，比如构建、测试、部署等。你可以使用已有的操作（actions）或者自定义操作来执行这些步骤。
* 配置每个步骤的执行条件、环境变量和其他参数。
* 提交YAML文件到你的GitHub仓库

以下是一个简单的示例，展示了如何在GitHub Actions中使用Node.js进行构建和测试：

<<< @/md/devops/ci/src/nodejs.yaml

上述示例中，当代码被推送到main分支或者有pull request时，将会触发这个工作流程。工作流程中的步骤包括检出代码、安装Node.js、安装依赖、运行测试。

# 第三方的CI流水线工具

使用第三方的CI流水线工具，可以考虑使用以下几种方式：

* 集成持续集成服务：许多CI服务商（如Travis CI、CircleCI、Jenkins等）都提供了与GitHub的集成。你可以根据你的需求选择一个合适的CI服务，并按照其文档指引将其与GitHub仓库进行集成。一般来说，你需要在CI服务商的网站上注册账号，授权访问你的GitHub仓库，并根据指引配置你的流水线。

* 使用Docker和自托管的CI/CD工具：你可以使用Docker来打包你的应用和相关环境，并在自己的服务器上搭建CI/CD工具，比如Jenkins、GitLab CI等。你可以在服务器上安装所需的CI工具和相关插件，然后配置你的流水线。在你的流水线中，你可以使用git命令来获取GitHub仓库的代码，并执行构建、测试和部署等操作。

* 自定义脚本和触发器：你可以编写自定义的脚本来实现CI流水线，并使用GitHub提供的Webhooks和Actions来触发流水线。你可以在代码提交、push、pull request等事件发生时，通过Webhooks将事件通知发送到你的服务器上，然后在服务器上执行相应的脚本来进行构建、测试和部署等操作。

以上这些方式都可以实现GitHub与第三方CI流水线工具的集成，你可以根据自己的需求和技术栈选择适合的方式来实现CI流水线。每种方式都有其优点和限制，你可以根据项目的规模、复杂度和团队的需求做出决策。