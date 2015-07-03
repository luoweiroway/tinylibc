# slibc
> A small C library for learning.

#定位
glibc的代码非常庞大而且佶屈聱牙，非常难读，定位于嵌入式linux系统的uClibc虽相对来说轻量一点，但对于初学者来说一点也不轻量。

所以开发了一个简易版的C库，功能、性能、可移植性上点到为止，便于学习入门，目的并不是为了重复造轮子，仅作提高自身及交流学习之用。

#功能
目前功能比较少：

* CPU：X86-64，操作系统：linux
* 拥有自己的入口函数，正常的进程退出操作；
* 基本的字符串操作，部分，待增加；

#使用
###编译C库
```
# gcc -c -fno-builtin -nostdlib -fno-stack-protector entry.c stdio.c string.c printf.c
```
上述命令编译各源文件，选项功能依次是：关闭GCC内置函数功能,不使用任何来自Glibc、GCC的库文件和启动文件,禁用堆栈保护。

```
# ar -rs slibc.a printf.o stdio.o string.o
```
上述命令产生静态链接库。

###编译你的C程序

```
# gcc -c -ggdb -fno-builtin -nostdlib test.c
# ld -static -e slibc_entry entry.o test.o slibc.a -o test
```
静态链接，指定入口函数为slibc_entry，其在entry.c中定义

#TODO

* 增加Makefile；
* 增加堆上的动态内存管理；
