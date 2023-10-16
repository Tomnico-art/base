## 1.面向对象程序设计

面向对象设计主要就是使用UML的类图，类图用于描述系统中所包含的类以及它们之间的相互关系，帮助人们简化对系统的理解，它是**系统分析和设计阶段的重要产物**，也是系统编码和测试的重要模型依据。
## 2.类的UML画法
**类(Class）封装了数据和行为，是面向对象的重要组成部分，它是具有相同属性、操作、关系的对象集合的总称**。在系统中，每个类都具有一定的职责，职责指的是类要完成什么样子的功能，要承担什么样子的义务。一个类可以有多种职责，但是设计得好的类一般只有一种职责。

假设定义一个类：

```c++
class Person
{
public:
	string getName() {
		return name;
	}
	void setName(string name) {
		this->name = name;
	}
protected:
	void playBasketball() {
		pass();
	}
private:
	void pass() {
	}
private:
	string name = "jack";
};
```

此类对应的UML为：

![image-20230217144542392](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230217144542392.png)

看到该图分为三层:**最顶层的为类名，中间层的为属性，最底层的为方法。**

## 3.继承关系

### 3.1 普通继承关系

```c++
class Student :public Person
{
public:
	void study(){}
private:
	string studentNo;
};

class Teacher :public Person
{
public:
	void teach() {}
private:
	string teacherNo;
};
```

此类对应的UML为：

![image-20230217152557046](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230217152557046.png)

### 3.2 抽象继承关系

上面的继承是普通的继承，在C++中，除了普通的继承之外，众所周知的还有一种抽象的继承关系，因此就再讲讲抽象继承关系，作为上面的继承的补充。

比方说我想实现一个链表（Link)，插入 (insert)与删除（remove)动作我想让子类去实现，链表本身只实现统计链表中元素个数的动作(count)，**然后有一个子类单向链表（OneWayLink)去实现父类没有实现的动作**，C++代码为:

```c++
//抽象类（含有纯虚函数的类）
class Link
{
public:
	virtual void insert() = 0;
	virtual void remove() = 0;

	int count() {
		return 0;
	}
};

//子类
class OneWayLink :public Link 
{
public:
	void insert(){}//实现纯虚函数
	void remove(){}
};
```

此类对应的UML为：

![image-20230217153256597](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230217153256597.png)

## 4.关联关系

关联(Assocition)关系是类与类之间最常见的一种关系，它是一种结构化的关系，**表示一类对象与另一类对象之间有联系**，如汽车和轮胎、师傅和徒弟、班级和学生等。在UML类图中，用实线连接有关联关系的对象所对应的类，在C++中通常将一个类的对象作为另一个类的成员变量。关联关系分**单向关联、双向关联、自关联**，逐一看一下。

### 4.1 单向关联关系

单向关联指的是关联只有一个方向，比如顾客(Customer）拥有地址(Address)，其代码实现为:

```c++
//地址类
class Address 
{

};

//顾客类
class Customer 
{
private:
	Address address;	//作为成员变量
};
```

此类对应的UML为：

![image-20230217153522221](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230217153522221.png)









### 4.2 双向关联关系

默认情况下的关联都是双向的，比如顾客（Customer）购买商品（Product)，反之，卖出去的商品总是与某个顾客与之相关联，这就是双向关联。c++类的写法为:

```c++
//商品类
class Product
{
private:
	Customer customer;	//该商品属于哪一位顾客，作为成员变量
};

//顾客类
class Customer
{
private:
	Product product[64];	//给顾客购买了哪些商品，作为成员变量
};
```

此类对应的UML为：

![](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230217154100381.png)

### 4.3 自关联关系

自关联，指的就是对象中的属性为对象本身，这在链表中非常常见，单向链表Node中会维护一个它的前驱Node，双向链表Node中会维护一个它的前驱Node和一个它的后继Node。就以单向链表为例，它的C++写法为:

```c++
//链表节点
class Node
{
private:
	Node* nextNode;
};
```

此类对应的UML为：

![image-20230217154911986](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230217154911986.png)

## 5.聚合关系

**聚合(Aggregation)关系**表示整体与部分的关系。在聚合关系中，成员对象是整体的一部分，但是成员对象可以脱离整体对象独立存在。在UML中，**聚合关系用带空心菱形**的直线表示,I如汽车(Car)与引擎(Engine)、轮胎（Wheel) 、车灯(Light) , C++表示为:

```c++
class Engine
{
};

class Wheel
{
};

class Light
{
};

class Car
{
public:
	Car(Engine engine, Light light, Wheel wheel) {
		this->engine = engine;
		this->light = light;
		this->wheel = wheel;
	}
	void drive() {

	}
private:
	Engine engine;
	Light light;
	Wheel wheel;
};
```

此类对应的UML为：

![image-20230218131836969](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230218131836969.png)

## 6.组合关系

**组合(Composition）关系**也表示的是一种整体和部分的关系，但是在组合关系中整体对象可以控制成员对象的生命周期，一旦整体对象不存在，成员对象也不存在，**整体对象和成员对象之间具有同生共死的关系**。在UML中组合关系用带实心菱形的直线表示。

比如人的头(Head)和嘴巴(Mouth)、鼻子(Nose)，嘴巴和鼻子是头的组成部分之一，一旦头没了，嘴巴也没了，因此头和嘴巴、鼻子是组合关系，C++表示为;

![image-20230218132002115](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230218132002115.png)

## 7.依赖关系