#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdarg.h>
#include <stdexcept>
#include <fstream>

using namespace std;

#include "Student.h"
#include "Plane.h"
#include "PlaneA.h"


//FFMPEG

//MediaInfo,YUVPlayer,libgif

/*

//类型转换
//static_cast//普通情况
//const_cast;//去常量转换
//dynamic_cast;//子类类型转父类类型
//reinterpret_cast;//函数指针转换，不具备移植性




void* fun(int type)
{
	switch (type)
	{
	case 1:
	{
		int i = 1;
		return &i;
	}
		
	case 2:
	{
		char a = 'a';
		return &a;
	}
		
	default:
		return NULL;
	}
}



int main()
{
	//int a = 2;
	//double b = a;
	//cout << b << endl;
	//double c = 800.3;
	//int d = c;
	//int e = static_cast<int>(c);

	//cout << d << endl;

	char* c = (char*)fun(2);
	char* d = static_cast<char*>(fun(2));
	cout << *c << "," << *d << endl;
	system("pause");
}





*/



/*

//自定义异常

class NullPointException : public exception
{
public:
	NullPointException(const char* e) : exception(e) {
	}
};



//异常

//throw (char*)表示函数可能会抛出的异常类型
int main() throw (char*){

	try
	{

		throw NullPointException("空指针异常");
		if (1)
		{
			throw "发生异常";

		}
		else
		{
			//抛出标准异常
			throw out_of_range("越界异常");
		}

		
		
	}
	catch (char* e)
	{
		cout << e << endl;
	}
	catch (int x)
	{
		cout << x << endl;
	}

	catch (NullPointException n)
	{
		cout << n.what() << endl;
	}
	
	catch (...)
	{
		cout << "发生未知异常" << endl;
	}
	catch (const std::exception&)
	{
		cout << "发生未知异常" << endl;
	}

	system("pause");
	
}

*/


/*

//模板类
template<class T>
class A
{
public:
	A(T a)
	{
		this->a = a;
	}
public:
	T a;
};

//继承模板类
class B : public A<int>
{
public:
	B(int b) : A<int>(b)
	{
		
	}
};

int main()
{
	A<int> a(1);
	cout << a.a << endl;
	system("pause");
}


*/

/*

//函数模板（泛型）

//泛型：业务逻辑一样，数据类型不一样

template <typename T>
void myswap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

int main() {

	int a = 10;
	int b = 20;
	myswap(a,b);
	cout << a << "," << b << endl;
	system("pause");
}


//接口：只是逻辑上的划分，语法上跟抽象类没有任何区别
//接口和抽象类的作用：为了继承的约束性，根本不知道未来的实现
class Drawable {
	virtual void draw() = 0;
};

*/

/*
//抽象类（有纯虚函数的类成为抽象类）
//子类继承时，必须实现父类的虚函数

class Shape {
	
public:
	//纯虚函数
	virtual void sayArea() = 0;
};

class Circle : public Shape {
public:
	Circle(int r) {
		this->r = r;
	}

	void sayArea() {
		cout << "计算圆的面积" << endl;
	
	}

private:
	int r;
};

int main() {
	Circle c(10);
	system("pause");
}
*/

/*

//多态：程序扩展性
//静态多态：重载
//动态多态：程序运行过程中，决定哪一个函数被调用（重写）
//发生多态的条件：1.继承 2.父类的引用或指针指向子类对象 3.重写

//虚函数:使用虚函数实现多态

void print(Planes &p) {

	p.fly();
	p.land();
}
 
int main() {

	Planes ps;
	print(ps);

	PlaneA pa;
	print(pa);
	system("pause");
}


*/


/*

//多继承的二义性
//虚继承：不同路径继承来的成员只有一份拷贝，解决多继承二义性问题

class A 
{
public:
	char* name;
};


class A1 : virtual public A {};
class A2 : virtual public A {};

class B : public A1, public A2 {

};

int main() {

	B b;
	//通过虚继承解决二义性问题
	b.name = (char*)"lucy";
}

*/

/*

//继承:程序复用性
class A {
private:
	int a;
	char* name;
public:
	A(char* name,int a) {
		cout << "A()" << endl;
	}
	void sayHi() {
	
		cout << "hello world" << endl;
	}

};

class B : public A {

public: 

	//构造函数传参及构造函数属性初始化列表
	B(char* name,char* a_name,int a_a) : A(name, 1), a(a_name,a_a) {

		
		cout << "B()" << endl;
	}

	//和父类方法同名
	void sayHi() {
	
		cout << "hello I am B" << endl;
	}

private:
	A a;
	
};

int main() {

	B b((char*)"Rosy",(char*)"Lucy",21);
	
	b.sayHi();
	//调用父类同名方法
	b.A::sayHi();
	system("pause");
}

*/

/*


//运算符重载（属性共有），当属性私有时，通过友元函数完成
class Point {

public:
	int x;
	int y;

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Point operator+(Point p) {
		Point temp(this->x + p.x,this->y + p.y);
		return temp;
	}

};

int main() {
	Point p1(10,20);
	Point p2(20, 10);
	Point p3 = p1 + p2;
	cout << p3.x << "," << p3.y << endl;
	system("pause");
}
*/
/*
//友元函数：

class A {
	//友元类B可以访问A类任何资源
	friend class B;
private:
	int i;
public:
	A(int i) {
		this->i = i;
	}

	void print() {
		cout << i << endl;
	}

	//友元函数的声明
	friend void func(A* p, int x);

};

//友元函数的实现
void func(A* p, int x) {

	p->i = x;
}

//友元类
class B {

	void accessA() {
		a.i = 10;
	}
private:
	A a;

};

int main() {

	A* a = new A(10);
	a->print();
	func(a, 20);//通过友元函数修改私有变量i的值
	a->print();

	system("pause");
}

*/

//常函数：修饰的是this
//既不能改变指针的值，也不能改变指针指向的地址
//const Person* const this;//指针常量和常量指针
/*

常量对象只能调用常量函数
void fun() const
{
//里面的任何对象都不能修改
}
*/

/*
//静态属性和静态方法
class Person {

public:
	static int count;

public:
	static void total() {
	
		count++;
		cout << count << endl;
	}

};

//静态属性只能这样赋值
int Person::count = 1;

void main() {

	Person::count++;
	cout << Person::count << endl;
	Person::total();
	system("pause");
}
*/

//C++动态内存分配，使用new/delete分配堆内存和释放内存
//molloc/free仍然有效,不同点：molloc不会调用构造和析构函数



/*

//构造函数的属性初始化列表
class Teacher
{
private:
	int age;
	char* name;
public:
	

	//会覆盖默认无参数构造函数
	Teacher(char* name,int age) {
		this->name = name;
		
		cout << "Teacer有参构造函数" << endl;
	}

	~Teacher() {
		cout << "Teacer有参构造函数" << endl;
	}
};

class Students 
{
private: 
	int id;
	//Teacher t = Teacher((char*)"Rose");
	Teacher t;
	Teacher e;

public:
	Students(int id, char* name,int age,char* name1) : t(name,age) ,e(name1,age){
		this->id = id;
	}

	
};

int main() {
	Students s1(10,(char*)"Rose",21, (char*)"Jack");
	system("pause");
}


*/

/*

//浅拷贝：拷贝的是指针地址
//深拷贝：拷贝的是指针指向的内容

//深拷贝（重新分配内存）
class Person
{
private:
	char* name;
	int age;
public:
	Person(char* name, int age) {
		//分配堆内存
		this->name = (char*)malloc(100);
		strcpy(this->name, name);
		this->age = age;
	}

	Person(const Person &obj) {

		//深拷贝
		int len = strlen(obj.name);

		this->name = (char*)malloc(len + 1);
		strcpy(this->name, obj.name);
		this->age = obj.age;

	}

	~Person() {
		cout << "析构函数" << endl;
		free(name);
		
	}
};

void fun() {
	//p1和p2分别指向两块内存区域
	Person p1((char*)"Rose", 21);
	Person p2 = p1;
}

int main() {

	fun();

	system("pause");
}
*/

/*

//浅拷贝（值拷贝）的问题：free()不能调用两次
//解决方案：深拷贝，覆盖默认的拷贝构造函数
class Person 
{
private:
	char* name;
	int age;
public:
	Person(char* name,int age) {
		//分配堆内存
		this->name = (char*)malloc(100);
		strcpy(this->name, name);
		this->age = age;
	}

	~Person() {
		free(name);
	}
};

int main() {

	//p1和p2指向同一块内存区域，不能释放两次
	Person p1((char*)"Rose",21);
	Person p2 = p1;
}





*/


/*

class Person 
{
private:
	char* name;
	int age;

	//1.构造函数
public:
	Person() {
		name = (char*)malloc(100);
		strcpy(name, "Rose");
		cout << "无参构造函数覆盖默认的构造函数" <<  name << endl;
	}

	Person(char* name,int age) {
		this->name = name;
		this->age = age;
	}

	//2.析构函数:当对象内存被系统释放时调用
	//作用：善后处理，释放内存
	//~Person() {
	//	cout << "析构函数" << endl;
	//	//释放name所占的内存
	//	free(this->name);
	//
	//}

	//3.拷贝构造函数(值拷贝,浅拷贝)
	Person(const Person &obj) {

		this->name = obj.name;
		this->age = obj.age;

	}

	void print() {
		cout << name << endl;
	}

};


void fun() {
	


}

int main() {


	Person p1;
	Person p2((char*)"Jack",20);
	Person p3 = Person((char*)"Rose", 21);
	fun();

	Person p1((char*)"Rose and Jack", 21);
	Person p2 = p1;
	
	p2.print();


	system("pause");
}
*/

/*

//可变参数
void fun(int i, ...) {

	

	//可变参数指针
	va_list args_p;
	va_start(args_p, i);
	
	int a = va_arg(args_p, int);
	char b = va_arg(args_p, char);
	int c = va_arg(args_p, int);

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;

	va_end(args_p);
	

	va_list args_p;
	va_start(args_p, i);

	int value;
	while (1) {
		value = va_arg(args_p, int);
		if (value < 0) {
			break;
		}
		cout << value << endl;
	}

	va_end(args_p);

	Student stu;
	stu.setName((char*)"hello");
	cout << stu.getName() << endl;
	
}

int main() 
{

	//fun(10, 20, 'b', 30);
	fun(10, 20, 30, 40);
	system("pause");
}
*/

/*

//指针常量和常量指针


int main()
{
	int a = 1;
	int b = 2;
	//1.指针常量 不改变地址的指针，但是可以改变它指向的内容
	int* const p1 = &a;

	//2.常量指针 指向常量的指针，可以改变地址，但是不能改变指向的内容（值）
	const int* p2 = &a;

	//3.常引用
	const int& c = a;//不能重新赋值
	
	
}
*/

/*
//引用主要作用：作为函数的参数或返回值
//指针保存的是变量的地址，而引用是变量的别名
//指针间接操作变量，引用可以直接操作变量，无须产生副本

//代替二级指针
struct Teacher {
	char name[20];
	int age;
};

void getTeacher1(Teacher** p) {
	Teacher *tea = (Teacher*)malloc(sizeof(Teacher));
	tea->age = 20;
	*p = tea;
}

void getTeacher2(Teacher* &t) {

	t = (Teacher*)malloc(sizeof(Teacher));
	t->age = 21;
}

int main() {

	Teacher *t = NULL;
	getTeacher1(&t);
	getTeacher2(t);
}

*/

/*

//指针交换
void swap_1(int *a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}

//引用交换
void swap_2(int &a, int &b) {

	int c = a;
	a = b;
	b = c;
}

//引用

int main() 
{

	//&:引用符号
	int a = 10;
	int &b = a;
	b = 1;
	cout << a << " " << b << endl;

	int x = 10;
	int y = 20;
	//swap_1(&x, &y);
	//swap_2(x, y);
	cout << x << " " << y << endl;


	system("pause");
}

*/

/*
//结构体 不能继承
struct Teacher {
public:
	char name[20];
	int age;
public:
	void sayHi() {
	
		cout << "年龄：" << age << endl;
	}
};

int main() {
	Teacher teacher;
	teacher.age = 20;
	teacher.sayHi();
	system("pause");
}
*/


/*

//类 可以继承
class Circle 
{
private:
	double r;
	double s;
public:
	void setR(double r) {
		this->r = r;
	}

	double getS() {
	
		return 3.14 * r * r;
	}

};


int main()
{
	Circle c;
	c.setR(2);
	cout << "圆的面积：" << c.getS() << endl;
	system("pause");
}

*/

/*

//标准命名空间std::
void main() {
	// <<：运算符重载
	//std::cout << "this is c++" << std::endl;
	cout << "this is c++" << endl;

	system("pause");
}
*/