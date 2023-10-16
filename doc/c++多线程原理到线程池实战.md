c++多线程原理到线程池实战

## 1 为什么使用多线程

- 任务分解
  - 耗时的操作，任务分解，实时响应
- 数据分解
  - 充分利用多核CPU处理数据，
  - 例如音视频处理，图像处理，加解密算法
- 数据流分解
  - 读写分离，解耦合设计
  - 设计模式角度：读写分离

### 1.1 第一个多线程实例

```c++
#include<thread>
#include<iostream>
using namespace std;

void ThreadMain() {
	cout << "begin sub thread main " << this_thread::get_id() << endl;
	for (int i = 0; i < 10; i++) {
		cout << "in thread " << i << endl;
		this_thread::sleep_for(chrono::seconds(1));//1s
	}
	cout << "end sub thread main " << this_thread::get_id() << endl;
}

//创建进程，包含一个主线程
int main()
{
	cout << "main thread ID " << this_thread::get_id() << endl;
	//线程创建启动
	thread th(ThreadMain);
	cout << "begin wait sub thread " << endl;
	//阻塞等待子线程退出
	th.join();
	cout << "end wait sub thread " << endl;
	
	return 0;
}
```

### 1.2 线程等待和分离

```c++
#include<thread>
#include<iostream>
using namespace std;

bool is_exit = false;

void ThreadMain() {
	cout << "begin sub thread main " << this_thread::get_id() << endl;
	for (int i = 0; i < 10; i++) {
		if (!is_exit)
			break;
		cout << "in thread " << i << endl;
		this_thread::sleep_for(chrono::seconds(1));//1s
	}
	cout << "end sub thread main " << this_thread::get_id() << endl;
}

//创建进程，包含一个主线程
int main()
{
	{
		//thread th(ThreadMain); //出错，thread对象被销毁，子线程还在运行
	}
	{
		thread th(ThreadMain);
		th.detach();//子线程与主线程分离，守护线程
					//坑：主线程退出后，子线程不一定退出
	}
	{
		thread th(ThreadMain);
		this_thread::sleep_for(chrono::seconds(1));
		is_exit = true;//通知子线程退出
		cout << "主线程阻塞，等待子线程退出" << endl;
		th.join();	//主线程阻塞，等待子线程退出
		cout << "子线程已退出" << endl;
	}
	getchar();

	return 0;
}
```

