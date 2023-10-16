linux系统编程

## 1. linux文件目录

Unix/Linux也采用了树状结构的文件系统，它由目录和目录下的文件一起构成。但Unix/Linux文件系统不使用`驱动器`这个概念，而是使用单一的根目录结构，所有的分区都挂载到单一的“/"目录上，其结构示意图如图所示:

![image-20230102165818854](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230102165818854.png)

- `/`:根目录，一般根目录下只存放目录，在Linux下有且只有一个根目录。所有的东西都是从这里开始。当你在终端里输入"/home"，你其实是在告诉电脑，先从/(根目录)开始，再进入到home目录。
- `/bin:/usr/bin`:可执行二进制文件的目录，如常用的命令ls、tar、mv、cat等。
- `/boot`:放置linux系统启动时用到的一些文件，如Linux的内核文件: /boot/vmlinuz，系统引导管理器:/boot/grub。
- `/dev`:存放linux系统下的设备文件，访问该目录下某个文件，相当于访问某个设备，常用的是挂载光驱mount /dev/cdrom /mnt。
- `/etc`:系统配置文件存放的目录，不建议在此目录下存放可执行文件，重要的配置文件有/etc/inittab、/etc/fstab、/etc/init.d、/etc/x11、/etc/sysconfig./etc/xinetd.d。
- `/home`:系统默认的用户家目录，新增用户账号时，用户的家目录都存放在此目录下，~表示当前用户的家目录，-edu表示用户edu的家目录。
- `/lib: /usr/lib:/usr/local/lib`系统使用的函数库的目录，程序在执行过程中，需要调用一些额外的参数时需要函数库的协助。
- `/lost+fount`:系统异常产生错误时，会将一些遗失的片段放置于此目录下。
- `/mnt:/media`:光盘默认挂载点，通常光盘挂载于/mnt/cdrom下，也不一定，可以选择任意位置进行挂载。
- `/opt`: 给主机额外安装软件所摆放的目录。
- `/proc`:此目录的数据都在内存中，如系统核心，外部设备，网络状态，由于数据都存放于内存中



linux命令解析器

Linux系统中提供了好几种不同的命令解释器，如**shell(/bin/sh)、bash(/bin/bash)**等，一般默认使用bash作为默认的解释器。

![image-20230102203037140](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230102203037140.png)

## 2.进程

### 2.1 进程概念

在 Linux 系统中，操作系统是通过进程去完成一个一个的任务，**进程是管理事务的基本单元。**

**操作系统——公司	进程——部门	线程——员工**

### 2.2 并行和并发

**并行(parallel)：**指在同一时刻，有多条指令在**多个处理器**上同时执行。

![image-20230307170345655](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230307170345655.png)

**并发(concurrency)：**指在同一时刻只能有一条指令执行，但多个进程指令被快速的轮换执行，使得在宏观上具有多个进程同时执行的效果，但在微观上并不是同时执行的，只是把时间分成若干段，使多个进程快速交替的执行。

![image-20230307170409730](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230307170409730.png)

### 2.3 进程控制块PCB（了解）

进程运行时，**内核为进程每个进程分配一个PCB（进程控制块）**，维护进程相关的信息，Linux内核的进程控制块是task_struct结构体。

### 2.4 进程的状态（重点）

进程状态反映进程执行过程的变化。这些状态随着进程的执行和外界条件的变化而转换。

在三态模型中，进程状态分为三个基本状态，即**运行态，就绪态，阻塞态**。

在五态模型中，进程分为**新建态、终止态，运行态，就绪态，阻塞态**。

![image-20230307200003685](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230307200003685.png)

### 2.5 进程号和相关函数

每个进程都由一个进程号来标识，其类型为 pid_t（整型），进程号的范围：0～32767。进程号总是唯一的，但进程号可以重用。当一个进程终止后，其进程号就可以再次使用。



**进程号（PID）**：

标识进程的一个非负整型数。

**父进程号（PPID）**：

任何进程（ 除 init 进程）都是由另一个进程创建，该进程称为被创建进程的父进程，对应的进程号称为父进程号（PPID）。如，A 进程创建了 B 进程，A 的进程号就是 B 进程的父进程号。

**进程组号（PGID）**：

进程组是一个或多个进程的集合。他们之间相互关联，进程组可以接收同一终端的各种信号，关联的进程有一个进程组号（PGID） 。这个过程有点类似于 QQ 群，



### 2.6 进程的创建

系统允许一个进程创建新进程，新进程即为子进程，子进程还可以创建新的子进程，形成进程树结构模型。

```c
#include <sys/types.h>
#include <unistd.h>
​
pid_t fork(void);
功能：
    用于从一个已存在的进程中创建一个新进程，新进程称为子进程，原进程称为父进程。
参数：
    无
返回值：
    成功：子进程中返回 0，父进程中返回子进程 ID。pid_t，为整型。
    失败：返回-1。
    失败的两个主要原因是：
        1）当前的进程数已经达到了系统规定的上限，这时 errno 的值被设置为 EAGAIN。
        2）系统内存不足，这时 errno 的值被设置为 ENOMEM。
```

![image-20230308201915216](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230308201915216.png)

### 2.7 父子进程关系

使用 fork() 函数得到的子进程是父进程的一个复制品，它从父进程处继承了整个进程的地址空间：包括进程上下文（进程执行活动全过程的静态描述）、进程堆栈、打开的文件描述符、信号控制设定、进程优先级、进程组号等。

子进程所独有的只有它的进程号，计时器等（只有小量信息）。因此，使用 fork() 函数的代价是很大的。

![image-20230308203306998](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230308203306998.png)

简单来说， 一个进程调用 fork() 函数后，系统先给新的进程分配资源，例如存储数据和代码的空间。然后把原来的进程的所有值都复制到新的新进程中，只有少数值与原来的进程的值不同。相当于克隆了一个自己。

实际上，更准确来说，Linux 的 fork() 使用是通过**读时共享，写时拷贝** (copy- on-write) 实现。写时拷贝是一种可以推迟甚至避免拷贝数据的技术。内核此时并不复制整个进程的地址空间，而是让父子进程共享同一个地址空间。只用在需要写入的时候才会复制地址空间，从而使各个进行拥有各自的地址空间。也就是说，资源的复制是在需要写入的时候才会进行，在此之前，只有以只读方式共享。

注意：fork之后父子进程共享文件，fork产生的子进程与父进程相同的文件文件描述符指向相同的文件表，引用计数增加，共享文件文件偏移指针。

### 2.8 区分父子进程

fork() 函数被调用一次，但返回两次。两次返回的区别是：**子进程的返回值是 0，而父进程的返回值则是新子进程的进程 ID**。









## 3. 线程

### 3.1 线程的概念

在许多经典的操作系统教科书中，总是把进程定义为程序的执行实例，它并不执行什么, **进程只是维护应用程序所需的各种资源，而线程则是真正的执行实体。**

所以，**线程是轻量级的进程（LWP：light weight process），在Linux环境下线程的本质仍是进程。**

为了让进程完成一定的工作，进程必须至少包含一个线程。

![image-20230306135258286](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230306135258286.png)

进程，直观点说，保存在硬盘上的程序运行以后，会在内存空间里形成一个独立的内存体，这个内存体有自己的地址空间，有自己的堆，上级挂靠单位是操作系统。操作系统会以进程为单位，分配系统资源，所以我们也说，**进程是CPU分配资源的最小单位**。

线程存在与进程当中(进程可以认为是线程的容器)，是操作系统调度执行的最小单位。说通俗点，线程就是干活的。

进程是具有一定独立功能的程序关于某个数据集合上的一次运行活动，进程是系统进行资源分配和调度的一个独立单位。

线程是进程的一个实体，是 CPU 调度和分派的基本单位，它是比进程更小的能独立运行的基本单位。线程自己基本上不拥有系统资源，只拥有一点在运行中必不可少的资源（如程序计数器，一组寄存器和栈），但是它可与同属一个进程的其他的线程共享进程所拥有的全部资源。

**进程是操作系统分配资源的最小单位**

**线程是操作系统调度的最小单位**

### 3.2 线程的常用操作

#### 3.2.1 线程号

就像每个进程都有一个进程号一样，每个线程也有一个线程号。进程号在整个系统中是唯一的，但线程号不同，线程号只在它所属的进程环境中有效。

进程号用 pid_t 数据类型表示，是一个非负整数。线程号则用 pthread_t 数据类型来表示，Linux 使用无符号长整数表示。

有的系统在实现pthread_t 的时候，用一个结构体来表示，所以在可移植的操作系统实现不能把它做为整数处理。

**pthread_self函数：**

```c
#include <pthread.h>

pthread_t pthread_self(void);
功能：
    获取线程号。
参数：
    无
返回值：
    调用线程的线程 ID 。
```

**pthread_equal函数:**

```
int pthread_equal(pthread_t t1, pthread_t t2);
功能：
    判断线程号 t1 和 t2 是否相等。为了方便移植，尽量使用函数来比较线程 ID。
参数：
    t1，t2：待判断的线程号。
返回值：
    相等：  非 0
    不相等：0
```

#### 3.3.2 线程的创建

**pthread_create函数：**

```c

#include <pthread.h>
​
int pthread_create(pthread_t *thread,
            const pthread_attr_t *attr,
            void *(*start_routine)(void *),
            void *arg );
功能：
    创建一个线程。
参数：
    thread：线程标识符地址。
    attr：线程属性结构体地址，通常设置为 NULL。
    start_routine：线程函数的入口地址。
    arg：传给线程函数的参数。
返回值：
    成功：0
    失败：非 0
```

在一个线程中调用pthread_create()创建新的线程后，当前线程从pthread_create()返回继续往下执行，而新的线程所执行的代码由我们传给pthread_create的函数指针start_routine决定。

由于pthread_create的错误码不保存在errno中，因此不能直接用perror()打印错误信息，可以先用strerror()把错误码转换成错误信息再打印。

参考程序：

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void *fun()
{
        printf("new thread task tid: %lu\n", pthread_self());

        return NULL;
}

int main()
{
        int ret = -1;
        pthread_t tid = -1;

        //create thread
        ret = pthread_create(&tid, NULL, fun, NULL);
        if(0 != ret){
                printf("pthread_creat failed...\n");
                return 1;
        }
        printf("main thread...tid: %lu\n", pthread_self());

        printf("enter any to make main thread exit...\n");
        getchar();

        return 0;
}

```

#### 3.3.3 多线程共享数据

- 线程共享资源
  1)文件描述符表
  2)每种信号的处理方式
  3)当前工作目录
  4)用户ID和组ID
  **内存地址空间(.text/.data/.bss/heap/共享库)**
- 线程非共享资源
  1)线程id
  2)处理器现场和栈指针(内核栈)
  3)独立的栈空间(用户空间栈)
  4)errno变量
  5)信号屏蔽字
  6)调度优先级

参考程序:

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

int num = 100;  //数据段

void *fun(void *arg)
{
        int *pn = (int*)arg;
        printf("before fun num = %d *pn = %d\n", num, *pn);
        num++;
        (*pn)++;
        printf("after fun num = %d *pn = %d\n", num, *pn);

        return NULL;
}

int main()
{
        int ret = -1;
        pthread_t tid;
        memset(&tid, 0, sizeof(tid));

        int *p = NULL;  //堆
        p = malloc(sizeof(int));

        ret = pthread_create(&tid, NULL, fun, (void*)p);
        if(ret != 0){
                printf("pthread_create failed...\n");
                return 0;
        }

        printf("按下任意键，函数继续...\n");
        getchar();
        printf("main num = %d\n", num);
        free(p);
        
        return 0;
}

```

#### 3.3.4 线程资源回收

pthread_join函数

```
#include <pthread.h>
​
int pthread_join(pthread_t thread, void **retval);
功能：
    等待线程结束（此函数会阻塞），并回收线程资源，类似进程的 wait() 函数。如果线程已经结束，那么该函数会立即返回。
参数：
    thread：被等待的线程号。
    retval：用来存储线程退出状态的指针的地址。
返回值：
    成功：0
    失败：非 0
```

参考程序：

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

void *fun(void *arg)
{
        int i = 0;
        for(i = 0; i < 5; i++){
                printf("fun thread do working %d\n", i);
                sleep(1);
        }

        return (void*)0x3;
}

int main()
{
        int ret = -1;
        void *retp = NULL;
        pthread_t tid = -1;

        //创建一个线程
        ret = pthread_create(&tid, NULL, fun, NULL);
        if(ret != 0){
                printf("pthread_create failed...\n");
                return 1;
        }
        printf("main thread tunning...\n");

        //等待线程结束，会阻塞
        ret = pthread_join(tid,  &retp);
        if(ret != 0){
                printf("pthread_join failed...\n");
                return 1;

        }
        printf("retp: %p\n", retp);
        printf("main thread exit...\n");

        return 0;
}
```

