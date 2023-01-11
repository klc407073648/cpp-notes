# conan-c++包管理工具
# C++包管理工具vcpkg

docker run -it -d --name consul_install docker.io/klc407073648/centos_build_lib:v3.0 /bin/bash

# conan软件安装
python3 -m pip install --upgrade pip
python3 -m pip install --upgrade setuptools
pip3 install conan

##conan所需sqlite3
yum install -y sqlite*
cd /home/tools/Python-3.7.10
./configure --prefix=/home/tools/python3/ --with-ssl
make && make install

# conan软件安装
mkdir -p /home/ppconsul
cd /home/ppconsul
git clone git@github.com:oliora/ppconsul.git //docker cp /home/ppconsul.tar.gz consul_install:/home/ppconsul
tar -zxvf ppconsul.tar.gz


#更新conan的默认安装路径
mkdir ppconsul_depend
old_path="path = ./data"
new_path="path = /home/ppconsul/ppconsul/ppconsul_depend"
echo "old_path:$old_path"
echo "new_path:$new_path"
sed -i 's#'''"$old_path"'''#'''"$new_path"'''#g' /root/.conan/conan.conf

## 
/home/tools/python3/bin/conan install .
mkdir ppconsul_output
mkdir build
cd build
cmake ..
make -j4 DESTDIR=../ppconsul_output/ install

mkdir -p /home/ppconsul/ppconsul_output/data
cp -rf  /root/.conan/data/* /home/ppconsul/ppconsul_output/data

编译：
register.cpp 

export LD_LIBRARY_PATH=/home/ppconsul/ppconsul_output/usr/local/lib64
export LIBRARY_PATH=/home/ppconsul/ppconsul_output/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/lib/
ldconfig

CMakeLists.txt

```
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CONSUL_PRJ)
SET(CMAKE_CXX_COMPILER "g++")

SET(STIBEL_CONSUL_INCLUDE      /home/ppconsul/ppconsul_output/usr/local/include/)
SET(STIBEL_BOOST_INCLUDE       /home/ppconsul/ppconsul_output/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/include)

SET(CONSUL_DIR  /home/ppconsul/ppconsul_output/usr/local/lib64)
SET(BOOST_DIR   /home/ppconsul/ppconsul_output/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/include/lib)

set(CMAKE_INCLUDE_PATH    ${STIBEL_CONSUL_INCLUDE} ${STIBEL_BOOST_INCLUDE})
set(CMAKE_LIBRARY_PATH    ${CONSUL_DIR} ${BOOST_DIR})

INCLUDE_DIRECTORIES( ${STIBEL_CONSUL_INCLUDE} ${STIBEL_BOOST_INCLUDE} )
LINK_DIRECTORIES(${CONSUL_DIR} ${BOOST_DIR})

SET(LIB_BOOST       
    boost_contract
	boost_coroutine
	boost_fiber_numa
	boost_fiber
	boost_context
	boost_graph
	boost_iostreams
	boost_json
	boost_locale
	boost_log_setup
	boost_log
	boost_math_c99
	boost_math_c99f
	boost_math_c99l
	boost_math_tr1
	boost_math_tr1f
	boost_math_tr1l
	boost_nowide
	boost_program_options
	boost_random
	boost_regex
	boost_stacktrace_addr2line
	boost_stacktrace_backtrace
	boost_stacktrace_basic
	boost_stacktrace_noop
	boost_timer
	boost_type_erasure
	boost_thread
	boost_chrono
	boost_container
	boost_date_time
	boost_unit_test_framework
	boost_prg_exec_monitor
	boost_test_exec_monitor
	boost_exception
	boost_wave
	boost_filesystem
	boost_atomic
	boost_wserialization
	boost_serialization
)

add_executable(${PROJECT_NAME} /home/ppconsul/ppconsul_output/register.cpp)
target_link_libraries(${PROJECT_NAME} ppconsul ${LIB_BOOST})

```

g++ -o register register.cpp  -I/home/ppconsul_output/usr/local/include/ -I/home/root/.conan/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/include/ -L/home/ppconsul_output/usr/local/lib64/ -L/home/root/.conan/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/lib -lppconsul
   35  ./register
   36  ldd register
   37  find /home/ -name  libppconsul.so.0.2
   38  cd /home/ppconsul_output/usr/local/lib64/
   39  ls -al
   40  export LD_LIBRARY_PATH=/home/usr/local/lib64:/home/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/lib
   

g++ -o register register.cpp  -I/home/usr/local/include/ -I/home/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/include/ -L/home/ppconsul_output/usr/local/lib64/ -L/home/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/lib -lppconsul

Cmakelists.txt
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CONSUL_PRJ) 
SET(CMAKE_CXX_COMPILER "g++")  
MESSAGE (STATUS "CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/usr/local/cmake)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/usr/local/cmake)
include(ppconsulConfig)
find_package(ppconsul)
add_executable(${PROJECT_NAME} /home/register.cpp)
target_link_libraries(${PROJECT_NAME} ppconsul)






[root@d9bcc671b5c3 ppconsul-master]# history
    1  pip install conan -i http://mirrors.aliyun.com/pypi/simple/
    2  pip3 install conan -i http://mirrors.aliyun.com/pypi/simple/
    3  python3 -m pip install --upgrade pip
    4  pip3 install conan -i http://mirrors.aliyun.com/pypi/simple/
    5  pip3 install conan
    6  python3 -m pip install --upgrade setuptools
    7  pip3 install conan
    8  find /home/tools/ -name "conan"
    9  cd /home/
   10  unzip ppconsul-master.zip
   11  cd ./ppconsul-master
   12  /home/tools/python3/bin/conan install .
   13  pip3 install pysqlite3
   14  /home/tools/python3/bin/conan install .
   15  yum install sqlite*
   16  cd /home/tools/Python-3.7.10
   17  ./configure --prefix=/home/tools/python3/ --with-ssl
   18  make
   19  make insta;;
   20  make install
   21  /home/tools/python3/bin/conan install .
   22  cd -
   23  /home/tools/python3/bin/conan install .
   24  mkdir workspace
   25  cd workspace
   26  cmake ..
   27  yum install git
   28  cmake ..
   29  rm -rf ./*
   30  cmake ..
   31  cd ..
   32  ls -al
   33  cd ..
   34  cd ./ppconsul-master
   35  ls -al
   36  rm -rf ./8
   37  rm -rf ./*
   38  git clone git@github.com:oliora/ppconsul.git
   39  history





   1  pip install conan -i http://mirrors.aliyun.com/pypi/simple/
    2  pip3 install conan -i http://mirrors.aliyun.com/pypi/simple/
    3  python3 -m pip install --upgrade pip
    4  pip3 install conan -i http://mirrors.aliyun.com/pypi/simple/
    5  pip3 install conan
    6  python3 -m pip install --upgrade setuptools
    7  pip3 install conan
    8  find /home/tools/ -name "conan"
    9  cd /home/
   10  unzip ppconsul-master.zip
   11  cd ./ppconsul-master
   12  /home/tools/python3/bin/conan install .
   13  pip3 install pysqlite3
   14  /home/tools/python3/bin/conan install .
   15  yum install sqlite*
   16  cd /home/tools/Python-3.7.10
   17  ./configure --prefix=/home/tools/python3/ --with-ssl
   18  make
   19  make insta;;
   20  make install
   21  /home/tools/python3/bin/conan install .
   22  cd -
   23  /home/tools/python3/bin/conan install .
   24  mkdir workspace
   25  cd workspace
   26  cmake ..
   27  yum install git
   28  cmake ..
   29  rm -rf ./*
   30  cmake ..
   31  cd ..
   32  ls -al
   33  cd ..
   34  cd ./ppconsul-master
   35  ls -al
   36  rm -rf ./8
   37  rm -rf ./*
   38  git clone git@github.com:oliora/ppconsul.git
   39  history
   40  cd /home/
   41  tar -zxvf ppconsul.tar.gz
   42  mkdir new
   43  tar -zxvf ppconsul.tar.gz  ./new/
   44  cd ./new/
   45  cp ../ppconsul.tar.gz  .
   46  tar -zxvf ppconsul.tar.gz
   47  cd
   48  cd -
   49  /home/tools/python3/bin/conan install .
   50  mkdir workspace
   51  cd workspace
   52  cmake ..
   53  cmake --build . --config Release
   54  rm -rf ./*
   55  cmake --build . --config Release
   56  cmake ..
   57  cd ..
   58  mkdir ppconsul_output
   59  cd -
   60  make -j4 DESTDIR=../ppconsul_output/ install
   61  ls
   62  cd ..
   63  ls -al
   64  cd ./ppconsul_output
   65  ls -al
   66  history


库使用：
    1  cd /home/
    2  ls -al
    3  tar -zxvf ppconsul_output.tar.gz
    4  cd ./ppconsul_output
    5  ls -al
    6  ls
    7  vi register.cpp
    8  g++ -o register register.cpp  -I./ppconsul_output/usr/local/include/ -L./ppconsul_output/usr/local/lib64/
    9  PWD
   10  pwd
   11  g++ -o register register.cpp  -I/home/ppconsul_output/usr/local/include/ -L/home/ppconsul_output/usr/local/lib64/
   12  yum install boost
   13  g++ -o register register.cpp  -I/home/ppconsul_output/usr/local/include/ -L/home/ppconsul_output/usr/local/lib64/
   14  find / -name variant.hpp
   15  exit
   16  cd /home/
   17  ls -al
   18  tar -zxvf boost.tar.gz
   19  g++ -o register register.cpp  -I/home/ppconsul_output/usr/local/include/ -I/root/.conan/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/include/ -L/home/ppconsul_output/usr/local/lib64/
   20  cd ./ppconsul_output
   21  g++ -o register register.cpp  -I/home/ppconsul_output/usr/local/include/ -I/root/.conan/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/include/ -L/home/ppconsul_output/usr/local/lib64/
   22  cd
   23  cd -
   24  cd ..
   25  ls -al
   26  cd ./root/
   27  pwd
   28  cd-
   29  cd -
   30  cd ./ppconsul_output
   31  g++ -o register register.cpp  -I/home/ppconsul_output/usr/local/include/ -I/home/root/.conan/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/include/ -L/home/ppconsul_output/usr/local/lib64/
   32* cd /home/root/.conan/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/lib/
   33  g++ -o register register.cpp  -I/home/ppconsul_output/usr/local/include/ -I/home/root/.conan/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/include/ -L/home/ppconsul_output/usr/local/lib64/ -L/home/root/.conan/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/lib
   34  g++ -o register register.cpp  -I/home/ppconsul_output/usr/local/include/ -I/home/root/.conan/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/include/ -L/home/ppconsul_output/usr/local/lib64/ -L/home/root/.conan/data/boost/1.78.0/_/_/package/adf48b8e4446dcb68f440fe42ff08878d5c7feed/lib -lppconsul
   35  ./register
   36  ldd register
   37  find /home/ -name  libppconsul.so.0.2
   38  cd /home/ppconsul_output/usr/local/lib64/
   39  ls -al
   40  export LD_LIBRARY_PATH=/home/ppconsul_output/usr/local/lib64
   41  ldocnfig
   42  ldcofig
   43  ldconfig
   44  ./register
   45  cd -
   46  ./register
   47  history
