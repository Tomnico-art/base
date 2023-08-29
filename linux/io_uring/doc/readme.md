
## io_uring原理

使用 read() 和 write() 等系统调用进行 I/O 操作时，会从用户态嵌入到内核态，如下图所示：
![Alt text](image.png)

io_uring 为了减少或者摒弃系统调用，采用了用户态与内核态 共享内存 的方式来通信。如下图所示：
![Alt text](image-1.png)