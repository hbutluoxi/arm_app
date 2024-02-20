20230108
在linux应用中去编写静态库与动态库，主要是为了封装一些函数。或者为了一些联合开发。

编译一般分为四部分 预处理（-E  c文件变成.i文件） 编译（-S i文件变成.s文件） 汇编（-c s文件变成.o文件） 链接（-o o文件变成可执行程序）

静态库则只需要先编译成.o文件后单独用命令生成静态库。

1 新建libfunc.c  libfun.h  库文件最好以lib开头
2 在libfunc.c 中编写自己的库函数，在头文件中声明
3 编译 gcc -I ./ -c libfunc.c    编译当前文件和当前目录下的头文件,会生成一个libfunc.o的文件
4 封库 ar rc libfunc.a libfunc.o 会生成一个 libfunc.a的库文件，可以用grep “函数名” libfunc.a查询该接口是否被包含。将生成的.a文件放在主程序的编译目录下去编译
5 将库文件和头文件放在主函数中去使用即可，在makefile中编译时链接库文件
6 LIBFLGS += -L./ libfunc.a
7 或者 gcc -o main main.c -L ../lib/ -ltest

编译静态库
gcc -I ./ -c libfunc.c
ar rc libfunc.a libfunc.o

编译成功后，可以使用命令查看函数是否被链接
grep "Crc16_get" libfunc.a


编译动态库
gcc -I ./ -shared -fpic -o libfuncso.so libfuncso.c

查看当前so符号表
objdump -tT libfuncso.so
mn -D libfuncso.so

查看当前so中是否有yourFunction函数
nm -D libfuncso.so |grep -w yourFunction

或者也可以使用Makefile方式去编译，或者用脚本加Makefile的方式

sqlite-amalgamation-3400100是数据库sqlite3的源码编译的静态库文件，暂未测试，添加头文件后可以在mainproject中使用