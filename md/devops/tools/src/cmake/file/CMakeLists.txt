# 设置测试文件名称为 test1.txt
SET(TEST_FILE test1.txt)
# 打印当前路径
message(STATUS "current dir: ${CMAKE_CURRENT_SOURCE_DIR}")  

# 写内容到 测试文件
file(WRITE ${TEST_FILE} "Some messages to Write\n" )  

# 将信息内容追加到 测试文件 末尾
file(APPEND ${TEST_FILE} "Another message to write\n")  

# 读取指定内容
# file(READ filename variable [LIMIT numBytes] [OFFSEToffset] [HEX])
# READ 会读取文件的内容并将其存入到变量中。它会在给定的偏移量处开始读取最多numBytes个字节。
# 如果指定了HEX参数，二进制数据将会被转换成十进制表示形式并存储到变量中。
file(READ ${TEST_FILE} CONTENTS LIMIT 4 OFFSET 12)  
message(STATUS "contents of ${TEST_FILE} is: [${CONTENTS}]")  

# 求取文件的MD5码，与该命令 md5sum test1.txt 一致
file(MD5 ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_FILE} HASH_CONTENTS)  
message(STATUS "hash contents of ${TEST_FILE} is: [${HASH_CONTENTS}]")  

# STRINGS 从文件中解析出ASCII字符串列表并存储在变量中。
file(STRINGS ${TEST_FILE} PARSED_STRINGS)  
message(STATUS "strings of ${TEST_FILE} is: [${PARSED_STRINGS}]")  

# 当前路径下的所有文件
file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.*")  
message(STATUS  "files: ${files}")  

# 文件操作
file(MAKE_DIRECTORY dir1 dir2)  
file(RENAME dir2 dir3)  
file(REMOVE dir3)  
file(REMOVE_RECURSE dir3)  

file(RELATIVE_PATH relative_path ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_FILE})  
message(STATUS "relative path : ${relative_path}")  

# TO_CMAKE_PATH会将路径转换成cmake风格的路径表达形式。
file(TO_CMAKE_PATH "$ENV{PATH}" cmake_path)  
message(STATUS "cmake path: ${cmake_path}")  

# 将cmake风格的路径转换为操作系统特定风格的路径表式形式。
file(TO_NATIVE_PATH "/usr/local/sbin;/usr/local/bin" native_path)  
message(STATUS "native path: ${native_path}")  

# DOWNLOAD下载指定URL的资源到指定的文件上
file(DOWNLOAD "http://www.baidu.com" ${CMAKE_CURRENT_SOURCE_DIR}/index.html SHOW_PROGRESS) 

# 拷贝和安装操作
#file(COPY ${TEST_FILE} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dir1)  
file(INSTALL ${TEST_FILE} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dir1)  