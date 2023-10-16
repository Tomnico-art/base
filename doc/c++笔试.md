## 1.char *const *(*next)() 请解释该行代码

const char *s 常量指针，指针可以修改，指向的数据由于const的修饰而不可通过指针s去修改
char *const s 指针常量，s是个不可修改的指针，但可通过指针s去修改s所指向的数据

(*next) ----> next是个指针
(*next)() ----> next是个函数指针
char *const ----> 常量指针
char *const *(*next)() next是个函数指针，指向一个没有参数的函数，并且该函数的返回值是一个指针，该指针指向一个类型为char的常量指针。


## 2.char *(*c[10])(int **p)

1.char *pt[10]: pt是数组，数组由10个char *指针所组成。pt是指针数组
2.char (*pt)[10]: pt是指针，pt指针指向10个char元素构成的数组，即pt是数组指针

char *(*c[10])(int **p) c数组每个元素都是函数指针，其所指向的函数返回值是char *类型，且函数带一个指向指针的指针

## 3.字符串常量
    char *pt = "AAA";   //字符串常量存放在只读区域，不能修改值，智能修改指针指向。
    printf("%s\n", pt);

    *pt = 'B';       //段错误
    printf("%s\n", pt);

    pt = "B";           //正确
    printf("%s\n", pt);

## 4. 嵌入式系统经常具有要求程序员去访问某特定的内存位置，要求读取地址的里面的内容或者向该地址写入新值，特别是在嵌入式处理器开发中操作寄存器时这种用法会经常出现。例如在某工程中，要求设置一绝对内存地址为0x40020800的位置，将该地址里面的内容设置为整型值Ox3456。编写代码完成这一任务。

（1）
int *pt;
pt = (unsigned long *)0x40020800
*pt = 0x3456

(2)更好
#define ADDR (*(volatile unsigned long *)0x40020800)
ADDR = 0x3456

## 5.typedef对比#define
#define dPS struct s *
typedef struct s * tPS;
以上两种情况的意图都是要定义dPS和tPS作为一个指向结构s指针。哪种方法更好呢?
 
 (1)定义一个变量时，相同
dPS p1; ------> struct s *p1;
tPS p2; ------> struct s *p2;

(2)
dPS p1, p2 ------> struct s *p1, p2; p1是结构体指针，p2是结构体对象
tPS p3, p4 ------> struct s *p3, *p4; p3,p4是结构体指针

## 6.函数返回局部变量地址的问题

下面的代码有什么问题，如何修改
#include <stdio.h>
char *get_str(void);

int main()
{
    char *p = get_str();
    printf("%s\n", p);

    return 0;
}

char *get_str()
{
    char str[] = {"abcd"};
    return str;
}

问题：局部变量存放在栈空间，函数结束会被释放
解决：1.使用静态变量static char str[] = {"abcd"};
      2.使用字符串常量 char *str = "abcd";


## 7.无符号整数和有符号整数相加

1，在计算机内部，无符号数和有符号数相加，回自动转化成无符号整数
2，整数在计算机内部都是以补码的形式出现 (正数的补码与原码相同，负数的补码是源码取反+1)

    unsigned int a = 6;
    int b = -20;

    printf("a+b = %d\n", a+b); -14
    printf("a+b = %ud\n", a+b); 4294967282d
    
    return 0;

6
补码：0000 0000 0000 0000 0000 0000 0000 0110

-20
原码：1000 0000 0000 0000 0000 0000 0001 0100
反码：1111 1111 1111 1111 1111 1111 1110 1011
补码：1111 1111 1111 1111 1111 1111 1110 1100

0000 0000 0000 0000 0000 0000 0000 0110
1111 1111 1111 1111 1111 1111 1110 1100 +
1111 1111 1111 1111 1111 1111 1111 0010 

## 8.大小端模式的判定
大端模式：数据的低位存放在内存的高地址中，数据的高位存放在内存的低地址中
小端模式：数据的低位存放在内存的低地址中，数据的高位存放在内存的高地址中

## 19.在Linux内核代码(版本2.6.22)中有如下定义:#define offsetof(TYPE，MEMBER) ((size t) &((TYPE*)0)->MEMBER)请尝试解释下上面这行语句的含义。
1）(TYPE*)0:将0强制类型转换为TPYE类型的指针，p = (TYPE *)0
2) ((TYPE *)0)->MEMBER ---> p->MEMBER ---> 访问MEMBER成员变量
3) &((TYPE*)0)->MEMBER:取出MEMBER成员变量的地址
4) (size t)&((TYPE*)0)->MEMBER: size_t相当于类型转换，将MEMBER成员变量的地址转换为size_t类型的数据，size_t== int

总结:该宏的作用就是求出MEMBER成员变量在TYPE中的偏移量

## 64位系统和32位系统字节对齐问题
64位ubantu系统默认8字节对齐，32位系统默认4字节对齐

## 21.const关键字作用
1.const定义一个常量，这个常量必须在定义时初始化，否则后面就没机会了
2.实际上const定义的变量并不是一个真正的常量，
3
char const *s
const char *s :两者相同，常量指针，指针可以修改，指向的数据由于const的修饰而不可通过指针s去修改
char *const s 指针常量，s是个不可修改的指针，但可通过指针s去修改s所指向的数据

4.const修饰形参，避免参数在函数内部被修改
int add(const int *pt1, const int *pt2) 


## 33.定义一个空的类，对该类求sizeof，得到的结果是多少
结果1(字节)