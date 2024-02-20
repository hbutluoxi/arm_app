##
## Makefile
##
## History:
##     20240220 luoxi
##     arm-ca9-linux-gnueabihf-gcc
##     arm-mol-linux-uclibcgnueabihf-gcc   
##     arm-linux-gnueabihf-gcc

default: all
PWD			:= $(shell pwd)

#当前目录
ROOTDIR = ./
# 获取当前目录
CURRDIR = $(shell pwd)
# 交叉编译工具
CC = $(TOOL_PREFIX)gcc
# 生成静态库命令
AR = $(TOOL_PREFIX)ar
# 编译选项参数
CFLAGS = -g -Wall
# 头文件目录
INC_DIR = -I./include/
# 包含库目录
LIB_DIR = -L./mylib/
# 包含的系统库文件
LIBFLGS = -lpthread
# 编译链接库
LDFLAGS = $(CURRDIR)/applib/libfunc.a
LDFLAGS += $(CURRDIR)/applib/libsqlite3.a
LDFLAGS += $(CURRDIR)/applib/libfuncso.so
# 生成的可执行程序的名称
TARGET = release/arm_app
# 将该目录下的.c文件展开
SOURCES = $(wildcard $(CURRDIR)/src/*.c)
# 去除该目录 这个当前还没用到
DIR = $(notdir $(CURRDIR)/src)
# 将展开的.c文件替换成.o文件，获取.o文件列表 为了编译可执行程序时使用
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

.PHONY: clean all

all : $(TARGET)

# 静态模式，将所有.o文件匹配成.c文件，然后将所有依赖文件（$^）编译成目标文件（$@）将c文件编译成o文件
%.o:%.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $^ -o $@

# 将.o文件编译成可执行程序
$(TARGET) : $(OBJECTS)
# echo -e $(OBJECTS)
# 以下链接库的方式两种形式都可以
	$(CC) $(OBJECTS) -fPIC -o $(TARGET) $(LIBFLGS) $(LDFLAGS) -ldl
	#$(CC) $(LIB_DIR) $(OBJECTS) -o $(TARGET) $(LIBFLGS) -lfunc -lsqlite3 -lfuncso
	rm -f $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS)


