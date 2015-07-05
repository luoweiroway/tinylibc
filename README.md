# tinylibc
> A tiny C library for learning.

#定位
glibc的代码非常庞大而且佶屈聱牙，非常难读，定位于嵌入式linux系统的uClibc虽相对来说轻量一点，但对于初学者来说一点也不轻量。

所以开发了一个简易版的C库，功能、性能、可移植性上点到为止，便于学习入门，目的并不是为了重复造轮子，仅作提高自身及交流学习之用。

欢迎fork并添加代码，欢迎试用并提交issue。

#功能
目前功能比较少：

* CPU：X86-64，操作系统：linux
* 拥有自己的入口函数，正常的进程退出操作；
* 基本的字符串操作，部分，待增加；

#使用
两种方法使用，简洁一点就是直接用make命令生成静态库与启动文件，并编译链接C程序，如下：
##使用Makefile
```
make
```
将会生成tinylibc.a(静态库)及start.o(启动文件)，以及最终的可执行程序文件。


由于目前项目文件非常少，所以也可以直接使用gcc编译套件进行手动编译，如下：

##使用gcc编译器套件
###1 编译C库
```
# gcc -c -fno-builtin -nostdlib -fno-stack-protector start.c stdio.c string.c printf.c
```
上述命令编译各源文件，选项功能依次是：关闭GCC内置函数功能,不使用任何来自Glibc、GCC的库文件和启动文件,禁用堆栈保护。

```
# ar -rs tinylibc.a printf.o stdio.o string.o
```
上述命令产生静态链接库。

###2 编译你的C程序

```
# gcc -c -ggdb -fno-builtin -nostdlib test.c
# ld -static -e tinylibc_entry start.o test.o tinylibc.a -o test
```
静态链接，指定入口函数为tinylibc_entry，其在start.c中定义




#TODO

* 增加堆上的动态内存管理；
