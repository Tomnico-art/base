**Windows网络编程**

## 线程

### 1. 线程的创建

####  线程的介绍

线程概念:
**操作系统调度的最小单位**。线程包含在进程中，是进程中实际运行的单位。一个进程中可以同时运行多个线程，每个线程可以执行不同的任务，这就是所谓的多线程。
内核（英语:Kernel)，又称核心，**是操作系统最基本的部分**，主要负责管理系统资源。

#### 线程的分类

1. 用户线程
   **用户线程受内核支持，但无须内核管理**
   由进程利用线程库创建，释放和管理，因此内核对用户线程不可知，内
   核只会负责用户线程的进程以及轻量级进程的调度，而不会消耗其他内核资源。因为上下文切换不需要内核干预，所以可以省去用户线程进出内核态的消耗由于用户线程在用户空间中实现，所以一个用户线程如果阻塞在系统调用中，则整个进程都将会阻塞。
2. 内核线程
   **由操作系统直接支持，管理和调度，通过系统调用完成**

#### 创建线程

创建线程
`HANDLE CreateThread(
LPSECURITY ATTRIBUTES IpT hreadAttributes, DWORD dwStackSize, LPTHREAD START ROUTINElpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadld);`

第一个参数是指向SECURITY ATTRIBUTES型态的结构的指针。在Windows 98中忽略该参数。在WindowsNT中，它被设为NULL。
第二个参数是用于新线程的初始堆栈大小，默认值为0。在任何情况下，Windows根据需要动态延长堆栈的大小.
第三个参数是指向线程函数的指标。函数名称没有限制，但是必须以下列形式声明:**DWORD WINAPI ThreadProc (PVOID pParam);**
第四个参数为传递给ThreadProc的参数。**这样主线程和从属线程就可以共享数据**。
第五个参数通常为0，但当建立的线程不马上执行时为标记CREATE_SUSPENDED。线程将暂停直到呼叫ResumeThread来恢复线程的执行为止。
第六个参数是一个指标，指向接受执行绪ID值的变量。

```c++
#include<iostream>
#include<windows.h>
using namespace std;

DWORD WINAPI ThreadProc(PVOID lp)
{
	for (int i = 1; i <= 10; i++)
	{
		cout << i << " ";
	}
	return 0;
}

int main()
{
	//Win API 
	//创建线程,线程的挂起和恢复
	HANDLE h =  CreateThread(NULL, 0, ThreadProc, 0, CREATE_SUSPENDED, 0);	//h:句柄-内核对象
	ResumeThread(h);	//恢复

	for (int i = 11; i <= 15; i++)
	{
		cout << i << " ";
	}

	return 0;
}
```

#### 终止线程

1. 线程函数返回。
   这是确保线程的所有资源被正确地清除的唯一办法。当线程函数返回时，如下情况将会发生:
   - 在线程函数中创建的所有C++对象将通过它们的析构函数正确地撤销;
   - 操作系统将正确地释放线程的堆栈使用的内存;
   - 系统将线程的退出代码设置为线程函数的返回值;
   - 系统递减线程内核对象的引用计数。
2. ExitThread函数。
   可以通过在线程中调用ExitThread函数，来强制终止自身线程的运行。原型为:`VOID ExitThread(DWORD dwExitCode);`
   该函数将终止自身线程的运行，并导致操作系统清除该线程使用的所有操作系统资源。但是，C++资源（如C++对象)将不被正确地撤销。

#### 线程的挂起与恢复运行

任何线程都可以调用`SuspendThread()`来暂停另一个线程的运行（只要拥有线程的句柄。原型为:`DWORD SuspendThread(HANDLE hThread);`
返回值是前一次暂停计数，一个线程能够被暂停的最多次数是MAXIMUM SUSPENDcOUNT,
参数`HANDLE hThread`表示将要被挂起的线程
调用`ResumeThread()`可以让挂起的线程恢复运行。原型为:`DWORD ResumeThread(HANDLE hThread);`
返回值是前一次暂停计数，参数`HANDLE hThread`表示将要被恢复的线程

### 2. 线程间同步

#### 线程间的同步
当**多个线程无限制的在同一段时间内访问同一资源时**，会发生错误。
#### 线程间同步方法
1. 原子访问，互锁函数
   互锁函数提供了一套多个线程同步**访问一个简单变量的处理机制**。

   

   `LONG InterlockedIncrement(LONG volatile* lpAddend);`该函数提供多线程情况下，对一个变量以原子操作方式增加

   `LONG InterlockedDecrement(LONG volatile* IpAddend;`该函数提供多线程情况下，对一个变量以原子操作方式减少

   `LONG InterlockedExchange(LONG volatile* IpTarget,LONG IValue);`该函数提供在多线程情况下，以原子操作方式用IValue给lpTarget指向的目标变量赋值，并返回赋值以前的IlpTarget指向的值。
   `LONG InterlockedExchangeAdd(LONG volatile"pAddend,LONG IValue)`该函数提供在多线程情况下，以原子的操作方式将lpAddend指向的变量增加Value.并返回调用前的llpAddend指向的目标变量的值。

   ```c++
   #include<iostream>
   #include<windows.h>
   using namespace std;
   
   unsigned int g;
   DWORD WINAPI ThreadProc(LPVOID lp)
   {
   	for (int i = 0; i < 10000000; i++)
   	{
   		InterlockedIncrement(&g);	//原子锁，以原子方式自动+1
   	}
   	return 0;
   }
   
   int main()
   {
   	HANDLE h = CreateThread(0, 0, ThreadProc, 0, 0, 0);
   	for (int i = 0; i < 10000000; i++)
   	{
   		InterlockedIncrement(&g);	//原子锁，以原子方式自动+1
   	}
   	WaitForSingleObject(h, INFINITE);	//等待子线程结束
   	cout << "g = " << g << endl;
   	CloseHandle(h);	//关闭句柄
   
   	return 0;
   }
   ```

2. 临界区

   临界区**是一段连续的代码区域**，它要求在执行前获得对某些共享数据的独占的访问权。如果一个进程中的所有线程中访问这些共享数据的代码都放在临界区中，就能够实现对该共享数据的同步访问。**临界区只能用于同步单个进程中的线程**。

   

   `CRITICAL_SECTION g_sec;`            //实例化临界区对象
   `InitializeCriticalSection(&g_sec);`           //初始化临界区对象

   进入临界区`EnterCriticalSection(&g_sec);`

   进入临界区，临界区对象的引用计数加1，同一个线程可以多次调用EnterCriticalSection，但是如果调用n次EnterCriticalSection以后，必须再调用n次的LeaveCriticalSection，**使临界区对象的引用计数变为0**，其它的线程才能进入

   离开临界区`LeaveCriticalSection(&g_sec);`
   释放临界区对象`DeleteCriticalSection(&g_sec);`

   ```c++
   #include<iostream>
   #include<windows.h>
   using namespace std;
   
   unsigned int g;
   CRITICAL_SECTION g_sec;		//创建临界区对象
   DWORD WINAPI ThreadProc(LPVOID lp)
   {
   	for (int i = 0; i < 10000000; i++)
   	{
   		EnterCriticalSection(&g_sec);	//进入临界区
   		g++;
   		LeaveCriticalSection(&g_sec);	//离开临界区
   	}
   	return 0;
   }
   
   int main()
   {
   	InitializeCriticalSection(&g_sec);	//初始化临界区对象
   	HANDLE h = CreateThread(0, 0, ThreadProc, 0, 0, 0);
   	for (int i = 0; i < 10000000; i++)
   	{
   		EnterCriticalSection(&g_sec);	//进入临界区
   		g++;
   		LeaveCriticalSection(&g_sec);	//离开临界区
   	}
   	WaitForSingleObject(h, INFINITE);	//等待子线程结束
   	cout << "g = " << g << endl;
   	CloseHandle(h);	//释放句柄
   	DeleteCriticalSection(&g_sec);	//释放临界区对象
   
   	return 0;
   }
   ```

3. 内核对象

   (1）互斥变量
   互斥量类似于临界区，但它能够同步多个进程间的数据访问。
   `CreateMutex (NULL，FALSE，"MutexForSubThread");`		//创建互斥量
   `WaitForSingleObject (g_hMutex,I INFINITE);`		//等待互斥量，如果互斥量处于信号态，该函数返回，同时将互斥量自动变为无信号态
   /**访问共享数据区**/
   `ReleaseMutex (g hMutex);`		//使互斥量重新处于信号态

   ```c++
   #include<iostream>
   #include<windows.h>
   using namespace std;
   
   unsigned int g;
   HANDLE hmutex;	//创建内核对象
   DWORD WINAPI ThreadProc(LPVOID lp)
   {
   	for (int i = 0; i < 10000; i++)
   	{
   		WaitForSingleObject(hmutex, INFINITE);
   		g++;
   		ReleaseMutex(hmutex);
   	}
   	return 0;
   }
   
   int main()
   {
   	hmutex = CreateMutex(NULL, 0, NULL);
   	HANDLE h = CreateThread(0, 0, ThreadProc, 0, 0, 0);
   	for (int i = 0; i < 10000; i++)
   	{
   		WaitForSingleObject(hmutex, INFINITE);
   		g++;
   		ReleaseMutex(hmutex);
   	}
   	WaitForSingleObject(h, INFINITE);	//等待子线程结束
   	cout << "g = " << g << endl;
   	CloseHandle(h);	//释放句柄
   	CloseHandle(hmutex);
   
   	return 0;
   }
   ```

   (2)信号量

   

   (3)事件对象





## 进程

### 1. 进程的创建

#### 介绍

狭义定义∶**进程是正在运行的程序的实例**(an instance of a computerprogram that is being executed)。
广义定义: 进程是一个具有一定独立功能的程序关于某个数据集合的一次运行活动。它是操作系统动态执行的基本单元，在传统的操作系统中，进程既是基本的分配单元，也是基本的执行单元。

#### 进程的基本状态

![image-20221122210855195](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221122210855195.png)

- **创建状态︰**进程在创建时需要申请一个空白**PCB(进程控制块）**，向其中填写控制和管理进程的信息，完成资源分配。如果创建工作无法完成，比如资源无法满足，就无法被调度运行，把此时进程所处状态称为创建状态
- **就绪状态∶**进程已经准备好，已分配到所需资源，只要分配到CPU就能够立即运行
  **执行状态:**进程处于就绪状态被调度后，进程进入执行状态
- **阻塞状态∶**正在执行的进程由于某些事件（I/O请求，申请缓存区失败）而暂时无法运行，进程受到阻塞。在满足请求时进入就绪状态等待系统调用
- **终止状态︰**进程结束，或出现错误，或被系统终止，进入终止状态。无法再执行

#### 进程的创建

进程创建函数

`bool CreateProcess (
LPCTSTR lpApplicationName,
LPTSTR lpCommandLine,
LPSECURITY ATTRIBUTES lpProcessAttributes,
LPSECURITY ATTRIBUTES lpThreadAttributes,
BOOL blnheritHandles,
DWORD dwCreationFlags,
LPVOID lpEnvironment,
LPCTSTR lpCurrentDirectory,
LPSTARTUPINFO lpStartupInfo,
LPPROCESS INFORMATION lpProcessInformation)`

```c++
#include<iostream>
#include<Windows.h>
using namespace std;

int main()
{
	TCHAR commandline[] = TEXT("C:\\Users\\pengyang\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe");
	_STARTUPINFOW startinfo = { sizeof(_STARTUPINFOW) };
	_PROCESS_INFORMATION processInfo;

	bool ret = CreateProcess(
								NULL,//不指定可执行文件的文件名
								commandline,//命令行参数
								NULL,//默认进程安全性
								NULL,//默认线程安全性
								FALSE,//指定当前进程的句柄是否被子进程继承
								0,//指定附加的、用来控制优先类和进程的创建的标志。，
								NULL,//使用当前进程的环境变量
								NULL,//使用当前进程的驱动和目录
								&startinfo,//指向一个用于觉得心进程主窗体如何显示的结构体
								&processInfo//进程信息结构体
								);
	cout << ret << endl; //1

	if (!ret)
	{
		cout << "进程创建失败" << endl;
		return 0;
	}
	else {
		WaitForSingleObject(processInfo.hProcess, INFINITE);//等待进程句柄
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
		cout << "新创建的进程id：" << processInfo.dwProcessId << endl;
		cout << "新创建的主线程id：" << processInfo.dwThreadId << endl;
	}

	return 0;
}
```

### 2. 进程间通信

#### 通信方式

- **无名管道（ pipe)︰**管道是一种半双工的通信方式，数据只能单向流动，而且只能在具有亲缘关系的进程间使用。进程的亲缘关系通常是指父子进程关系。

- **命名管道(named pipe):**有名管道也是半双工的通信方式，但是它允许无亲缘关系进程间的通信。

- **消息队列( message queue)∶**消息队列是由消息的链表，存放在内核中并由消息队列标识符标识。消息队列克服了信号传递信息少、管道只能承载无格式字节流以及缓冲区大小受限等缺点。

- **互斥量**

- **共享内存(shared memory) ︰**共享内存就是**映射一段能被其他进程所访问的内存，这段共享内存由一个进程创建，但多个进程都可以访问。共享内存是最快的IPC方式，**它是针对其他进程间通信方式运行效率低而专门设计的。它往往与其他通信机制，如信号量，配合使用，来实现进程间的同步和通信。

方法——文件共享

创建共享文件句柄（物理内存）
`HANDLE hMapFile= CreateFileMapping(
	INMALID HANDLE VALUE，//物理文件句柄
	NULL,	//默认安全级别
	PAGE_READWRITE,	//可读可写
	0,	//高位文件大小
	BUF_SIZE,	//低位文件大小
	szName	//共享内存名称
);`

`char*p Buf =(char *)MapViewOfFile(
	hMapFile,	//共享内存的句柄
	FILE MAP ALL ACCESS，//可读写许可
	0,
	0,
	BUF SIZE
);`

`UnmapViewOfFile(pBuf);`

`CloseHandle(hMapFile);`

*Process-send*

```c
#include<stdio.h>
#include<windows.h>

int main()
{
	HANDLE hMapFile = CreateFileMapping(
		NULL,//物理文件句柄
		NULL,//默认映射文件的安全级别
		PAGE_READWRITE,//访问权限
		0,//高位
		128,//低位
		TEXT("fileMap")//共享内存名
	);

	char* buf = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 128);
	gets_s(buf, 100);
	while (1);
	UnmapViewOfFile(buf);
	CloseHandle(hMapFile);

	return 0;
}
```

Process-receive

```c
#include<stdio.h>
#include<windows.h>

int main()
{
	HANDLE hMapFile = CreateFileMapping(
		NULL,//物理文件句柄
		NULL,//默认映射文件的安全级别
		PAGE_READWRITE,//访问权限
		0,//高位 
		128,//低位
		TEXT("fileMap")//共享内存名
	);

	char* buf = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 128);
	printf("%s\n", buf);
	while (1);
	UnmapViewOfFile(buf);
	CloseHandle(hMapFile);

	return 0;
}
```

## 内存管理

#### 进程的虚拟地址空间

32位的CPU的寻址空间是4G，所以虚拟内存的最大值为4G，而windows操作系统把这4G分成2部分，即**3G的用户空间和1G的系统空间**，**系统空间是各个进程所共享的**，他存放的是操作系统及一些内核对象等，**而用户空间是分配给各个进程使用的，用户空间包括用∶程序代码和数据，堆，共享库，栈。**

![image-20221123103419640](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221123103419640.png)

##### 用户空间

用户空间从低向上可分为：
**text段-代码段**
	text段存放程序代码，运行前就已经确定（编译时确定），通常为只读、共享。
**.rodata-只读数据段**
	存放一些只可以读的常量数据比如:被const修饰的全局变量，**被define宏定义的常量，和只可读的字符串常量。**
**.data**
	存放在编译阶段(而非运行时)就能确定的数据,可读可写。也就是通常所说的静态存储区,赋了初值的全局变量和赋初值的静态变量存放在这个区域,常量也存放在这个区域，static声明的变量，不管它是全局变量也好，还是在函数之中的也好，只要是没有赋初值都存在.bss段，如果赋了初值，则把它放在.data段。
**.bss**
	定义而没有赋初值的全局变量和静态变量,放在这个区域;
**heap**
	堆是用于存放进程运行中被动态分配的内存段，它的大小并不固定，可动态扩张或缩减。当进程调用malloc等函数分配内存时，新分配的内存就被动态添加到堆上（堆被扩张);当利用free等函数释放内存时，被释放的内存从堆中被剔除（堆被缩减)。由低向高。
**共享库区域**
	这里被内核用来把文件内容直接映射到内存。所有的应用程序都可以使用linux提供的mmap()系统调用或者在windows中使用CreateFileMapping()/MapViewOfFile来进行这样的映射。memory mapping是进行文件I/O的高效方法，所以动态库的加载使用这个方式来实现。当然，也可以进行一些不关联到文件的程序数据的匿名memory mapping。在linux中，如果你通过malloc()来申请一块大的内存，C库就会在memory mapping segment中创建一个匿名memory mapping而不是使用堆空间。这里的“大“意味着大于MMAP_THRESHOLD字节，默认是128kb,可以通过mallopt()来进行调整。
**stack**
stack段存储参数变量和局部变量，由系统进行申请和释放，属于静态内存分配。由高向低。

## 网络通信

### 1. IP地址

IP地址的分类：A,B,C,D,E五类

![image-20221123134737517](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221123134737517.png)

### 2. 网络模型

1. **OSI7层模型：物数网传会表应**

- 应用层：主要就是应用程序，ftp，ssh，email，http

- 表示层：进行编解码和翻译工作
- 会话层：建立会话和保持会话
- 传输层：定义端到端传输，TCP，UDP协议
- 网络层：定义点到点传输，IP协议，主要设备：路由器
- 数据链路层: 数据校验，定义了数据格式——帧，ARP协议，RARP协议

- 物理层：通信介质——双绞线，光纤，调制解调器modemn（模数转换和数模转换）

2. **TCP四层模型**

- 应用层:对应会话层,表示层和应用层
- 传输层:对应传输层
- 网络层:对应网络层
- 网络接口层:对应于物理层和数据链路层

![image-20221123135400687](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221123135400687.png)

### 3. TCP/IP协议

**IP（网际协议）**是TCP/I P协议族中最为**核心的协议**。所有的TCP、UDP、ICM P及IGMP数据都以**lP数据报格式**传输。

**TCP(Transmission Control Protocol传输控制协议)**是一种**面向连接**(连接导向)的、可靠的、基于IP的传输层协议。TCP在IP报文的协议号是6。

![image-20221123140759311](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221123140759311.png)

**Source Port和Destination Port:**分别占用16位，表示源端口号和目的端口号;用于**区别主机中的不同进程,而IP地址是用来区分不同的主机的**，源端口号和目的端口号配合上IP首部中的源IP地址和目的IP地址就能唯一的确定一个TCP连接;

**Sequence Number:**用来标识从TCP发端向TCP收端发送的数据字节流，它表示在这个报文段中的的第一个数据字节在数据流中的序号;**主要用来解决网络报乱序的问题;**

**Acknowledgment Number:**32位确认序列号包含发送确认的一端所期望收到的下一个序号，因此，确认序号应当是上次已成功收到数据字节序号加1。不过，只有当标志位中的ACK标志(下面介绍)为1时该确认序列号的字段才有效。**主要用来解决不丢包的问题;**

Offset给出首部中32 bit字的数目，需要这个值是因为任选字段的长度是可变的。这个字段占4bit(最多能表示15个32bit的的字，即4*15=60个字节的首部长度)，因此TCP最多有60字节的首部。然而，没有任选字段，正常的长度是20字节;

**TCP Flags:TCP首部中有6个标志比特**，它们中的多个可同时被设置为1，主要是用于操控TCP的状态机的，依次为**URG, ACK，PSH，RST, SYN，FIN**。每个标志位的意思如下:
**URG:**此标志表示TCP包的紧急指域(后面马上就要说到)有效，用来保证TCP连接不被中断，并且督促中间层设备要尽快处理这些数据;
**ACK:**此标志表示应答域有效，就是说前面所说的TCP应答号将会包含在TCP数据包中;有两个取值:0和1，为1的时候表示应答域有效，反之为0;
**PSH:**这个标志位表示Push操作。所谓Push操作就是指在数据包到达接收端以后，立即传送给应用程序，而不是在缓冲区中排队;
**RST:**这个标志表示连接复位请求。用来复位那些产生错误的连接，也被用来拒绝错误和非法的数据包;
**SYN:**表示同步序号，用来建立连接。SYN标志位和ACK标志位搭配使用，当连接请求的时候，SYN=1,ACK=0;连接被响应的时候，SYN=1，ACK=1;这个标志的数据包经常被用来进行端口扫描。扫描者发送―个只有SYN的数据包，如果对方主机响应了一个数据包回来，就表明这台主机存在这个端口;但是由于这种扫描方式只是进行TCP三次握手的第一次握手，因此这种扫描的成功表示被扫描的机器不很安全，一台安全的主机将会强制要求一个连接严格的进行TCP的三次握手;
**FIN:**表示发送端已经达到数据末尾，也就是说双方的数据传送完成，没有数据可以传送了，发送FIN标志位的TCP数据包后，连接将被断开。这个标志的数据包也经常被用于进行端口扫描。

Window:窗口大小，也就是有名的滑动窗口，用来进行流量控制;

#### 三次握手

1. 第一次握手:建立连接。客户端发送连接请求报文段，**将SYN设置为1**，Sequence Number为x;然后，**客户端进入SYN_SEND状态**，等待服务器的确认;

2. 第二次握手:**服务器收到SYN报文段**。服务器收到客户端的SYN报文段，需要对这个SYN报文段进行确认，设置Acknowledgment Number为x+1(Sequence Number+1);同时，自己还要发送SYN请求信息，将SYN位置为1，Sequence Number为y;**服务器端将上述所有信息放到一个报文段(即SYN+ACK报文段)中，一并发送给客户端，此时服务器进入SYN_RECV状态**;

3. 第三次握手:**客户端收到服务器的SYN+ACK报文段**。然后将Acknowledgment Number设置为y+1，**向服务器发送ACK报文段**，这个报文段发送完毕以后，**客户端和服务器端都进入ESTABLISHED状态，完成TCP三次握手**。

   完成了三次握手，客户端和服务器端就可以开始传送数据。

#### 四次挥手

1. 第一次分手:主机1(可以是客户端，也可以是服务器端)，设置Sequence Number和Acknowledgment Number，**向主机2发送一个FIN报文段;此时，主机1进入FIN_WAIT_1状态;**这表示主机1没有数据要发送给主机2了;

2. 第二次分手:**主机2收到了主机1发送的FIN报文段，向主机1回一个ACK报文段**，AcknowledgmentNumber为Sequence Number加1;**主机1进入FIN_WAIT_2状态;主机2告诉主机1**，我也没有数据要发送了，可以进行关闭连接了;

3. 第三次分手:**主机2向主机1发送FIN报文段，请求关闭连接，同时主机2进入CLOSE_WAIT状态;**

4. 第四次分手:**主机1收到主机2发送的FIN报文段，向主机2发送ACK报文段，然后主机1进入TIME_WAIT状态**:主机2收到主机1的ACK报文段以后，就关闭连接;此时，**主机1等待2MSL后依然没有收到回复**，则证明Server端已正常关闭，那好，主机1也可以关闭连接了。

   ![image-20221123143615000](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221123143615000.png)

### TCP与UDP的区别

**TCP---传输控制协议,**提供的是**面向连接、可靠的字节流服务**。当客户端和服务器彼此交换数据前，必须先在双方之间建立一个TCP连接，之后才能传输数据。TCP提供超时重发，丢弃重复数据，检验数据流量控制等功能，故而传输速度慢，保证数据能从一端传到另一端。

**UDP---用户数据报协议**，是一个简单的**面向数据报的运输层协议**。UDP**不提供可靠性**，它只是把应用程序传给IP层的数据报发送出去，但是并不能保证它们能到达目的地。由于UDP在传输数据报前不用在客户端和服务器之间建立一个连接，且没有超时重发等机制，故而传输速度很快。

## 基于TCP的C/S模型

### TCP的服务端/客户端创建

![image-20221124104644517](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221124104644517.png)

### 套接字

Socket(套接字)可以看成是两个网络应用程序进行通信时，各自通信连接中的端点，这是一个逻辑上的概念。进程从网络中接收数据，向网络发送数据都是通过套接字来进行的。socket可以看成是程序访问系统网络组件的接口。

`SOCKET socket(int domain, int type, int protocol);`

**domain:**协议域，又称协议族〔family)。常用的协议族有AI_INET、AF_INLT6、AFT_LOCAL(或称ATI_UNIX, Unixl域Socket)、 AF_ROUTE等。协议族决定了socket的地址类型，在通信中必须采用对应的也址，**如AF_INET决定了要用ipv4地址〔32位的)与端口号(16位的）的组合**、AF_UNIX决定了要用一个绝对路径名作为地址。
**type:**指定Socket类型。常用 的socket类型有SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKFT、SOCKK_SEQPACKET等。**流式Socket(SOCK_STREAM)是一种面向连接的Socket**，**针对于面向连接的TCP服务应用**。数据报式Socket (SOCK_DGRAM)是一种无连接的Socket，对应于无连接的UDP服务应用.
**protocol:**指定协议。常用协议有IPPROTO_TCP、IPPROTO_UDP、IPPROTO_STCP、IPPROTO_TIPC等，分别对应TCP传输协议、UDP传输协议.STCP传输协议、TIPC传输协议。
注意：
1.type和protccol不可以随意组合，如SOCK_STREAM不可以跟IPPROTO_UDP组合。当第三个参数为0时，会自动选择第二个参数类型对应的默认协议。
2.WindowsSocket 下protocol参数中不存在IPPROTO_STCP

### 代码示例

动态库 *SocketInit.hpp*

```c++
#ifndef _SOCKET_INIT_H_
#define _SOCKET_INIT_H_

#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib, "ws2_32.lib")

class SocketInit {
public:
	SocketInit() {	//构造函数
		WORD socketVersion = MAKEWORD(2, 2);
		WSADATA wasData;
		if (WSAStartup(socketVersion, &wasData) != 0) {
			printf("动态链接库加载失败！\n");
		}
	}
	~SocketInit() {	//析构函数
		WSACleanup();
	}
};

#endif // !_SOCKET_INIT_H_

```

*TcpServer*

```c
#pragma warning(disable:4996)
#include<stdio.h>
#include"../SocketInit/SocketInit.hpp"

int main()
{
	SocketInit socketInit;

	//创建服务端监听套接字
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sListen == SOCKET_ERROR) {
		printf("监听套接字创建失败！\n");
		return -1;
	}

	sockaddr_in sock_in;//服务端
	sock_in.sin_family = AF_INET;//协议簇
	sock_in.sin_port = htons(12306);//端口号
	sock_in.sin_addr.S_un.S_addr = INADDR_ANY;//本机ip

	//绑定套接字
	int ret = bind(sListen, (const sockaddr*)&sock_in, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR) {
		printf("绑定套接字失败!\n");
		closesocket(sListen);
		return -1;
	}

	//监听
	if (listen(sListen, 10) == SOCKET_ERROR) {
		printf("监听失败！\n");
		closesocket(sListen);
		return -1;
	}

	//接受客户端连接
	sockaddr_in clientAddr;
	int nlen = sizeof(sockaddr_in);
	SOCKET sClient = accept(sListen, (sockaddr*)&clientAddr, &nlen);
	if (sClient == SOCKET_ERROR) {
		printf("接收客户端失败！\n");
		closesocket(sListen);
		return -1;
	}

	printf("与客户端建立连接...\n");

	while (true) {
		char buff[1024] = { 0 };
		int result = recv(sClient, buff, 1024, 0);
		if (result > 0) {
			printf("接收到的数据： %s\n", buff);
		}
		else {
			printf("客户端断开连接！\n");
			break;
		}

	}
	closesocket(sListen);
	getchar();//保持阻塞状态

	return 0;
}
```

TcpClient

```c
#pragma warning(disable:4996)
#include<stdio.h>
#include"../SocketInit/SocketInit.hpp"

int main()
{
	SocketInit socketInit;

	//创建客户端套接字
	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == SOCKET_ERROR) {
		printf("客户端套接字创建失败！\n");
		return -1;
	}

	sockaddr_in sock_in;//客户端
	sock_in.sin_family = AF_INET;//协议簇
	sock_in.sin_port = htons(12306);//端口号
	sock_in.sin_addr.S_un.S_addr = inet_addr("192.168.128.5");

	//连接服务端
	if (connect(sClient, (const sockaddr*)&sock_in, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		printf("连接服务端失败！\n");
		return -1;
	}

	while (true) {
		char buff[1024] = { 0 };
		gets_s(buff, 1024);
		send(sClient, buff, strlen(buff), 0);

	}
	closesocket(sClient);
	getchar();//保持阻塞状态

	return 0;
}
```



## select 模型实现多客户端连接服务器

#### 多线程方式

基于多线程方式可以实现多客户端连接服务器，**但在实际开发中一般不用**

实现：客户端代码不变，修改服务端代码

*TcpServer*

```c
#pragma warning(disable:4996)
#include<stdio.h>
#include"../SocketInit/SocketInit.hpp"

DWORD WINAPI ThreadProc(LPVOID lp) {
	SOCKET sClient = *(SOCKET*)lp;
	while (true) {
		char buff[1024] = { 0 };
		int result = recv(sClient, buff, 1024, 0);
		if (result > 0) {
			printf("接收到的数据： %s\n", buff);
		}
		else {
			printf("客户端断开连接！\n");
			break;
		}

	}
	return NULL;
}

int main()
{
	SocketInit socketInit;

	//创建服务端监听套接字
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sListen == SOCKET_ERROR) {
		printf("监听套接字创建失败！\n");
		return -1;
	}

	sockaddr_in sock_in;//服务端
	sock_in.sin_family = AF_INET;//协议簇
	sock_in.sin_port = htons(12306);//端口号
	sock_in.sin_addr.S_un.S_addr = INADDR_ANY;//本机ip

	//绑定套接字
	int ret = bind(sListen, (const sockaddr*)&sock_in, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR) {
		printf("绑定套接字失败!\n");
		closesocket(sListen);
		return -1;
	}

	//监听
	if (listen(sListen, 10) == SOCKET_ERROR) {
		printf("监听失败！\n");
		closesocket(sListen);
		return -1;
	}

	sockaddr_in clientAddr;
	int nlen = sizeof(sockaddr_in);
	while (true) {
		//接受客户端连接
		SOCKET sClient = accept(sListen, (sockaddr*)&clientAddr, &nlen);
		if (sClient == SOCKET_ERROR) {
			printf("接收客户端失败！\n");
			closesocket(sListen);
			return -1;
		}

		printf("与客户端建立连接...\n");
		CreateThread(NULL, NULL, ThreadProc, (LPVOID)&sClient, NULL, NULL);//创建多线程
	}

	closesocket(sListen);
	getchar();//保持阻塞状态

	return 0;
}
```

#### select模型

选择（select）模型是Winsock中最常见的I/O模型。核心便是利用select函数。实现对I/O的管理。利用select函数来判断某Socket上是否有数据可读,或者能否向一个套接字写入数据，防止程序在Socket处于阻塞模式中时,在一次I/O调用( send、recv.、accept等）过程中.被迫进入“锁定”状态;可以同时等待多个套接字，当某个或者多个套接字满足可读写条件时，通知应用程序调用输入或者输出函数进行读写。
"select函数返回时,通过移除没有未决I/O操作的套接字句柄修改每个fd_set集合。

select 的函数原型如下:
`int select(
_in 		int nfds,	//第一个参数nfds会被忽略。之所以仍然要提供这个参数，只是为了保持与Berkeley套接字兼容。
_in_out		fd_set* readfds,	//用于检查可读性(readfds）
_in out 	fd set* writefds,	//用于检查可写性(writefds)
_in_out 	fd_set* exceptfds,	//用于例外数据（exceptfds ）
_in			const struct timeval* timeout 	//等待时间)`

#### 代码

TcpClient

```c
#pragma warning(disable:4996)
#include<stdio.h>
#include"../SocketInit/SocketInit.hpp"

int main()
{
	SocketInit socketInit;

	//创建客户端套接字
	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == SOCKET_ERROR) {
		printf("客户端套接字创建失败！\n");
		return -1;
	}

	sockaddr_in sock_in;//客户端
	sock_in.sin_family = AF_INET;//协议簇
	sock_in.sin_port = htons(12306);//端口号
	sock_in.sin_addr.S_un.S_addr = inet_addr("192.168.128.5");

	//连接服务端
	if (connect(sClient, (const sockaddr*)&sock_in, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		printf("连接服务端失败！\n");
		return -1;
	}

	while (true) {
		char buff[1024] = { 0 };
		gets_s(buff, 1024);
		send(sClient, buff, strlen(buff), 0);

	}
	closesocket(sClient);
	getchar();//保持阻塞状态

	return 0;
}
```

TcpServer

```c
#pragma warning(disable:4996)
#include<stdio.h>
#include"../SocketInit/SocketInit.hpp"


int main()
{
	SocketInit socketInit;

	//创建服务端监听套接字
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sListen == SOCKET_ERROR) {
		printf("监听套接字创建失败！\n");
		return -1;
	}

	sockaddr_in sock_in;//服务端
	sock_in.sin_family = AF_INET;//协议簇
	sock_in.sin_port = htons(12306);//端口号
	sock_in.sin_addr.S_un.S_addr = INADDR_ANY;//本机ip

	//绑定套接字
	int ret = bind(sListen, (const sockaddr*)&sock_in, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR) {
		printf("绑定套接字失败!\n");
		closesocket(sListen);
		return -1;
	}

	//监听
	if (listen(sListen, 10) == SOCKET_ERROR) {
		printf("监听失败！\n");
		closesocket(sListen);
		return -1;
	}

	FD_SET fd_read;//存储SOCKET对象
	FD_ZERO(&fd_read);//初始化
	FD_SET(sListen, &fd_read);//监听套接字放入fd数组

	while (true) {
		FD_SET fd_tmp = fd_read; //fd_read备份SOCKET对象
		const timeval tv = { 1, 0 };
		int ret = select(NULL, &fd_tmp, NULL, NULL, &tv);//间隔1s筛选套接字对象
		if (ret == 0) {	//为筛选到则间隔1s继续
			Sleep(0);
			continue;
		}

		for (int i = 0; i < fd_tmp.fd_count; i++) {
			//如果监听到套接字中有网络事件，则证明有客户端在连接服务器
			if (fd_tmp.fd_array[i] == sListen) {
				sockaddr_in clientAddr;
				int nlen = sizeof(sockaddr_in);
				//接受客户端连接
				SOCKET sClient = accept(sListen, (sockaddr*)&clientAddr, &nlen);

				if (sClient == SOCKET_ERROR) {
					printf("接收客户端失败！\n");
					closesocket(sListen);
					return -1;
				}

				printf("与客户端建立连接...%s\n", inet_ntoa(clientAddr.sin_addr));
				FD_SET(sClient, &fd_read);//将已连接的客户端放入集合
			}
			else { //如果客户端套接字有网络事件，则证明客户端在发送数据，服务端在接收数据
				char buff[1024] = { 0 };
				int result = recv(fd_tmp.fd_array[i], buff, 1024, 0);
				if (result > 0) {
					printf("接收到的数据： %s\n", buff);
				}
				else {
					//从fd_read中移除当前SOCKET
					FD_CLR(fd_tmp.fd_array[i], &fd_read);
					printf("客户端断开连接！\n");
					break;
				}
			}
		}
	}

	closesocket(sListen);
	getchar();//保持阻塞状态

	return 0;
}
```



## 项目——网络聊天室

### 多线程实现客户端收发分离

消息信息封装*Messagtype.hpp*

```c++
#pragma once

enum MSG_TYPE
{
	MSG_SHOW,
	MSG_JOIN,
	MSG_CREATE,
	MSG_LEAVE,
	MSG_TALK
};


class MsgHead {	
public:
	int msgType;//消息类型
	int dataLen;//消息长度
};

class MsgShow :public MsgHead{
public:
	MsgShow() {
		msgType = MSG_SHOW;
		dataLen = sizeof(MsgShow);
	}
};

class MsgJoin :public MsgHead {
public:
	int roomId;
	MsgJoin(int r) {
		msgType = MSG_JOIN;
		dataLen = sizeof(MsgJoin);
		roomId = r;
	}
};

class MsgCreate :public MsgHead {
public:
	MsgCreate() {
		msgType = MSG_CREATE;
		dataLen = sizeof(MsgCreate);
	}
};

class MsgLeave :public MsgHead {
public:
	MsgLeave() {
		msgType = MSG_LEAVE;
		dataLen = sizeof(MSG_LEAVE);
	}
};

class MsgTalk:public MsgHead {
	char buff[1000];
public:
	MsgTalk() {
		msgType = MSG_TALK;
		dataLen = sizeof(MsgTalk);
	}

	char* getbuff() {
		return buff;
	}
};
```

客户端*clientmain.cpp*

```c
#pragma warning(disable:4996)
#include<stdio.h>
#include"../SocketInit/SocketInit.hpp"
#include"../MessageType/Messagtype.hpp"

DWORD WINAPI ThreadProc(LPVOID lp) {
	SOCKET sClient = *(SOCKET*)lp;
	printf("show join create talk exit\n");
	while (true) {
		char buff[1024] = { 0 };
		gets_s(buff, 1024);

		if (strcmp(buff, "show") == 0) {
			//显示当前服务器下的聊天室
			MsgShow msgShow;
			send(sClient, (const char*)&msgShow, msgShow.dataLen, 0);

		}else if (strncmp(buff, "join", strlen("join")) == 0) {
			//加入一个聊天室
			int r = atoi(buff + strlen("join"));//解析房间号装换成整型
			MsgJoin msgJoin(r);
			send(sClient, (const char*)&msgJoin, msgJoin.dataLen, 0);

		}else if (strcmp(buff, "create") == 0) {
			//创建一个聊天室

		}else if (strcmp(buff, "talk") == 0) {
			//聊天
			printf("开始聊天\n");
			while (true) {
				MsgTalk msgTalk;
				gets_s(msgTalk.getbuff(), 1000);
				if (strcmp(msgTalk.getbuff(), "leave") == 0) {
					printf("聊天结束\n");
					MsgLeave msgLeave;
					send(sClient, (const char*)&msgLeave, msgLeave.dataLen, 0);
					break;
				}
				send(sClient, (const char*)&msgTalk, msgTalk.dataLen, 0);
			}

		}else if (strcmp(buff, "exit") == 0) {
			break;
		}

	}
	return -1;
}


int main()
{
	SocketInit socketInit;

	//创建客户端套接字
	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == SOCKET_ERROR) {
		printf("客户端套接字创建失败！\n");
		return -1;
	}

	sockaddr_in sock_in;//客户端
	sock_in.sin_family = AF_INET;//协议簇
	sock_in.sin_port = htons(12306);//端口号
	sock_in.sin_addr.S_un.S_addr = inet_addr("192.168.128.5");

	//连接服务端
	if (connect(sClient, (const sockaddr*)&sock_in, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		printf("连接服务端失败！\n");
		return -1;
	}

	//多线程实现数据收发
	//子线程-发数据
	HANDLE h = CreateThread(0, 0, ThreadProc, (LPVOID)&sClient, 0, 0);

	//主线程-收数据
	while (true) {
		char buff[1024] = { 0 };
		gets_s(buff, 1024);
		int ret = recv(sClient, buff, 1024, 0);
		if (ret > 0) {

		}
		else {
			printf("客户端接收数据失败...\n");
			break;
		}

	}

	WaitForSingleObject(h, INFINITE);
	closesocket(sClient);
	getchar();//保持阻塞状态

	return 0;
}
```

服务端*servermain.cpp*

```c
#pragma warning(disable:4996)
#include<stdio.h>
#include"../SocketInit/SocketInit.hpp"
#include"../MessageType/Messagtype.hpp"

void dealWithData(MsgHead* magHead) {//多态
	switch (magHead->msgType)
	{
		case MSG_SHOW:
			printf("显示聊天室\n");
			break;
		case MSG_JOIN:
		{
			MsgJoin* join = (MsgJoin*)magHead;
			printf("加入 %d 聊天室\n", join->roomId);
			break;
		}
		case MSG_CREATE:
			printf("请求创建聊天室\n");
			break;
		case MSG_TALK:
		{
			MsgTalk* talk = (MsgTalk*)magHead;
			printf("%s...\n", talk->getbuff());
			break;
		}
		case MSG_LEAVE:
		{
			printf("离开聊天室\n");
			break;
		}

		default:
			printf("消息解析失败。。。\n");
			break;
	}
}


int main()
{
	SocketInit socketInit;

	//创建服务端监听套接字
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sListen == SOCKET_ERROR) {
		printf("监听套接字创建失败！\n");
		return -1;
	}

	sockaddr_in sock_in;//服务端
	sock_in.sin_family = AF_INET;//协议簇
	sock_in.sin_port = htons(12306);//端口号
	sock_in.sin_addr.S_un.S_addr = INADDR_ANY;//本机ip

	//绑定套接字
	int ret = bind(sListen, (const sockaddr*)&sock_in, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR) {
		printf("绑定套接字失败!\n");
		closesocket(sListen);
		return -1;
	}

	//监听
	if (listen(sListen, 10) == SOCKET_ERROR) {
		printf("监听失败！\n");
		closesocket(sListen);
		return -1;
	}

	FD_SET fd_read;//存储SOCKET对象
	FD_ZERO(&fd_read);//初始化
	FD_SET(sListen, &fd_read);//监听套接字放入fd数组

	while (true) {
		FD_SET fd_tmp = fd_read; //fd_read备份SOCKET对象
		const timeval tv = { 1, 0 };
		int ret = select(NULL, &fd_tmp, NULL, NULL, &tv);//间隔1s筛选套接字对象
		if (ret == 0) {	//为筛选到则间隔1s继续
			Sleep(0);
			continue;
		}

		for (int i = 0; i < fd_tmp.fd_count; i++) {
			//如果监听到套接字中有网络事件，则证明有客户端在连接服务器
			if (fd_tmp.fd_array[i] == sListen) {
				sockaddr_in clientAddr;
				int nlen = sizeof(sockaddr_in);
				//接受客户端连接
				SOCKET sClient = accept(sListen, (sockaddr*)&clientAddr, &nlen);

				if (sClient == SOCKET_ERROR) {
					printf("接收客户端失败！\n");
					closesocket(sListen);
					return -1;
				}

				printf("与客户端建立连接...%s\n", inet_ntoa(clientAddr.sin_addr));
				FD_SET(sClient, &fd_read);//将已连接的客户端放入集合
			}
			else { //如果客户端套接字有网络事件，则证明客户端在发送数据，服务端在接收数据
				char buff[1024] = { 0 };
				int result = recv(fd_tmp.fd_array[i], buff, 1024, 0);
				if (result > 0) {
					//处理客户端发送过来的消息
					dealWithData((MsgHead*) buff);

					//printf("接收到的数据： %s\n", buff);
				}
				else {
					//从fd_read中移除当前SOCKET
					FD_CLR(fd_tmp.fd_array[i], &fd_read);
					printf("客户端断开连接！\n");
					break;
				}
			}
		}

	}

	
	closesocket(sListen);
	getchar();//保持阻塞状态

	return 0;
}
```

客户端和服务端封装
