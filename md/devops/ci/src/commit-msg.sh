#!/bin/sh

# 用 `` 可以将命令的输出结果赋值给变量
# 获取当前提交的 commit msg
commit_msg=`cat $1`

# 获取用户 email
email=`git config user.email`
msg_re="^(feat|fix|docs|style|refactor|perf|test|workflow|build|ci|chore|release|workflow)(\(.+\))?: .{1,100}"

if [[ ! $commit_msg =~ $msg_re ]]
then
    echo "\n不合法的 commit 消息提交格式，请使用正确的格式：\
    \nfeat: add comments\
    \nfix: handle events on blur (close #28)\
    \n详情请查看 git commit 提交规范：https://github.com/woai3c/Front-end-articles/blob/master/git%20commit%20style.md"

    # 异常退出
    exit 1
fi