## 0 C++ 核心编程

### 0.1 内存分区模型

C++程序在执行时，将内存大方向划分为4个区域

- 代码区︰存放函数体的二进制代码，由操作系统进行管理的。

- 全局区:存放全局变量和静态变量以及常量

- 栈区:由编译器自动分配释放,存放函数的参数值,局部变量等

- 堆区:由程序员分配和释放,若程序员不释放,程序结束时由操作系统回收

  

内存四区意义:
不同区域存放的数据，赋予不同的生命周期,给我们更大的灵活编程

#### 0.1.1 程序运行前

在程序编译后，生成了exe可执行程序，未执行该程序前分为两个区域

**代码区:**
	存放CPU执行的机器指令Ⅰ

​	**代码区是共享的**，共享的目的是对于频繁被执行的程序，只需要在内存中有一份代码即可

​	**代码区是只读的**，使其只读的原因是防止程序意外地修改了它的指令
**全局区:**
​	**全局变量和静态变量**存放在此.

​	**全局区还包含了常量区**,字符串常量和其他常量也存放在此.

​	**该区域的数据在程序结束后由操作系统释放**



#### 0.1.2 程序运行后

**栈区:**
	由编译器自动分配释放,存放函数的参数值,局部变量等

​	注意事项:**不要返回局部变量的地址**，栈区开辟的数据由编译器自动释放

**堆区：**

​	由程序员分配释放,若程序员不释放,程序结束时由操作系统回收

​	在C++中主要利用**new**在堆区开辟内存



指针的本质也是局部变量，放在栈区，指针保存的数据放在堆区

![image-20221117105416388](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221117105416388.png)

### 0.2 指针

#### 0.2.1 const修饰指针

const修饰指针有3种情况

```c++
int a = 10;
int b = 20;

//1.const修饰指针-- - 常量指针
//指针指向可以改，指针指向的值不可以更改
const int* p1 = &a;
p1 = &b;	//正确
*p1 = 100;	//错误

//2.const修饰常量-- - 指针常量
//指针指向不可以改，指针指向的值可以更改
int * const p2 = &a;
p2 = &b;	//错误
*p2 = 100;	//正确

//3.const即修饰指针，又修饰常量
//指针指向和指针指向的值都不可以改
const int* const p3 = &a;
p3 = &b;	//错误
*p3 = 100;	//错误
```

 



## 1 对象和类

面向对象三大特性：**封装，继承，多态**

### 1.1 封装

#### 1.1.1 访问权限

封装的意义一:

- 将属性和行为作为一个整体，表现生活中的事物

- 将属性和行为加以权限控制

封装的意义二：

类在设计时，可以把属性和行为放在不同的权限下，加以控制

访问权限有三种:

1. public 公共权限					 ——类内可以访问，类外可以访问

2. protected 保护权限              ——类内可以访问，类外不可以访问             在继承中，子类可以访问父类的保护内容
3. private 私有权限                   ——类内可以访问，类外不可以访问             在继承中，子类不可以访问父类的私有内容

#### 1.1.2 struct和class的区别

在C++中struct和class唯—的区别就在于默认的**访问权限不同**
区别:

- struct默认权限为公共. 

- class默认权限为私有

```c++
class C1
{
    int A;	//默认权限为私有
};

struct C2
{
    int A;	//默认权限为公共
};
```



### 1.2 对象特性

#### 1.2.1 构造函数和析构函数

对象的**初始化和清理**也是两个非常重要的安全问题，—个对象或者变量没有初始状态，对其使用后果是未知，同样的使用完一个对象或变量，没有及时清理，也会造成—定的安全问题

C++利用了**构造函数和析构函数**解决上述问题，这两个函数将会被编译器自动调用，完成对象初始化和清理工作。对象的初始化和清理工作是编译器强制要我们做的事情，因此**如果不提供构造和析构，编译器会提供编译器提供的构造函数和析构函数是空实现。**

- 构造函数:主要作用在于创建对象时为对象的成员属性赋值，构造函数由编译器自动调用，无须手动调用。

- 析构函数:主要作用在于对象销毁前系统自动调用，执行一些清理工作。



构造函数语法：`类名(){}`

1. 构造函数，没有返回值也不写void
2. 函数名称与类名相同
3. 构造函数可以有参数，因此可以发生重载
4. 程序在调用对象时候会自动调用构造，无须手动调用,而且只会调用一次



析构函数语法：`~类名(){}`

1. 析构函数，没有返回值也不写void
2. 函数名称与类名相同,在名称前加上符号~
3. 析构函数不可以有参数，因此不可以发生重载
4. 程序在对象销毁前会自动调用析构，无须手动调用,而且只会调用—次



#### 1.2.2 构造函数的分类和调用

两种分类方式:

- 按参数分为:有参构造和无参构造

- 按类型分为:普通构造和拷贝构造

三种调用方式:

- 括号法

- 显式法

- 隐式转换法

```c++
class Person {
public:
	int age;
public:
	//无参（默认）构造函数
	Person() {
		cout << "无参构造函数！" << endl;
	}
	//有参构造函数
	Person(int a) {
		age = a;
		cout << "无参构造函数！" << endl;
	}
	//拷贝构造函数
	Person(const Person& p) {
		age = p.age;
		cout << "无参构造函数！" << endl;
	}
	//析构函数
	~Person();
};

void test01()
{
	//1、括号法
	Person p1;	//调用默认构造函数
	Person p2(10);	//调用有参构造函数
	Person p3(p2);	//调用拷贝构造函数

	//注意事项：调用默认构造函数时，不要加()，因为下面这行代码，编译器会认为是函数声明，不会认为是在创建对象
	Person p1()

	//2.显式法
	Person p1;
	Person p2 = Person(10);
	Person p3 = Person(p2);

	//注意事项：
	Person(10)	//匿名对象，特点：当前行执行结束后，系统会立即回收掉匿名对象
	Person(p3)	//不要利用拷贝构造函数初始化匿名对象编译器会认为Person (p3) === Person p3;

	//3、隐式转换法
	Person p4 = 10;		//相当于写了Person p4 = Person(10); 有参构造
	Person p5 = p4;		//拷贝构造
}
```



#### 1.2.3 拷贝构造函数的调用时机

C++中拷贝构造函数调用时机通常有三种情况

- 使用一个已经创建完毕的对象来初始化一个新对象
- 值传递的方式给函数参数传值
- 以值方式返回局部对象



#### 1.2 4 构造函数的调用规则

默认情况下，c++编译器至少给一个类添加3个函数

1. 默认构造函数(无参，函数体为空)

2. 默认析构函数(无参，函数体为空)

3. 默认拷贝构造函数，对属性进行值拷贝

   

构造函数调用规则如下:

- 如果用户定义有参构造函数，c++不在提供默认无参构造，但是会提供默认拷贝构造
- 如果用户定义拷贝构造函数，C++不会再提供其他构造函数



#### 1.2.5 深拷贝与浅拷贝

- 浅拷贝：简单的赋值拷贝操作
- 深拷贝：在堆区重新申请空间，进行拷贝操作

浅拷贝带来的问题：堆区内存重复释放

![image-20221116133406235](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221116133406235.png)

利用深拷贝解决浅拷贝带来的问题

![image-20221116133509897](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221116133509897.png)



```c++
#include<iostream>
using namespace std;

class Person {
public:
	int* m_Height;
	int m_age;
public:
	//无参（默认）构造函数
	Person() {
		cout << "无参构造函数！" << endl;
	}
	//有参构造函数
	Person(int age, int height) {
		cout << "有参构造函数！" << endl;
		m_age = age;
		m_Height = new int(height);
	}
	//拷贝构造函数
	Person(const Person& p) {
		cout << "拷贝构造函数！" << endl;
		//如果不利用深拷贝在堆区创建新的内存，会导致浅拷贝带来的重复释放堆区的问题
		m_age = p.m_age;
		m_Height = new int(*p.m_Height);
	}
	//析构函数
	~Person() {
		cout << "析构函数！" << endl;
		if (m_Height != NULL) {		
			delete m_Height;
		}
	}
};

void test01()
{
	Person p1(18, 170);
	Person p2(p1);

	cout << "p1的年龄：" << p1.m_age << " 身高：" << *p1.m_Height << endl;
	cout << "p2的年龄：" << p2.m_age << " 身高：" << *p2.m_Height << endl;
}

int main()
{
	test01();

	return 0;
}
```

**总结:如果属性有在堆区开辟的，一定要自己构造拷贝构造函数，防止浅拷贝带来的问题。**



#### 1.2.6 初始化列表

语法：`构造函数():属性1(值1),属性2(值2),属性3(值3)...{}`

```c++
class Person {
public:
    int m_A;
    int m_B;
    int m_C;
public:
    Person(int a, int b, int c) :m_A(a), m_B(b), m_C(c)
    {

    }
};
```

#### 1.2.7 类对象作为类成员

C++类中的成员可以是另—个类的对象，我们称该成员为对象成员

构造的顺序是：先调用对象成员的构造，再调用本类构造

析构顺序与构造相反，先析构本类

#### 1.2.8 静态成员

静态成员就是在成员变量和成员函数前加上关键字static，称为静态成员

静态成员分为:

- 静态成员变量
  - 所有对象共享同一份数据
  - **在编译阶段分配内存。**
  - 类内声明，类外初始化

- 静态成员函数
  - 所有对象共享同一个函数
  - 静态成员函数只能访问静态成员变量



```c++
class Person {
public:
	static int m_A;	//静态成员变量
};

int Person::m_A = 10;	//类外初始化

void test01()
{
	//静态成员变量的两种访问方式
	//1、通过对象
	Person p1;
	cout << p1.m_A << endl;	//10
	p1.m_A = 100;
	cout << p1.m_A << endl;	//100

	//共享同一份数据
	Person p2;
	cout << p2.m_A << endl;	//100
	p2.m_A = 200;
	cout << p2.m_A << endl;	//200

	//2、通过类名
	cout << Person::m_A << endl;	//200
}
```



```c++
class Person {
public:
	static void func()
	{
		m_A = 100;	//静态成员函数可以访问静态成员变量
		m_B = 100;	//错误，不可以访问非静态成员变量
	}

	static int m_A;	//静态成员变量
	int m_B;	//非静态成员变量
};
```



#### 1.2.9 成员变量和成员函数

在C++中，类内的成员变量和成员函数分开存储

**只有非静态成员变量才属于类的对象上**

```c++
class Person {
	int m_A;				//非静态成员变量，属于类的对象上
	static int m_B;			//静态成员变量，不属于类的对象上
	void func(){}			//非静态成员函数，不属于类的对象上
	static void func2(){}	//静态成员函数，不属于类的对象上
};
```



```c++
class Person {

};

void test01()
{
	Person p;
	//空对象占用内存空间为:1
	//C++编译器会给每个空对象也分配一个字节空间，是为了区分空对象占内存的位置
	//每个空对象也应该有一个独一无二的内存地址
	cout << "size of p = " << sizeof(p) << endl;	//1
}
```



#### 1.2.10 this指针

我们知道在C++中成员变量和成员函数是分开存储的
每一个非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用一块代码那么问题是:这—块代码是如何区分那个对象调用自己的呢?
C++通过提供特殊的对象指针，this指针，解决上述问题。**this指针指向被调用的成员函数所属的对象**
this指针是隐含每一个非静态成员函数内的一种指针
this指针不需要定义，直接使用即可

**this指针的用途:**

- 当形参和成员变量同名时，可用this指针来区分
- 在类的非静态成员函数中返回对象本身，可使用return *this

```c++
class Person
{
public:
	int age;

	Person(int age)
	{
        //当形参和成员变量同名时，可用this指针来区分
		this->age = age;
	}

	Person& PersonAddPerson(Person p)
	{
		this->age += p.age;
        //返回对象本身，可使用return *this
		return *this;
	}
};
```



#### 1.2.11 空指针访问成员函数

C++中空指针可以调用成员函数，但是要注意有没有用到this指针

```c++
#include<iostream>
using namespace std;

class Person
{
public:
	int age;

	//空指针可以调用
	void showClassName()
	{
		cout << "this is Person class" << endl;
	}

	//空指针不能调用
	void showPersonAge()
	{
		cout << this->age << endl;
	}
};
```



#### 1.2.12 const修饰成员函数

常函数:

- 成员函数后加const后我们称为这个函数为常函数

- 常函数内不可以修改成员属性

- 成员属性声明时加关键字mutable后，在常函数中依然可以修改

  

常对象:

- 声明对象前加const称该对象为常对象
- 常对象只能调用常函数



#### 1.2.13 友元

生活中你的家有客厅(Public)，有你的卧室(Private)
客厅所有来的客人都可以进去，但是你的卧室是私有的，也就是说只有你能进去但是呢，你也可以允许你的好闺蜜好基友进去。
在程序里，**有些私有属性也想让类外特殊的一些函数或者类进行访问，就需要用到友元的技术**
友元的目的就是让一个函数或者类访问另一个类中私有成员
友元的关键字为**friend**

友元的三种实现

- 全局函数做友元
- 类做友元
- 成员函数做友元



**全局函数做友元**

```c++
class Building
{
	friend void goodGay(Building* building);
public:
	Building()
	{
		this->m_SittingRoom;
		this->m_BedRoom;
	}

public:
	string m_SittingRoom;
private:
	string m_BedRoom;
};

void goodGay(Building* building) 
{
	cout << "好基友正在访问：" << building->m_SittingRoom << endl;
	cout << "好基友正在访问：" << building->m_BedRoom<< endl;
}
```



### 1.3 运算符重载

运算符重载的概念：对已有的运算符重新定义，以适应不同(自定义)数据类型的运算

#### 1.3.1 加号运算符重载

1. 成员函数重载加号

   ```c++
   class Person
   {
   public:
   	//1、成员函数重载+号
   	Person operator+(Person& p)
   	{
   		Person temp;
   		temp.m_A = this->m_A + p.m_A;
   		temp.m_B = this->m_B + p.m_B;
   		return temp;
   	}
   
   	int m_A;
   	int m_B;
   };
   
   void test01()
   {
   	Person p1;
   	p1.m_A = 10;
   	p1.m_B = 20;
   	Person p2;
   	p2.m_A = 30;
   	p2.m_B = 40;
   
   	////成员函数重载的本质调用
   	//Person p3 = p1.operator+(p2);
   
   	//简化调用
   	Person p3 = p1 + p2;
   }
   ```

2. 全局函数重载+号

   ```c++
   class Person
   {
   public:
   	int m_A;
   	int m_B;
   };
   
   //2、全局函数重载+号
   Person operator+(Person& p1,Person& p2)
   {
   	Person temp;
   	temp.m_A = p1.m_A + p2.m_A;
   	temp.m_B = p1.m_B + p2.m_B;
   	return temp;
   }
   
   //函数重载
   Person operator+(Person& p1, int num)
   {
   	Person temp;
   	temp.m_A = p1.m_A + num;
   	temp.m_B = p1.m_B + num;
   	return temp;
   }
   
   void test01()
   {
   	Person p1;
   	p1.m_A = 10;
   	p1.m_B = 20;
   	Person p2;
   	p2.m_A = 30;
   	p2.m_B = 40;
   
   	////全局函数重载本质调用
   	//Person p3 = operator+(p1, p2);
   
   	//简化调用
   	Person p3 = p1 + p2;
   
   	//运算符重载，也可以发生函数重载
   	Person p4 = p1 + 100;
   }
   ```

   **注意：**不可以改变内置的数据类型的表达式的运算符

#### 1.3.2 左移运算符重载

作用：输出自定义数据类型

```c++
#include<iostream>
using namespace std;

class Person
{
public:
	int m_A;
	int m_B;
};

//智能利用全局函数重载左移运算符
ostream& operator<<(ostream& out, Person& p)
{
	cout << "m_A = " << p.m_A << " m_B = " << p.m_B;
	return cout;
}

void test01()
{
	Person p1;
	p1.m_A = 10;
	p1.m_B = 20;
	cout << p1;
}

int main()
{
	test01();
}
```

### 1.4 继承

#### 1.4.1 继承基本语法

`class A:public B;`

A为子类或派生类，B为父类或基类

#### 1.4.2 继承方式

- 公共继承
- 保护继承
- 私有继承

![image-20221119101846136](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221119101846136.png)

#### 1.4.3 继承中的对象模型

```c++
class Base
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son :public Base
{
public:
	int m_D;
};

void test01()
{
	//父类中所有非静态成员属性都会被子类继承下去
	//父类中私有成员属性是被编译器给隐藏了，因此是访问不到，但是确实被继承下去了
	cout << "sizeof Son = " << sizeof(Son) << endl;	//16
}
```

#### 1.4.4 继承中构造与析构的顺序

继承中先调用父类构造函数，再调用子类构造函数，析构顺序与构造相反，先调用子类构造函数，再调用父类构造函数

#### 1.4.5 同名成员处理

1. 子类对象可以直接访问到子类中同名成员
2. 子类对象加作用域可以访问到父类同名成员
3. 当子类与父类拥有同名的成员函数，子类会隐藏父类中同名成员函数，加作用域可以访问到父类中同名函数

```c++
class Base
{
public:
	Base()
	{
		m_A = 100;
	}

	void func()
	{
		cout << "Base-func() 调用" << endl;
	}

	void func(int a)
	{
		cout << "Base-func(int a) 调用" << endl;
	}

public:
	int m_A;
};

class Son :public Base
{
public:
	Son()
	{
		m_A = 200;
	}

	void func()
	{
		cout << "Son-func() 调用" << endl;
	}

public:
	int m_A;
};

void test01()
{
	Son s;
	cout << "Son下的m_A = " << s.m_A << endl;	//200
	cout << "Base下的m_A = " << s.Base::m_A << endl;	//100

	s.func();	//Son - func() 调用
	s.Base::func();		//Base - func() 调用
	s.Base::func(10);	//Base - func(int a) 调用
}
```

#### 1.4.6 多继承语法

C++允许一个类继承多个类
语法: `class 子类︰继承方式 父类1，继承方式 父类2...`
**多继承可能会引发父类中有同名成员出现，需要加作用域区分**



### 1.5 多态

#### 1.5.1 多态的基本概念

**多态是C++面向对象三大特性之一**

多态分为两类

- 静态多态:函数重载和运算符重载属于静态多态，**复用函数名**
- 动态多态:派生类和虚函数实现运行时多态

静态多态和动态多态区别:

- 静态多态的函数地址早绑定–编译阶段确定函数地址
- 动态多态的函数地址晚绑定–运行阶段确定函数地址

多态的好处：

符合开闭原则：对扩展进行开放，对修改进行关闭

动态多态演示

```c++
#include<iostream>
using namespace std;

class Animal {
public:
	//函数前面加上virtual关键字，变成虚函数，那么编译器在编译的时候就不能确定函数调用了。
	virtual void speak() {
		cout << "动物在说话。\n" << endl;
	}
};

class Cat:public Animal {
public:
    //多态实现：重写父类函数，函数的返回值类型，函数名，参数列表完全相同
	void speak() {
		cout << "小猫在说话。\n" << endl;
	}
};

/*
多态满足的条件：
	1.有继承关系
	2.子类重写父类中的虚函数
		重写—函数返回值类型，参数列表， 函数名完全一致
多态的使用：
	父类指针或引用指向子类对象
*/

void DoSpeak(Animal& animal) {
	animal.speak();
}

void test01() {
	Cat cat;
	DoSpeak(cat);
}

int main()
{
	test01();//小猫在说话
	return 0;
}
```

**多态满足的条件：**
	1.有继承关系
	2.子类重写父类中的虚函数
		重写—函数返回值类型，参数列表， 函数名完全一致
**多态的使用：**
	父类指针或引用指向子类对象

#### 1.5.2 多态的原理剖析

![image-20221126140917529](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221126140917529.png)

#### 1.5.3 多态的好处

利用多态实现计算器
多态好处:
/ /1、组织结构清晰/ /2、可读性强
/ /3、对于前期和后期扩展以及维护性高

```c++
#include<iostream>
using namespace std;

//普通实现
class Calculator
{
public:
	int getResult(string oper)
	{
		if (oper == "+") {
			return m_Num1 + m_Num2;
		}
		else if(oper == "-") {
			return m_Num1 - m_Num2;
		}
		else if (oper == "*") {
			return m_Num1 * m_Num2;
		}
		//如果提供新的运算，需要修改源码，不符合 开闭原则：对修改进行关闭，对扩展进行开放
	}
public:
	int m_Num1;
	int m_Num2;
};

//多态实现
//优点：代码组织结构清晰，可读性强，利于后期扩展和维护
//抽象计算器类
class AbstractCaculator
{
public:
	virtual int getResult() {
		return 0;
	}

	int m_Num1;
	int m_Num2;
};

//加法计算器
class AddCalculator:public AbstractCaculator
{
public:
	int getResult() {
		return m_Num1 + m_Num2;
	}
};

//减法计算器
class SubCalculator :public AbstractCaculator
{
public:
	int getResult() {
		return m_Num1 - m_Num2;
	}
};

int main()
{
	//多态的使用
	//父类指针或者引用指向子类对象
	AbstractCaculator* abc = new AddCalculator;
	abc->m_Num1 = 100;
	abc->m_Num2 = 100;
	cout << abc->getResult() << endl;
	delete abc;	//堆区数据，用完后销毁

	return 0;
}
```



#### 1.5.4 纯虚函数和抽象类

在多态中，通常父类中虚函数的实现是毫无意义的，主要都是调用子类重写的内容，**因此可以将虚函数改为纯虚函数**

纯虚函数语法:`virtual 返回值类型 函数名 (参数列表)=0 ;`
当类中有了纯虚函数，这个类也称为**抽象类**

抽象类特点:

- 无法实例化对象
- **子类必须重写抽象类中的纯虚函数**，否则也属于抽象类

```c++
class Base {
public:
	virtual void func() = 0;//纯虚函数
};
```

#### 1.5.5 虚析构与纯虚析构

多态使用时，如果**子类中有属性开辟到堆区**，那么父类指针在释放时无法调用到子类的析构代码
解决方式:将父类中的**析构函数改为虚析构或者纯虚析构**

虚析构和纯虚析构共性:

- **可以解决父类指针释放子类对象**
- 都需要有具体的函数实现

虚析构和纯虚析构区别:如果是纯虚析构，该类属于抽象类，无法实例化对象

虚析构语法: 
	`virtual ~类名(){}`
纯虚析构语法:
	`virtual ~类名()= 0;`
	`类名::~类名(){}`

**总结:**
	1.虚析构或纯虚析构就是用来解决通过父类指针释放子类对象
	2.如果子类中没有**堆区数据**，可以不写为虚析构或纯虚析构
	3.拥有纯虚析构函数的类也属于抽象类





## 2. 模板

### 2.1 模板的概念

- C++一种编程思想称为**泛型编程**，主要利用的技术就是模板

- C++提供两种模板机制:**函数模板**和**类模板**

  

### 2.2 函数模板

#### 2.2.1 函数模板的基本语法

函数模板作用:
建立一个通用函数，其函数返回值类型和形参类型可以不具体制定，用一**个虚拟的类型**来代表。
语法:

```c++
template<typename T>
函数声明或定义
```

解释:
template ---声明创建模板

typename ---表面其后面的符号是一种数据类型，可以用class代替

T---通用的数据类型，名称可以替换，通常为大写字母

```c++
//函数模板
#include<iostream>
using namespace std;

template<typename T>
void mySwap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

int main()
{
	int a = 10, b = 20;
	//两种方式使用函数模板
	//1.自动类型推导
	//mySwap(a, b);

	//2.显示指定类型
	mySwap<int>(a, b);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	return 0;
}
```

#### 2.2.2 函数模板注意事项
注意事项:

- 自动类型推导，必须推导出—致的数据类型T,才可以使用

  ```c++
  void test01()
  {
  	int a = 10;
  	int b = 20;
  	char c = 'c';
  	mySwap(a, b);	//正确
  	mySwap(a, c);	//错误，推导不出一致的T类型
  }
  ```

- 模板必须要确定出T的数据类型，才可以使用

  ```c++
  template<class T>
  void func()
  {
  	cout << "func调用" << endl;
  }
  
  void test02()
  {
  	func()			//错误，无法推导出T的类型
  	func<int>();	//正确
  }
  ```

  

#### 2.2.3 普通函数与函数模板的区别

1. 普通函数调用时可以发生自动类型转换(隐式类型转换)

2. 函数模板调用时，如果利用自动类型推导，不会发生隐式类型转换

3. 如果利用显示指定类型的方式，可以发生隐式类型转换

```c++
//普通函数
int myAdd01(int a, int b)
{
	return a + b;
}

//函数模板
template<class T>
T myAdd02(T a, T b)
{
	return a + b;
}

void test03()
{
	int a = 10;
	int b = 20;
	char c = 'c';

	myAdd01(a, c);	//正确，发生自动类型转换(隐式类型转换)
	myAdd02(a, c);	//错误，不会发生隐式类型转换
	myAdd02<int>(a, c);		//正确，显示指定类型的方式，可以发生隐式类型转换
}
```

#### 2.2.4 调用规则

1. 如果函数模板和普通函数都可以实现，优先调用普通函数
2. 可以通过空模板参数列表来强制调用函数模板
3. 函数模板也可以发生重载
4. 如果函数模板可以产生更好的匹配,优先调用函数模板

```c++
void myPrint(int a, int b)
{
	cout << "调用普通函数" << endl;
}

template<class T>
void myPrint(T a, T b)
{
	cout << "调用模板函数" << endl;
}

template<class T>
void myPrint(T a, T b，T c)
{
	cout << "调用重载模板" << endl;
}

void test01()
{
	int a = 10;
	int b = 20;
	int c = 30;

	myPrint<>(a, b);	//通过空模板参数列表来强制调用函数模板

	myPrint(a, b, c);	//函数模板也可以发生重载

	char c1 = 'a';
	char c2 = 'b';
	myPrint(c1, c2);	//函数模板可以产生更好的匹配,优先调用函数模板
}
```

### 2.3 类模板

#### 2.3.1 类模板的基本语法

类模板与函数模板的语法相似，在声明模板template后面加类，此类称为类模板

```c++
#include<iostream>
using namespace std;

//类模板
template<class NameType, class AgeType>
class Person
{
public:
	NameType mName;
	AgeType mAge;
public:
	//构造器
	Person(NameType name, AgeType age)
	{
		this->mName = name;
		this->mAge = age;
	}
	void showPerson()
	{
		cout << "name: " << this->mName << " age: " << this->mAge << endl;
	}
};

void test01()
{
	Person<string, int>P1("张三", 999);
	P1.showPerson();
}

int main()
{
	test01();

	return 0;
}
```

#### 2.3.2 类模板与函数模板的区别

类模板与函数模板区别主要有两点:

1. 类模板没有自动类型推导的使用方式

   ```c++
   void test01()
   {
   	Person<string, int>P1("张三", 999);	//正确
   	Person P1("张三", 999);	//错误，无法自动推导
   }
   ```

2. 类模板在模板参数列表中可以有默认参数

   ```c++
   template<class NameType, class AgeType = int>
   
   void test01()
   {
   	Person<string>P1("张三", 999);	//正确
   }
   
   ```



#### 2.3.3 类模板成员函数创建时机

类模板中成员函数和普通类中成员函数创建时机是有区别的:

- **普通类**中的成员函数**—开始就可以创建**

- **类模板**中的成员函数在**调用时才创建**

  

#### 2.3.4 类模板对象作函数参数

—共有三种传入方式:

1. 指定传入的类型---直接显示对象的数据类型

   ```c++
   //1.指定参数类型
   void printPerson1(Person<string, int>& p)
   {
   	p.showPerson();
   }
   
   void test01()
   {
   	Person<string, int>p("张三", 999);
   	printPerson1(p);
   }
   ```

   

2. 参数模板---将对象中的参数变为模板进行传递

   ```c++
   //2.参数模板化
   template<class T1, class T2>
   void printPerson2(Person<T1, T2>& p)
   {
   	p.showPerson();
   	//查看模板推导出的类型
   	cout << "T1的类型为： " << typeid(T1).name() << endl;
   	cout << "T2的类型为： " << typeid(T2).name() << endl;
   }
   
   void test02()
   {
   	Person<string, int>p("李四", 100);
   	printPerson2(p);
   }
   ```

   

3. 整个类模板化---将这个对象类型模板化进行传递

   ```c++
   //3.将整个类模板化
   template<class T>
   void printPerson3(T& p)
   {
   	p.showPerson();
   	//查看模板推导出的类型
   	cout << "T的类型为： " << typeid(T).name() << endl;
   }
   
   void test03()
   {
   	Person<string, int>p("王五", 101);
   	printPerson3(p);
   }
   ```

   

#### 2.3.5 类模板与继承

当类模板碰到继承时，需要注意一下几点:

- 当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中T的类型

- 如果不指定，编译器无法给子类分配内存

- 如果想灵活指定出父类中T的类型，子类也需变为类模板

  ```c++
  //类模板的继承
  template<class T>
  class Base
  {
  	T m;
  };
  
  //class Son:public Base	//错误
  class Son1 :public Base<int>
  {
  
  };
  
  //如果想灵活指定父类中T类型，子类也需要变为类模板
  template<class T1, class T2>
  class Son2 :public Base<T2>
  {
  	T1 obj;
  };
  ```



#### 2.3.6 类模板成员函数类外实现

- 类模中成员函数类外实现时，需要加上模板参数列表

  ```c++
  //类模板
  template<class NameType, class AgeType>
  class Person
  {
  public:
  	NameType mName;
  	AgeType mAge;
  public:
  	//构造器
  	Person(NameType name, AgeType age);
  	//成员函数
  	void showPerson();
  };
  
  //构造函数的类外实现
  template<class NameType, class AgeType>
  Person<NameType, AgeType>::Person(NameType name, AgeType age)
  {
  	this->mName = name;
  	this->mAge = age;
  }
  
  //成员函数类外实现
  template<class NameType, class AgeType>
  void Person<NameType, AgeType>::showPerson()
  {
  	cout << "name: " << this->mName << " age: " << this->mAge << endl;
  }
  ```

  

#### 2.3.7  类模板分文件编写

问题:

- 类模板中成员函数创建时机是在调用阶段，导致分文件编写时链接不到

解决:

- 解决方式1:直接包含.cpp源文件
- 解决方式2∶将声明和实现写到同一个文件中，并更改**后缀名为.hpp**，hpp是约定的名称，并不是强制

*person.hpp*

```c++
#pragma once
#include<iostream>
#include<string>
using namespace std;

//类模板
template<class NameType, class AgeType>
class Person
{
public:
	NameType mName;
	AgeType mAge;
public:
	//构造器
	Person(NameType name, AgeType age);
	//成员函数
	void showPerson();
};

//构造函数的类外实现
template<class NameType, class AgeType>
Person<NameType, AgeType>::Person(NameType name, AgeType age)
{
	this->mName = name;
	this->mAge = age;
}

//成员函数类外实现
template<class NameType, class AgeType>
void Person<NameType, AgeType>::showPerson()
{
	cout << "name: " << this->mName << " age: " << this->mAge << endl;
}
```

```c++
#include<iostream>
#include<string>
using namespace std;

//解决方式一：包含cpp源文件
//#include "person.h"
//#include "person.cpp"

//解决方式二：将声明和实现写到一起，文件后缀名改为.hpp
#include "person.hpp"

void test01()
{
	Person<string, int>p1("张三", 100);
	p1.showPerson();
}

int main()
{
	test01();
}
```



## 3 STL

### 3.1 STL介绍

#### 3.1.1 STL的诞生

- 长久以来，软件界一直希望建立—种可重复利用的东西
- C++的**面向对象**和**泛型编程**思想，目的就是**复用性的提升**
- 大多情况下，数据结构和算法都未能有一套标准,导致被迫从事大量重复工作·
- 为了建立数据结构和算法的一套标准,诞生了**STL**

#### 3.1.2 STL基本概念

- STL(Standard Template Library,标准模板库)
- STL从广义上分为:容器(container)算法(algorithm)迭代器(iterator)
- 容器和算法之间通过迭代器进行无缝连接。
- STL几乎所有的代码都采用了模板类或者模板函数

####  3.1.3 STL六大组件

STL大体分为六大组件，分别是:**容器、算法、迭代器、仿函数、适配器(配接器)、空间配置器**

1. 容器:各种数据结构，如vector、list、deque、set、map等,用来存放数据。
2. 算法:各种常用的算法，如sort、find、copy、for_each等
3. 迭代器:扮演了容器与算法之间的胶合剂。
4. 仿函数:行为类似函数，可作为算法的某种策略。
5. 适配器:一种用来修饰容器或者仿函数或迭代器接口的东西。
6. 空间配置器:负责空间的配置与管理。

#### 3.1.4 STL中容器、算法、迭代器

**容器:** 置物之所也
**STL容器就是将运用最广泛的一些数据结构实现出来**

常用的数据结构:数组,链表,树,栈,队列,集合,映射表等

这些容器分为**序列式容器和关联式容器**两种:

- 序列式容器:强调值的排序，序列式容器中的每个元素均有固定的位置。

- 关联式容器:二叉树结构，各元素之间没有严格的物理上的顺序关系

  

**算法:** 问题之解法也
有限的步骤，解决逻辑或数学上的问题，这一门学科我们叫做算法(Algorithms)

算法分为:**质变算法和非质变算法**。

质变算法:是指运算过程中会更改区间内的元素的内容。例如拷贝，替换，删除等等

非质变算法:是指运算过程中不会更改区间内的元素内容，例如查找、计数、遍历、寻找极值等等



**迭代器:** 容器和算法之间粘合剂
提供一种方法，使之能够依序寻访某个容器所含的各个元素，而又无需暴露该容器的内部表示方式。

每个容器都有自己专属的迭代器

迭代器使用非常类似于指针，初学阶段我们可以先理解迭代器为指针



#### 3.1.5 容器算法迭代器

STL中最常用的容器为Vector，可以理解为数组，下面我们将学习如何向这个容器中插入数据、并遍历这个容器

容器：`vector`

算法：`for_each`

迭代器：`vector<int>::iterator`

```c++
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void myPrint(int val)
{
	cout << val << endl;
}

void test01() {
	//创建容器
	vector<int> v;

	//插入数据
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);

	//通过迭代器访问容器中的数据
	vector<int>::iterator itBegin = v.begin();	//起始迭代器，指向容器中第一个元素
	vector<int>::iterator itEnd = v.end();	//结束迭代器，指向容器中最后一个元素的下一个位置

	//第一种遍历方式
	while (itBegin != itEnd)
	{
		cout << *itBegin << endl;
		itBegin++;
	}

	//第二种遍历方式
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}

	//第三种遍历方式，利用STL提供的遍历算法
	for_each(v.begin(), v.end(), myPrint);
}

int main()
{
	test01();
}
```

#### 3.1.6 vector存放自定义数据类型

```c++
#include<iostream>
#include<vector>
using namespace std;

class Person {
public:
	Person(string name, int age)
	{
		mName = name;
		mAge = age;
	}
public:
	string mName;
	int mAge;
};

//存放对象
void test01()
{
	vector<Person> v;

	Person p1("aaa", 1);
	Person p2("bbb", 2);
	Person p3("ccc", 3);
	Person p4("ddd", 4);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);

	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "Name: " << (*it).mName << " Age: " << (*it).mAge << endl;
	}
}

//存放对象指针
void test02()
{
	vector<Person*> v;

	Person p1("aaa", 4);
	Person p2("bbb", 3);
	Person p3("ccc", 2);
	Person p4("ddd", 1);

	v.push_back(&p1);
	v.push_back(&p2);
	v.push_back(&p3);
	v.push_back(&p4);

	for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
	{
		Person* p = (*it);
		cout << "Name: " << p->mName << " Age: " << (*it)->mAge << endl;
	}
}

int main()
{
	test01();
	test02();
}
```

#### 3.1.7 容器嵌套容器

```c++
#include<iostream>
#include<vector>
using namespace std;

void test01()
{
	vector< vector<int>> v;

	//先创建小容器
	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;

	//插入数据
	for (int i = 0; i < 4; i++)
	{
		v1.push_back(i + 1);
		v2.push_back(i + 2);
		v3.push_back(i + 3);
		v4.push_back(i + 4);
	}

	//将小容器数据插入到大容器中
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v4);

	//遍历数据
	for (vector < vector<int>>::iterator it = v.begin(); it != v.end(); it++)
	{
		for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)
		{
			cout << *vit << " ";
		}
		cout << endl;
	}
}

int main()
{
	test01();
}
```

### 3.2 string容器

#### 3.2.1 string基本概念

本质：

- string是C++风格的字符串，而string本质上是一个类

string和char*区别:

- char *是一个指针*
- *string是一个类，类内部封装了char*，管理这个字符串，是一个char*型的容器。*

特点:

- string类内部封装了很多成员方法
- 例如:查找find，拷贝copy，删除delete替换replace，插入insert
- string管理char*所分配的内存，不用担心复制越界和取值越界等，由类内部进行负责

#### 3.1.2 string构造函数

构造函数原型：

- string();	                           创建一个空字符，例如：string str;
- string(const char* s);          使用字符串s初始化
- string(const string& str);     使用一个str对象初始化另一个str对象
- string(int n, char c);            使用n个字符c初始化 

```c++
#include<string>

void test01()
{
	//创建空字符串，调用无参构造函数
	string s1;

	//把const_string转换成string
	const char* str = "hello world";
	string s2(str);

	//调用拷贝构造函数
	string s3(s2);

	//使用n个字符初始化
	string s4(10, 'a');
}
```



### 3.3 vector 容器

#### 3.3.1 vector容器的基本概念

- 功能: vector数据结构和数组非常相似，也称为单端数组
- vector与普通数组区别: 不同之处在于数组是静态空间，而vector可以动态扩展
- 动态扩展:并不是在原空间之后续接新空间，而是找更大的内存空间，然后将原数据拷贝新空间，释放原空间

![image-20221119214314731](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221119214314731.png)

#### 3.3.2 构造函数

函数原型:
`vector<T> v;`										//采用模板实现类实现，默认构造函数
`vector(v.begin( ), v.end( )) ;`		//将v[begin(), end())区间中的元素拷贝给本身。
`vector(n,elem) ;`						  		 //构造函数将n个elem拷贝给本身。
`vector(const vector &vec) ;`				//拷贝构造函数。

#### 3.3.3 赋值操作

函数原型:
`vector& operator=(const vector &vec);`		//重载等号操作符
`assign(beg, end) ;`		//将[beg, end)区间中的数据拷贝赋值给本身。
`assign(n,elem);`			//将n个elem拷贝赋值给本身。

#### 3.3.4 容量和大小

函数原型:
`empty( ) ;`			//判断容器是否为空
`capacity();`			//容器的容量
`size();`			//返回容器中元素的个数
`resize(int num);`			//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
`resize(int num，elem);`		//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除

#### 3.3.5 插入和删除

函数原型:
`push_back(ele);`		//尾部插入元素ele
`pop_back();`		//删除最后一个元素
`insert(const_iterator pos, ele);`		//迭代器指向位置pos插入元素ele
`insert(const_iterator pos, int count,ele);`		//迭代器指向位置pos插入count个元素ele 
`erase(const_iterator pos);`		//删除迭代器指向的元素
`erase(const_iterator start, const_iterator end);`		//删除迭代器从start到end之间的元素
`clear();`		//删除容器中所有元素

#### 3.3.6 数据存取

`at(int idx) ;`		//返回索引idx所指的数据
`operator[];`		//返回索引idx所指的数据
`front();`		//返回容器中第一个数据元素
`back();`		//返回容器[中最后一个数据元素

#### 3.3.7 互换容器

`swap(vec);`		//实现两个容器内的元素互换

```c++
void test01()
{
	vector<int> v1;
	for (int i = 0; i < 100000; i++)
	{
		v1.push_back(i);
	}
	cout << "v1的容量为：" << v1.capacity() << endl;	//138255
	cout << "v1的大小为：" << v1.size() << endl;	//100000

	v1.resize(3);
	cout << "v1的容量为：" << v1.capacity() << endl;	//138255
	cout << "v1的大小为：" << v1.size() << endl;	//3

	//收缩内存
	vector<int>(v1).swap(v1);//匿名对象
	cout << "v1的容量为：" << v1.capacity() << endl;	//3
	cout << "v1的大小为：" << v1.size() << endl;	//3
}
```

#### 3.3.8 预留空间

功能：减少vector在动态扩展容量时的扩展次数

`reserve(int len);`		//容器预留len个元素长度，预留位置不初始化，元素不可访问。

```c++
void test01()
{
	vector<int> v;
	v.reserve(100000);

	int num = 0;
	int* p = NULL;
	for (int i = 0; i < 100000; i++)
	{
		v.push_back(i);
		if (p != &v[0])
		{
			p = &v[0];
			num++;
		}
	}

	cout << "num = " << num << endl;	//未预留空间前，动态扩展30次
}
```

### 3.4 deque容器

#### 3.4.1 deque容器的基本概念

功能：双端数组，可以对头端进行插入删除操作

dequen与vector的区别：

- vector对于头部的插入删除效率低，数据量越大，效率越低
- deque相对而言,对头部的插入删除速度回比vector快
- vector访问元素时的速度会比deque快,这和两者内部实现有关

![image-20221120143730103](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221120143730103.png)

deque内部工作原理:
deque内部有个中控器，维护每段缓冲区中的内容，缓冲区中存放真实数据
中控器维护的是每个缓冲区的地址，使得使用deque时像一片连续的内存空间

![image-20221120143854380](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20221120143854380.png)

#### 3.4.2 deque中的构造函数

函数原型：

- `deque<T> deqT;`			//默认构造形式
- `deque(beg, end) ;`		//构造函数将[beg, end)区间中的元素拷贝给本身。
- `deque(n,elem);`			//构造函数将n个elem拷贝给本身。
- `deque(const deque &deq);`		//拷贝构造函数

```c++
void printDeque(const deque<int>& d)
{
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	deque<int> d1;
	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}
	printDeque(d1);

	deque<int> d2(d1.begin(), d1.end());
	printDeque(d2);

	deque<int>d3(10, 100);


	deque<int> d4 = d2;
	printDeque(d4);
}
```

#### 3.4.3 赋值操作

函数原型：
`deque& operator=(const deque &deq);`		//重载等号操作符
`assign(beg，end);`		//将[beg, end)区间中的数据拷贝赋值给本身。
`assign(n，elem);`		l/将n个elem拷贝赋值给本身。

#### 3.4.5 容量和大小

`deque.empty( ) ;`		//判断容器是否为空
`deque.size();`			 //返回容器中元素的个数
`deque.resize(num);`		//重新指定容器的长度为num,若容器变长，则以默认值填充新位置。//如果容器变短，则末尾超出容器长度的元素被删除。
`deque.resize(num，elem);`		//重新指定容器的长度为num,若容器变长，则以elem值填充新位置。//如果容器变短，则末尾超出容器长度的元素被删除。

**deque没有容量的概念**

#### 3.4.6 插入和删除

函数原型:

- 两端插入操作:
  `push_back(elem);`		//在容器尾部添加一个数据
  `push_front(elem) ;`		//在容器头部插入一个数据
  `pop_back();`				  //删除容器最后一个数据
  `pop_front();`				//删除容器第一个数据
- 指定位置操作:
  `insert(pos,elem);`	        //在pos位置插入一个elem元素的拷贝，返回新数据的位置。
  `insert(pos,n,elem); `        //在pos位置插入n个elem数据，无返回值。
  `insert(pos,beg,end); `      //在pos位置插入[beg,end)区间的数据，无返回值。
  `clear(); `                          //清空容器的所有数据
  `erase(beg,end); `           //删除[beg,end)区间的数据，返回下一个数据的位置。
  `erase(pos); `                 //删除pos位置的数据，返回下一个数据的位置。

#### 3.4.7 deque数据存取

函数原型;
`at(int idx);`		//返回索引idx所指的数据
`operator[];`		//返回索idx所指的数据
`front();`			 //返回容器中第一个数据元素
`back();`			//返回容器中最后—个数据元素

#### 3.4.8 排序操作

`sort(iterator beg,iterator end)`		//对beg和end区间内元素进行排序

### 3.5 stack容器

概念: stack是一种先进后出(First ln Last Out,FILO)的数据结构，它只有一个出口

常用接口：

- 构造函数:
  stack<T> stk;		//stack采用模板类实现, stack对象的默认构造形式
  stack(const stack &stk);          //拷贝构造函数

- 赋值操作:
  stack& operator=(const stack &stk);          //重载等号操作符
- 数据存取:
  push(elem);            //向栈顶添加元素
  pop();                     //从栈顶移除第一个元素
  top();                      //返回栈顶元素
- 大小操作:
  empty();                 //判断堆栈是否为空
  size();                    //返回栈的大小

### 3.7 list容器

#### 3.7.1 基本概念

功能:将数据进行链式存储
链表（list)是一种物理存储单元上非连续的存储结构，数据元素的逻辑顺序是通过链表中的指针链接实现的
链表的组成:链表由—系列结点组成
结点的组成:一个是存储数据元素的**数据域**，另一个是存储下一个结点地址的**指针域**
**STL中的链表是一个双向循环链表**

![image-20230204113539786](C:\Users\pengyang\AppData\Roaming\Typora\typora-user-images\image-20230204113539786.png)

由于链表的存储方式并不是连续的内存空间，因此链表list中的迭代器只支持前移和后移，属于双向迭代器
list的优点:

- 采用动态存储分配，不会造成内存浪费和溢出
- 链表执行插入和删除操作十分方便，修改指针即可，不需要移动大量元素

list的缺点:

- 链表灵活，但是空间(指针域)和时间(遍历)额外耗费较大

List有一个重要的性质，插入操作和删除操作都不会造成原有list迭代器的失效，这在vector是不成立的。

**总结:STL中List和vector是两个最常被使用的容器**，各有优缺点。



### 3.8 set 容器

set基本概念简介:所有元素都会在插入时**自动被排序**

本质:set/multiset属于关联式容器，底层结构是用**二叉树实现**。

set和multiset区别:

- set不允许容器中有重复的元素
- multiset允许容器中有重复的元素

#### 3.8.5 set查找和统计

功能描述:

- 对set容器进行查找数据以及统计数据

函数原型;

- `find(key);`	//查找key是否存在,若存在，返回该键的元素的迭代器;若不存在，返回set.end();
- `count( key ) ;`	//统计key的元素个数



### 3.9 map容器

#### 3.9.1 map基本概念

简介:

- map中所有元素都是**pair**
- pair中第一个元素为**key** (键值)，起到索引作用，第二个元素为**value** (实值)
- 所有元素都会根据元素的键值**自动排序**

本质:

- map/multimap属于关联式容器，底层结构是用二叉树实现。

优点:

- 可以根据key值快速找到value值

map和multimap区别:

- map不允许容器中有**重复key值元素**. 
- multimap允许容器中有重复key值元素

#### 3.9.2 map构造和赋值

功能描述:

- 对map容器进行构造和赋值操作

函数原型:
构造:

- map<T1，T2> mp;	//map默认构造函数:
- map( const map &mp) ;  //拷贝构造函数

赋值:

- map& operator=(const map &mp);	//重载等号操作符

```c++
void printMap(map<int, int>&m)
{
	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}
	cout << endl;
}

void test01()
{
	map<int, int>m;//默认构造
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(3, 10));
	m.insert(pair<int, int>(2, 10));
	printMap(m);

	map<int, int>m2(m);//拷贝构造
	printMap(m2);

	map<int, int>m3;//复制
	m3 = m2;
	printMap(m3);
}
```

