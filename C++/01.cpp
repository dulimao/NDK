#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdarg.h>

using namespace std;

#include "Student.h"


//�����������ε���this
//�Ȳ��ܸı�ָ���ֵ��Ҳ���ܸı�ָ��ָ��ĵ�ַ
//const Person* const this;//ָ�볣���ͳ���ָ��
/*

��������ֻ�ܵ��ó�������
void fun() const
{
//������κζ��󶼲����޸�
}
*/

//��̬���Ժ;�̬����
class Person {

public:
	static int count;

public:
	static void total() {
	
		count++;
		cout << count << endl;
	}

};

//��̬����ֻ��������ֵ
int Person::count = 1;

void main() {

	Person::count++;
	cout << Person::count << endl;
	Person::total();
	system("pause");
}


//C++��̬�ڴ���䣬ʹ��new/delete������ڴ���ͷ��ڴ�
//molloc/free��Ȼ��Ч,��ͬ�㣺molloc������ù������������



/*

//���캯�������Գ�ʼ���б�
class Teacher
{
private:
	int age;
	char* name;
public:
	

	//�Ḳ��Ĭ���޲������캯��
	Teacher(char* name,int age) {
		this->name = name;
		
		cout << "Teacer�вι��캯��" << endl;
	}

	~Teacher() {
		cout << "Teacer�вι��캯��" << endl;
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

//ǳ��������������ָ���ַ
//�������������ָ��ָ�������

//��������·����ڴ棩
class Person
{
private:
	char* name;
	int age;
public:
	Person(char* name, int age) {
		//������ڴ�
		this->name = (char*)malloc(100);
		strcpy(this->name, name);
		this->age = age;
	}

	Person(const Person &obj) {

		//���
		int len = strlen(obj.name);

		this->name = (char*)malloc(len + 1);
		strcpy(this->name, obj.name);
		this->age = obj.age;

	}

	~Person() {
		cout << "��������" << endl;
		free(name);
		
	}
};

void fun() {
	//p1��p2�ֱ�ָ�������ڴ�����
	Person p1((char*)"Rose", 21);
	Person p2 = p1;
}

int main() {

	fun();

	system("pause");
}
*/

/*

//ǳ������ֵ�����������⣺free()���ܵ�������
//������������������Ĭ�ϵĿ������캯��
class Person 
{
private:
	char* name;
	int age;
public:
	Person(char* name,int age) {
		//������ڴ�
		this->name = (char*)malloc(100);
		strcpy(this->name, name);
		this->age = age;
	}

	~Person() {
		free(name);
	}
};

int main() {

	//p1��p2ָ��ͬһ���ڴ����򣬲����ͷ�����
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

	//1.���캯��
public:
	Person() {
		name = (char*)malloc(100);
		strcpy(name, "Rose");
		cout << "�޲ι��캯������Ĭ�ϵĹ��캯��" <<  name << endl;
	}

	Person(char* name,int age) {
		this->name = name;
		this->age = age;
	}

	//2.��������:�������ڴ汻ϵͳ�ͷ�ʱ����
	//���ã��ƺ����ͷ��ڴ�
	//~Person() {
	//	cout << "��������" << endl;
	//	//�ͷ�name��ռ���ڴ�
	//	free(this->name);
	//
	//}

	//3.�������캯��(ֵ����,ǳ����)
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

//�ɱ����
void fun(int i, ...) {

	

	//�ɱ����ָ��
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

//ָ�볣���ͳ���ָ��


int main()
{
	int a = 1;
	int b = 2;
	//1.ָ�볣�� ���ı��ַ��ָ�룬���ǿ��Ըı���ָ�������
	int* const p1 = &a;

	//2.����ָ�� ָ������ָ�룬���Ըı��ַ�����ǲ��ܸı�ָ������ݣ�ֵ��
	const int* p2 = &a;

	//3.������
	const int& c = a;//�������¸�ֵ
	
	
}
*/

/*
//������Ҫ���ã���Ϊ�����Ĳ����򷵻�ֵ
//ָ�뱣����Ǳ����ĵ�ַ���������Ǳ����ı���
//ָ���Ӳ������������ÿ���ֱ�Ӳ��������������������

//�������ָ��
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

//ָ�뽻��
void swap_1(int *a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}

//���ý���
void swap_2(int &a, int &b) {

	int c = a;
	a = b;
	b = c;
}

//����

int main() 
{

	//&:���÷���
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
//�ṹ�� ���ܼ̳�
struct Teacher {
public:
	char name[20];
	int age;
public:
	void sayHi() {
	
		cout << "���䣺" << age << endl;
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

//�� ���Լ̳�
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
	cout << "Բ�������" << c.getS() << endl;
	system("pause");
}

*/

/*

//��׼�����ռ�std::
void main() {
	// <<�����������
	//std::cout << "this is c++" << std::endl;
	cout << "this is c++" << endl;

	system("pause");
}
*/