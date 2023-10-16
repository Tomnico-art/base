C高级编程

## 1. 指针

### 1.1 空指针和野指针

- 野指针的三种情况：
  1. 声明未初始化的指针
  2. malloc后free的指针
  3. 指针变量超出作用域

- 空指针可以重复释放，野指针不能重复释放

```c
int* doWork()
{
	int a = 10;
	int* p = &a;
	return p;
}

void test01()
{
	//1.声明未初始化的指针、
	//int* p1;
	//printf("%d\n", *p1);//错误

	//2.malloc后free的指针
	int* p2 = malloc(sizeof(int));
	*p2 = 100;
	printf("%d\n", *p2);//正确
	free(p2);
	printf("%d\n", *p2);//错误

	//3.指针变量超出作用域
	int* p3 = doWork();
	printf("%d\n", *p3);//错误
}
```

