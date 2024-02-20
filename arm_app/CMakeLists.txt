
#
#CMakeLists.txt
#

#指定cmake版本 
cmake_minimum_required(VERSION 3.8.2)
#指定系统名称
SET(CMAKE_SYSTEM_NAME Linux)
#指定C编译链
#SET(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
#指定C++编译链
#SET(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
 
#指定项目的名称，一般和项目的文件夹名称对应
PROJECT(my_test)

#头文件目录
INCLUDE_DIRECTORIES(
 include
 )
 
#源文件目录
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
 
#set environment
#variable，设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执
#行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"

SET(TEST_MATH
 ${DIR_SRCS}
 )

#添加库所在的目录
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
 
#添加要编译的可执行文件
ADD_EXECUTABLE(${PROJECT_NAME} ${TEST_MATH})


#添加可执行文件所需要的库的目录，如果没有添加库所在的目录LINK_DIRECTORIES，那就要指定路径和库的名称
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/libfuncso.so ${PROJECT_SOURCE_DIR}/lib/libfunc.a)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} funcso func)