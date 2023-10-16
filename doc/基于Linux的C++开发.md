## 基于Linux的C/C++开发

## linux系统编程

### 1 开发环境搭建

#### 1.1 编译器，调试器安装

- 安装GCC， GDB

```bash
sudo apt update
#通过以下命令安装编译器和调试器
sudo apt install bulid-essential gdb
```

- 安装成功确认

```bash
#以下命令确认软件安装是否成功，如果成功则显示版本号
gcc --version
g++ --version
gdb --version
```

#### 1.2 cmake安装

- 安装cmake

  ```bash
  #通过以下命令安装编译器和调试器
  sudo apt install cmake
  ```

- 安装成功确认

  ```bash
  #如果成功，则显示版本号
  cmake --version
  ```

  

### 2 编译过程

前言:

1. GCC编译器支持编译Go、Objective-C，Objective-C ++，Fortran，Ada，D和BRIG (HSAIL)等程序;

2. Linux开发C/C++一定要熟悉GCC

3. vscode是通过调用GCC编译器来实现C/C++的编译工作的;

   实际使用中:

   - **使用gcc指令编译C代码。**

   - **使用g++指令编译C++代码**

#### 2.1 编译过程

1. 预处理Pre-Processing	//.i文件

```bash
# -E选项指示编译器仅对输入文件进行预处理
g++ -E test.cpp -o test.i	
```

2. 编译-Compiling	//.s文件:

```bash
# -S 编译选项告诉g++在为C++代码产生了汇编语言文件后停止编译
# g++产生的汇编语言文件的缺省扩展名是 .s
g++ -S test.i -o test.s
```

3. 汇编-Assembling	// .o文件

```bash
# -c选项告诉g++仅把源代码编译为机器语言的目标代码
# 缺省时g++建立的目标代码文件有一个.o 的扩展名。
g++ -c test.s -o test.o
```

4. 链接-Linking	//bin文件.

```bash
#-o编译选项来为将产生的可执行文件用指定的文件名
g++ test.o -o test
```

以上可归为一条：

```bash
g++ test.cpp -o test
```

#### 2.2 g++重要编译参数

1. **-g** 编译带调试信息的可执行文件

   ```bash
   #-g 选项告诉 GCC产生能被GNU调试器GDB使用的调试信息，以调试程序。
   #产生带调试信息的可执行文件test
   g++ -g test.cpp
   ```

2. **-O[n]** 优化源代码

   ```bash
   #所谓优化，例如省略掉代码中从未使用过的变量、直接将常量表达式用结果值代替等等，这些操作会缩减目标文件所包含的代码量，提高最终生成的可执行文件的运行效率。
   
   # -O 选项告诉g++对源代码进行基本优化。这些优化在大多数情况下都会使程序执行的更快。-O2选项告诉g++产生尽可能小和尽可能快的代码。如-O2，-O3，-On (n常为0-3)
   # -O 同时减小代码的长度和执行时间，其效果等价于-O1
   # -O0 表示不做优化
   # -O1 为默认优化
   # -O2 除了完成-O1的优化之外，还进行一些额外的调整工作，如指令调整等。
   # -O3 则包括循环展开和其他一些与处理特性相关的优化工作。
   # 选项将使编译的速度比使用 -O 时慢，但通常产生的代码执行速度会更快。
   
   #使用 -O2 优化源代码，并输出可执行文件
   g++ -O2 test.cpp
   ```


3. **-l 指定库文件  ，-L 指定库文件路径**

   ```bash
   # -l参数(小写)就是用来指定程序要链接的库，-l参数紧接着就是库名
   # 在/lib和/usr/lib和/usr/local/lib里的库直接用-l参数就能链接
   
   # 链接glog库
   g++ -lglog test.cpp
   
   # 如果库文件没放在上面三个目录里，需要使用-L参数(大写)指定库文件所在目录
   # -L参数跟着的是库文件所在的目录名
   
   # 链接mytest库， libmytest.so在/home/bing/mytestlibfolder目录下
   g++ -L/home/bing/mytestlibfolder -lmytest test.cpp
   ```

   

4. **-I 指定头文件搜索目录**

   ```bash
   # -I
   # /usr/include目录一般是不用指定的, gcc知道去那里找，但是如果头文件不在/usr/include里我们就要用-I参数指定了，比如头文件放在/myinclude目录里，那编译命令行就要加上-I/myinclude参数了，如果不加你会得到一个"xxxx.h: No such file or directory"的错误。-T参数可以用相对路径，比如头文件在当前目录,可以用-I .来指定。上面我们提到的-cflags参数就是用来生成-I参数的。
   
   g++ -I/myinclude test.cpp
   ```

5. -Wall 打印警告信息

   ```bash
   # 打印gcc提供的警告信息
   g++ -Wall test.cpp
   ```

6. -w 关闭警告信息

   ```bash
   # 关闭所有警告信息
   g++ -w test.cpp
   ```

7. -stdc++11 设置编译标准

   ```bash
   # 使用c++11标准编译 test.cpp
   g++ -std=c++11 test.cpp
   ```

8. -o 指定输出文件名

   ```bash
   # 指定输出可执行文件为test
   g++ test.cpp -o test
   ```

9. -D 宏定义

```bash
# 在使用gcc/g++编译的时候定义宏
# 常用场景:
# -DDEBUG定义DEBUG宏，可能文件中有DEBUG宏部分的相关信息，用个DDEBUG来选择开启或关闭DEBUG
```

```c
// -Dname 定义宏name，默认定义内容为字符串"1"

#include<stdio.h>

int main()
{
    #ifdef DEBUG
    	printf("DEBUG LOG\n");
    #endif
    	printf("in\n");
}`		

// 1．在编译的时候，使用g++ -DDEBUG main.cpp
// 2．第七行代码可以被执行

```

#### 2.3 g++命令行编译

```bash
.
├── include
│   └── swap.h
├── main.cpp
└── src
    └── swap.cpp
```

##### 2.3.1 直接编译

直接编译

```bash
# 将 main.cpp src/swap.cpp 编译为可执行文件
g++ main.cpp src/swap.cpp -Iinclude
# 运行
./a.out

#增加编译参数
g++ main.cpp src/swap.cpp -Iinclude -std=c++11 -o2 -Wall -o b.out
```

##### 2.3.2 生成库文件并编译

- **链接静态库**生成可执行文件

```bash
#进入src目录
cd src

#汇编，生成swap.o文件
g++ swap.cpp -c -I../include
#生成静态库文件libswap.a
ar rs libswap.a swap.o

#回到上级目录
cd ..

#链接，生成可执行文件
g++ main.cpp -Iinclude -Lsrc -Iinclude -o static_main

#运行可执行文件
./static_main
```

- 链接动态库生成可执行文件

```bash
#进入src目录
cd src

生成动态库libswap.so
g++ swap.cpp -I../include -fPIC -shared -o libswap.so
## 以上命令等价于
gcc swap.cpp -I../include -fPIC
gcc -shared -o libswap.so swap.o

#回到上级目录
cd ..

#链接，生成可执行文件
g++ main.cpp -Iinclude -Lsrc -lswap -Lsrc -o dyna_main

#运行可执行文件
LD_LIBRARY_PATH=src ./dyna_main
```

#### 2.4 gdb调试器

- GDB(GNU Debugger)是一个用来调试C/C++程序的功能强大的调试器，是Linux系统开发C/C++最常用的调试器
- 程序员可以使用**GDB来跟踪程序中的错误**，从而减少程序员的工作量。. Linux开发C/C++一定要熟悉GDB
- vsCode是通过调用GDB调试器来实现C/C++的调试工作的;
  Windows系统中，常见的集成开发环境(IDE)，如VS、VC等，它们内部已经嵌套了相应的调试器

##### 2.4.1 GDB主要功能:

- 设置断点(断点可以是条件表达式)
- 使程序在指定的代码行上暂停执行
- 便于观察单步执行程序，便于调试
- 查看程序中变量值的变化
- 动态改变程序的执行环境
- 分析崩溃程序产生的core文件

##### 2.4.2 调试命令

```bash
##以下命令后括号内为命令的简化使用，比如run(r)，直接输入命令r就代表命令run

$(gdb)help(h)	# 查看命令帮助，具体命令查询在gdb中输入he1p + 命令
$(gdb)run(r)	# 重新开始运行文件（run-text:加载文本文件,run-bin:加载二进制文件)
$(gdb)start		# 单步执行，运行程序，停在第一行执行语句
$(gdb)list(l)	# 查看原代码(list-n ,从第n行开始查看代码。1ist+函数名:查看具体函数)
$(gdb)set		# 设置变量的值
$(gdb)next(n)	# 单步调试(逐过程，函数直接执行>
$(gdb)step(s)	# 单步调试（逐语句:跳入自定义函数内部执行）
$(gdb)backtrace(bt)		# 查看函数的调用的栈帧和层级关系
$(gdb)frame(f)	# 切换函数的栈帧
$(gdb)info(i)	# 查看函数内部局部变量的数值
$(gdb)finish 	# 结束当前函数，返回到函数调用点
$(gdb)continue(c)	# 继续运行
$(gdb)print(p）	# 打印值及地址
$(gdb)quit(q)	 # 退出gdb
$(gdb)info breakpoints	#查看当前设置的所有断点
$(gdb)delete breakpoints num(d)	#删除第num个断点
$(gdb)display	#追踪查看具体变量值
$(gdb)undisp1ay	#取消追踪观察变量
$(gdb)watch		#被设置观察点的变量发生修改时，打印显示
$(gdb)i watch	#显示观察点
$(gdb)enable breakpoints	#启用断点
$(gdb)disable breakpoints	#禁用断点
$(gdb)x					   #查看内存x/20xw显示20个单元，16进制，4字节每单元
$(gdb)run argv[1] argv[2]	#调试时命令行传参
$(gdb)set fo1low-fork-mode chi7d		#Makefile项目管理:选择跟踪父子进程(fork()

```

Tips:
 	1. 编译程序时需要加上-g，之后才能用gdb进行调试: gcc -g main.c -o main
 	2. 回车键:重复上一命令



### 3 makefile

命名：makefile 

​			Makefile



**1个规则：**

```makefile
目标：依赖条件
	(一个tab缩进)命令
```

	1. 目标的时间必须晚于依赖条件的时间，否则更新目录
	1. 依赖条件如果不存在，找寻新的规则产生依赖



示例程序：

makefile

```makefile
a.out:hello.o add.o sub.o div.o
        gcc hello.o add.o sub.o div.o -o a.out

hello.o:hello.c
        gcc -c hello.c -o hello.o
add.o:add.c
        gcc -c add.c -o add.o
sub.o:sub.c
        gcc -c sub.c -o sub.o
div.o:div.c
        gcc -c div.c -o div.o

```

<img src="C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230311151809173.png" alt="image-20230311151809173" style="zoom:80%;" />

修改add.c，makefile只对修改过得程序重新编译

![image-20230311152033054](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230311152033054.png)



**注意：makefile将文件中的第一组目标作为终极目标**

All:指定makefile的终极目标

```makefile
All:a.out

a.out:hello.o add.o sub.o div.o
        gcc hello.o add.o sub.o div.o -o a.out

hello.o:hello.c
        gcc -c hello.c -o hello.o
add.o:add.c
        gcc -c add.c -o add.o
sub.o:sub.c
        gcc -c sub.c -o sub.o
div.o:div.c
        gcc -c div.c -o div.o

```

2个函数

3个自动变量

### 4 linux系统函数

![image-20230425163530516](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230425163530516.png)



![image-20230425163712653](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230425163712653.png)

![image-20230425173232170](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230425173232170.png)

### 5 进程

#### 5.1 进程概述

![image-20230426110942484](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230426110942484.png)

![image-20230426111014001](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230426111014001.png)

![image-20230426111051660](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230426111051660.png)

![image-20230426111114312](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230426111114312.png)

![image-20230426111136580](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230426111136580.png)



![image-20230426112300932](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230426112300932.png)

![image-20230426112338117](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230426112338117.png)

![image-20230426112931372](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230426112931372.png)



#### 5.2 进程间通信

![image-20230426141102850](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230426141102850.png)

![image-20230426141502637](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230426141502637.png)
