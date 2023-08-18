gcc pthread_shared.c -o pthread_shared -m32 -Wall -g -lpthread
gcc read_write_lock.c -o read_write_lock -m32 -Wall -g -lpthread


## 线程与锁
线程同步：一个线程发出某一功能调用时，在没得到结果之前，该调用不返回，同时其他线程为保证数据的一致性，不能调用该功能

### 数据混乱的原因:

   资源共享

   调度随机

   线程之间缺乏必要的同步机制

### 互斥量

   linux提供一把互斥锁**mutex**（互斥量）

   对资源操作先加锁，结束再解锁

   资源还是共享的，线程间还是竞争的，但是错误不再产生


### 使用互斥锁的一般步骤
    1. pthread_mutex_t lock 创建锁
    2. pthread_mutex_init   初始化
    3. pthread_mutex_lock   加锁
    4. 访问共享数据
    5. pthread_mutex_unlock 解锁
    6. pthread_mutex_destroy    销毁锁

    注意事项：**尽量保证锁的粒度，越小越好（访问共享数据前加锁，访问结束立即解锁）**
            互斥锁，本质是结构体，可以看成整数，初值为1（pthread_mutex_init()调用成功）
            加锁：--操作
            解锁：++操作
            try锁：尝试加锁，成功--， 失败返回错误号ebusy

### 死锁
   1. 
