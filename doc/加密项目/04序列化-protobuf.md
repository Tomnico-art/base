## 1.序列化

序列化(Serialization)将**对象的状态信息转换为可以存储或传输的形式的过程**，与之相对应的过程称之为反序列化(Unserialization)。序列化和反序列化主要用于解决在**跨平台和跨语言的情况下**,模块之间的交互和调用,但**其本质是为了解决数据传输问题**。
实现数据序列化:

- 要有原始数据
  - 复合类型>最常见的情况。
  - 基础数据类型
- 通过某些方式→另外—种形式的数据
- 得到的数据干啥?→目的:进行分发,分发到不同的终端/平台,保证不同的平台能正确解析
  - 网络传输
  - 磁盘拷贝
    <font color="red">序列化目的不是为了加密,为的是数据的跨平台传输</font>

序列化的整体过程:

- 发送端
  - 原始数据→>序列化→特殊格式的字符串。
  - 发送这个字符串
- 接收端:
  - 接收数据
  - 特殊格式的字符串->反序列化>原始数据。
  - 对原始数据进行处理

### 1.1 网络通信中的问题分析

发送过程中遇到的问题？

- 平台不同
  - 32bit / 64bit
    - long、
  - 平台不同,某些数据类型占用的内存大小不同·
- 如果不是字符串,需要进行字节序转换
  - 字符串没有字节序问题,字符在内存中只占一个字节。
  - 如果发送的是结构体
  - 大小端问题

- 语言不同
  - 语言不同数据类型占用的内存有可能不同
    - c -> char -> 1字节
    - java -> char -> 2字节

- 字节序对齐问题

### 1.2 常用的序列化方式

	1. XML ( Extensible Markup Language）类似于html
XML是一种常用的序列化和反序列化协议，具有跨机器，跨语言等优点。XML历史悠久，其1.0版本早在1998年就形成标准，并被广泛使用至今。
XML的最初产生目标是对互联网文档进行标记，所以它的设计理念中就包含了对于人和机器都具备可读性。但是，当这种标记文档的设计被用来序列化对象的时候，就显得冗长而复杂。
XML基本格式:

```xml
<?xml version="1.0" encoding="utf-8"?>
<Library>
	<Type name="小说">
		<Book author="J.K.ROWLING" price=" 12$">哈利波特1</Book>
		<Book author="J.K.ROWLING" price="12$">哈利波特2</Book>
		<Book author="J.K.ROWLING" price="12$">哈利波特3</Book>
		<Book author="J.K.ROWLING" price="12$">哈利波特4</Book>
    </Type>
	<Type name="历史">
		<Book author="司马迁” price="28$”>史记</Book></Type>
</Library>

```

2. Json(JavaScript Object Notation)

   JSON起源于弱类型语言Javascript，它的产生来自于一种称之为"关联数组(Associative array)"的概念,其本质是就是采用**"键值对”**的方式来描述对象。
   JSON格式保持了XML的人眼可读的优点,非常符合工程师对对象的理解。
   相对于XML而言，**序列化后的数据更加简洁**(XML所产生序列化之后文件的大小接近ISON的两倍)，而且其协议比较简单,解析速度比较快
   JSON格式具备Javascript的先天性支持，所以被广泛应用于Web browser的应用常景中，是Ajax的事实标准协议。

3. Protocol Buffer
4. ASN.1抽象语法标记(Abstract Syntax Notation One)
5. boost序列化的类
