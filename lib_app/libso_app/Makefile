##
## Makefile
##
## History:
##     20230107 luoxi
##     arm-ca9-linux-gnueabihf-gcc
##     arm-mol-linux-uclibcgnueabihf-gcc   
##     arm-linux-gnueabihf-gcc

##编译动态库命令
##gcc -I ./ -shared -fpic -o libfuncso.so libfuncso.c

default: all
PWD			:= $(shell pwd)

ROOTDIR = ./
# 获取当前目录
CURRDIR = $(shell pwd)
# 交叉编译工具
CC = $(TOOL_PREFIX)gcc
# 生成静态库命令
AR = $(TOOL_PREFIX)ar rc
# 编译选项参数
CFLAGS = -g -Wall
# 编译链接库
LDFLAGS = $(CURRDIR)/
LDFLAGS += $(CURRDIR)/
# 头文件目录
INC_DIR = -I./
# 包含的系统库文件
LIBFLGS = -lpthread
#LIBFLGS += -L./ libfunc.a
#LIBFLGS += -L./ libfuncso.so
# 生成的可执行程序的名称
TARGET = libfuncso.so
# 将该目录下的.c文件展开
SOURCES = $(wildcard $(CURRDIR)/*.c)
# 去除该目录 这个当前还没用到
DIR = $(notdir $(CURRDIR))
# 将展开的.c文件替换成.o文件，获取.o文件列表 为了编译可执行程序时使用
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

.PHONY: clean all

all : $(TARGET)

# 静态模式，将所有.o文件匹配成.c文件，然后将所有依赖文件（$^）编译成目标文件（$@）将c文件编译成o文件
%.o:%.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -fpic $^ -o $@

# 将.o文件编译成动态库
$(TARGET) : $(OBJECTS)
	echo -e $(OBJECTS)
	$(CC) $(CFLAGS) $(INC_DIR) -fpic -shared -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) $(OBJECTS)


