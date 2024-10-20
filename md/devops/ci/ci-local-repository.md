# CI/CD - 本地仓库CI流程

# 参考资料

* [手写 git hooks 脚本（pre-commit、commit-msg）](https://zhuanlan.zhihu.com/p/391221822)

CI/CD(Continuous integration;Continuous Deployment, 持续集成与持续部署)。这个过程连接了从代码编写完毕到交付测试环节的整个链路。如果能够将CI/CD做好的
话，研发人员只需要专注于业务实现即可(实际上不可能，开发很多时候得自己搭建环境测试)。

通过verifyCI 保证代码质量，代码提交会经历编译——运行测试用例——跑覆盖率、圈复杂度——各类自定义工具检测(中英文、模型包校验)等，从流程上减少出错的可能性。将这个过程自动化，大大提高了研发人员的开发效率。

# 代码规范工具

* 代码格式化(VS code插件)和代码静态检测工具(cppcheck)

# 打造属于自己的本地CI流程

在git运行中的每个阶段，都暴露的生命周期的调用方法，通过增加相关的hooks文件我们可以非常简单的插入想要运行的shell命令。

git会自动扫描仓库git配置下hooks目录的文件，并去执行它。其中比较常用的有：pre-commit、commit-msg、pre-push 等钩子（hooks）。我们可以在 pre-commit 触发时进行代码格式验证，在 commit-msg 触发时对 commit 消息和提交用户进行验证，在 pre-push 触发时进行单元测试、e2e 测试等操作。

用于编写 git hooks 的脚本语言是没有限制的，可以用 nodejs、shell、python、ruby等脚本语言，非常的灵活方便。以 shell 语言为例演示一下如何编写 pre-commit 和 commit-msg 脚本。另外要注意的是，在执行这些脚本时，如果以非零的值退出程序，将会中断 git 的提交/推送流程。所以在 hooks 脚本中验证消息/代码不通过时，就可以用非零值进行退出，中断 git 流程。

## pre-commit

在 pre-commit 钩子中要做的事情特别简单，只对要提交的代码格式进行检查，因此脚本代码比较少：

```bash
#!/bin/sh
npm run lint

# 获取上面脚本的退出码
exitCode="$?"
exit $exitCode
```

在项目中已经配置好了相关的 eslint 配置以及 npm 脚本，因此在 pre-commit 中执行相关的 lint 命令就可以了，并且判断一下是否正常退出。

```
// 在 package.json 文件中已配置好 lint 命令
"scripts": {
    "lint": "eslint --ext .js src/"
 },
```

## commit-msg

在 commit-msg hooks 中，我们需要对 commit 消息和用户进行校验。

<<< @/md/devops/ci/src/commit-msg.sh

在 commit-msg 钩子触发时，对应的脚本会接收到一个参数，这个参数就是 commit 消息，通过 cat $1 获取，并赋值给 commit_msg 变量。