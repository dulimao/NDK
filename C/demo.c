#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "a.h"
#include "JNIMain.h"



//文件拆分
JNIEXPORT void JNICALL Java_jni_JNIMain_diff
(JNIEnv* env,jclass clazz,jstring jsource_path,jstring jformat,jint file_num) {

	const char* source_path = (*env)->GetStringUTFChars(env, jsource_path,NULL);
	const char* format_pattern = (*env)->GetStringUTFChars(env, jformat, NULL);

	//定义拆分后的文件路径数组，并分配堆内存

	char** patches = malloc(sizeof(char*) * file_num);
	int i = 0;
	for (; i < file_num; i++) {
	
		//分配数组元素内存
		patches[i] = malloc(sizeof(char) * 100);
		//赋值
		sprintf(patches[i], format_pattern, i + 1);
		printf("%s\n",patches[i]);
		
	}

	//得到原文件长度
	FILE* fp = fopen(source_path, "rb");//文件指针会随着读写自动移动
	fseek(fp, 0, SEEK_END);
	long file_length = ftell(fp);
	fseek(fp, 0, 0);

	if (file_length % file_num == 0) {
		//每一部分的长度
		int part_len = file_length / file_num;
		int i = 0;
		for (; i < file_num; i++) {
		
			FILE* fpt = fopen(patches[i],"wb");
			int j = 0;
			for (; j < part_len; j++) {
				fputc(fgetc(fp),fpt);
			}
			fclose(fpt);

		}
	}
	else {
		//每一部分的长度
		int part_len = file_length / file_num;
		int i = 0;
		for (; i < file_num; i++) {

			FILE* fpt = fopen(patches[i], "wb");
			int j = 0;
			for (; j < part_len; j++) {
				fputc(fgetc(fp), fpt);
			}
			fclose(fpt);

		}
	}

	fclose(fp);

	
	i = 0;
	for (; i < file_num; i++) {
		free(patches[i]);
	}
	free(patches);
	(*env)->ReleaseStringUTFChars(env, jsource_path, source_path);
	(*env)->ReleaseStringUTFChars(env, jformat, format_pattern);

}


//文件合并和拆分同理，从子文件中写入总文件
JNIEXPORT void JNICALL Java_jni_JNIMain_diff
(JNIEnv* env, jclass clazz, jstring jsource_path, jstring jformat, jint file_num) {


}



/*

//缓存策略

JNIEXPORT void JNICALL Java_jni_JNIMain_cache(JNIEnv* env, jclass clazz) {

	//jclass clazz = (*env)->GetObjectClass(env, obj);

	//fid 只获取一次
	//局部静态变量作用域不变，但是当方法结束以后，仍然存在内存中,生命周期和整个程序相同
	static jfieldID fid = NULL;

	if (fid == NULL) {
	
		fid = (*env)->GetFieldID(env, clazz, "key", "Ljava/lang/String;");
		printf("--------fid----------\n");

	}
	
}


//初始化全局变量，动态局加载完成后，立刻缓存起来

jfieldID fid = NULL;
jmethodID mid = NULL;


JNIEXPORT void JNICALL Java_jni_JNIMain(JNIEnv* env, jclass clazz) {

	jfieldID fid = (*env)->GetFieldID(env, clazz, "key", "Ljava/lang/String");
	jmethodID mid = (*env)->GetMethodID(env, clazz, "accessMetod", "()V");

	printf("初始化完成");

}

*/


/*
//异常处理
//1.保证Java代码可以运行
//2.补救措施保证C代码继续运行
//JNI自己抛出的异常，在java层使用Throwable捕捉
//用户通过ThrowNew抛出的异常可以在java层捕捉处理

void catchException(JNIEnv* env,jobject obj) {

	jclass clazz = (*env)->GetObjectClass(env,obj);

	jfieldID fid = (*env)->GetFieldID(env,clazz,"key1","Ljava/lang/String;");

	//检测是否发生异常
	jthrowable exception = (*env)->ExceptionOccurred(env);
	if (exception != NULL) {
	
		//发生了异常
		//需要清空这个异常，让java代码可以继续运行
		(*env)->ExceptionClear(env);

		//补救措施
		fid = (*env)->GetFieldID(env, clazz, "key", "Ljava/lang/String;");

	}

	//获取属性的值
	jstring jstr = (*env)->GetObjectField(env,obj,fid);
	char* str = (*env)->GetStringUTFChars(env, jstr, NULL);

	//对比属性值是否合法
	if (_stricmp(str, "hello world") != 0) {
	
		//抛出异常，给java层处理

		jclass excp_clazz = (*env)->FindClass(env,"java/lang/Exception");

		(*env)->ThrowNew(env, excp_clazz,"发生异常，属性值不相等");

	}

}

*/


//JNI引用变量：类型：局部引用，全部引用
//作用：JNI告知虚拟机何时回收一个JNI变量
















/*

//数组

int compare(int* a, int* b) {
	return (*a) - (*b) ;
}

JNIEXPORT jintArray JNICALL Java_jni_JNIMain_sortArray
(JNIEnv *env, jobject jobj, jintArray intarray) {

	jint* elements = (*env)->GetIntArrayElements(env,intarray,JNI_FALSE);

	int len = (*env)->GetArrayLength(env, intarray);
	printf("array length:%d", len);
	//排序
	qsort(elements,len,sizeof(jint),compare);

	//同步（必须）
	//0:java数组更新，并且释放C/C++数组
	//JNI_ABORT:java数组不更新，但是释放C/C++数组
	//JNI_COMMIT：java数组更新，不释放C/C++数组
	(*env)->ReleaseIntArrayElements(env,intarray,elements,0);

	//返回一个数组
	jintArray jarray = (*env)->NewIntArray(env, 10);
	jint* arr = (*env)->GetIntArrayElements(env, jarray, NULL);
	int i = 0;
	for (; i < 10; i++) {
	
		arr[i] = i;
	}

	(*env)->ReleaseIntArrayElements(env, jarray, arr, 0);

	return jarray;


}
*/


/*



//访问构造方法
//使用java/util/Date获取当前时间
void accessConstructMethod(JNIEnv *env, jobject obj) {


	jclass clazz = (*env)->FindClass(env,"java/util/Dat");


	//构造方法名称为<init>
	jmethodID construct_methodid = (*env)->GetMethodID(env,clazz,"<init>","()V");


	//实例化Date对象,相当于java的new
	jobject object = (*env)->NewObject(env,clazz,construct_methodid);


	//调用getTime方法
	jmethodID mid = (*env)->GetMethodID(env,clazz,"getTime","()J");
	jlong time = (*env)->CallLongMethod(env,object,mid);
	printf("当前时间：%lld",time);


}


//访问父类的方法
void accessConstructMethod(JNIEnv *env, jobject obj) {
	jclass cls = (*env)->GetObjectClass(env, obj);
	//获取man属性（对象）
	jfieldID fid = (*env)->GetFieldID(env, cls, "human", "Lcom/dongnaoedu/jni/Human;");
	//获取
	jobject human_obj = (*env)->GetObjectField(env, obj, fid);

	//执行sayHi方法
	jclass human_cls = (*env)->FindClass(env, "com/dongnaoedu/jni/Human"); //注意：传父类的名称
	jmethodID mid = (*env)->GetMethodID(env, human_cls, "sayHi", "()V");

	//执行
	//(*env)->CallObjectMethod(env, human_obj, mid);
	//调用的父类的方法
	(*env)->CallNonvirtualObjectMethod(env, human_obj, human_cls, mid);

}


// 中文问题
JNIEXPORT jstring JNICALL Java_com_dongnaoedu_jni_JniTest_chineseChars
(JNIEnv *env, jobject jobj, jstring in) {
	//输出
	//char *c_str = (*env)->GetStringUTFChars(env, in, JNI_FALSE);
	//printf("%s\n",c_str);

	//c -> jstring
	char *c_str = "马蓉与宋江";
	//char c_str[] = "马蓉与宋喆";
	//jstring jstr = (*env)->NewStringUTF(env, c_str);
	//执行String(byte bytes[], String charsetName)构造方法需要的条件
	//1.jmethodID
	//2.byte数组
	//3.字符编码jstring

	jclass str_cls = (*env)->FindClass(env, "java/lang/String");
	jmethodID constructor_mid = (*env)->GetMethodID(env, str_cls, "<init>", "([BLjava/lang/String;)V");

	//jbyte -> char 
	//jbyteArray -> char[]
	jbyteArray bytes = (*env)->NewByteArray(env, strlen(c_str));
	//byte数组赋值
	//0->strlen(c_str)，从头到尾
	//对等于，从c_str这个字符数组，复制到bytes这个字符数组
	(*env)->SetByteArrayRegion(env, bytes, 0, strlen(c_str), c_str);

	//字符编码jstring
	jstring charsetName = (*env)->NewStringUTF(env, "GB2312");

	//调用构造函数，返回编码之后的jstring
	return (*env)->NewObject(env, str_cls, constructor_mid, bytes, charsetName);
}



JNIEXPORT jstring JNICALL Java_jni_JNIMain_accessField
(JNIEnv *env, jobject obj) {
	accessConstructMethod(env, obj);

	return (*env)->NewStringUTF(env,"hello");
}
*/

/*

//访问方法 调用java的方法产生一个随机数

void accessMethod(JNIEnv *env, jobject obj) {

	jclass clz = (*env)->GetObjectClass(env, obj);
	jmethodID mid = (*env)->GetMethodID(env, clz, "accessMethod", "(I)I");
	jint num = (*env)->CallIntMethod(env, obj, mid, 100);
	printf("%ld", num);

}

//访问属性
//修改成员变量值

JNIEXPORT jstring JNICALL Java_jni_JNIMain_accessField
(JNIEnv *env, jobject obj) {

	accessMethod(env,obj);


	//得到字节码对象
	jclass cls = (*env)->GetObjectClass(env,obj);

	//获取属性ID
	jfieldID id = (*env)->GetFieldID(env,cls,"key","Ljava/lang/String;");



	//根据ID获取属性
	jstring jstr = (*env)->GetObjectField(env,obj,id);
	


	//转换成C语言的字符数组
	char* str = (*env)->GetStringUTFChars(env,jstr,JNI_FALSE);
	
	
	char text[20] = "C++";

	//拼接字符串
	strcat(text,str);

	//将c字符串转换成jstring类型
	jstring jstrs = (*env)->NewStringUTF(env, text);
	
	(*env)->SetObjectField(env,obj,id, jstrs);
	return jstrs;

}



*/






//JNIEnv :结构体指针（C语言中是二级指针，C++中是一级指针,就是结构体别名），
//代表java运行环境，调用Java中的代码
//jclass/jobject:
//当native方法为静态方法时，代表java中native方法所属的类的class对象
//当native方法为非静态方法时，代表java中native方法所属的实例对象





//JNIEnv模拟

/*

typedef struct JNINativeInterfaces_* JNIEnvs;

struct JNINativeInterfaces_ {
	char* (*NewStringUTF)(JNIEnvs*, char*);
};

char* NewStringUTF(JNIEnvs* env, char* str) {

	return str;
}

void main() {

	struct JNINativeInterfaces_ jni_env;
	jni_env.NewStringUTF = NewStringUTF;

	//结构体一级指针
	JNIEnvs env_p = &jni_env;

	//结构体二级指针
	JNIEnvs* env = &env_p;

	//调用
	char* str = (*env)->NewStringUTF(env, "hello");
	printf("%s",str);

	getchar();

}



jstring  Java_jni_JNIMain_getStringFromC
(JNIEnv * env, jclass clazz) {

	 jstring str = (*env)->NewStringUTF(env, "helo I am from C");
	 return str;

}
*/



/*

//头文件a.h中的具体实现
void printA() {
	printf("printA\n");

}

*/



//预编译/宏定义/宏替换
//C语言执行流程：
//编译：形成目标代码（.obj）
//链接：将目标代码与C函数库链接合并，形成最终可执行文件
//执行：

//预编译：为编译左准备工作，完成代码文本的替换

/*define命令
1.定义标识 #ifdef _cplusplus 标识支持c++语法
2.防止文件重复引入（循环引入）
3.定义常数
4.定义宏函数


*/

/*

#define MAX 100//无类型

void java_jni_read() {
	printf("read\n");

}


//宏函数
#define jni(NAME) java_jni_##NAME();

//__VA_ARGS_:可变参数，边长参数
#define LOG(FORMAT,...) printf(##FORMAT,__VA_ARGS__);
#define LOG_I(FORMAT,...) printf("INFO---|");printf(##FORMAT,__VA_ARGS__);

//升级版
#define LOG(LEVEL,FORMAT,...) printf(LEVEL);printf(FORMAT,__VA_ARGS__);
#define LOG_D(FORMAT,...) LOG("DEBUG---|",FORMAT,__VA_ARGS__);

void main() {
	//#include "head.txt";//预处理，替换为头文件的内容 printf("hello world");

	printA();

	jni(read);

	LOG_I("%s\n","hello");
	LOG_D("%s\n","hello world");


	getchar();

}

*/

/*IO流：


*/

/*
//二进制文件文件加密和解密

void main() {
	char* filepath = "C:\\Users\\Administrator\\Desktop\\timg.jpg";
	char* encrpypt_filepath = "C:\\Users\\Administrator\\Desktop\\encrpyptimg.jpg";
	FILE* normal_fp = fopen(filepath, "rb");
	FILE* encrpypt_ftp = fopen(encrpypt_filepath, "wb");
	//密码
	char* password = "8500721";
	int i = 0;//循环使用密码中的字符进行异或运算
	int strlens = strlen(password);

	//一次读一个字符
	int cha = 0;
	while ((cha = fgetc(normal_fp)) != EOF) {
		fputc(cha ^ password[i % strlens], encrpypt_ftp);
		i++;
	}


	fclose(normal_fp);
	fclose(encrpypt_ftp);

	getchar();

}
*/

/*
//文件加密和解密

void encrpypt(char normal_path[],char encrpypt_path[]) {

	FILE* normal_fp = fopen(normal_path,"r");
	FILE* encrpypt_ftp = fopen(encrpypt_path,"w");

	//一次读一个字符
	int cha=0;
	while ((cha = fgetc(normal_fp)) != EOF) {
		fputc(cha ^ 9, encrpypt_ftp);
	}


	fclose(normal_fp);
	fclose(encrpypt_ftp);

}


void main() {
	char* filepath = "C:\\Users\\Administrator\\Desktop\\demo.txt";
	char* encrpypt_filepath = "C:\\Users\\Administrator\\Desktop\\demo_encrpypt.txt";
	encrpypt(filepath, encrpypt_filepath);
	getchar();
}
*/

/*
//文件大小
void main() {

	char* filepath = "C:\\Users\\Administrator\\Desktop\\timg.jpg";
	FILE* fp = fopen(filepath,"r");

	//将指针移动到末尾
	fseek(fp,0,SEEK_END);

	//返回当前文件指针相对文件开头的位移量
	long len = ftell(fp);

	fclose(fp);
	printf("文件长度：%ld字节",len);
	getchar();
}
*/

/*

//二进制文件操作（复制文件）
void main() {

	char* read_path = "C:\\Users\\Administrator\\Desktop\\timg.jpg";
	char* write_path = "C:\\Users\\Administrator\\Desktop\\timg2.jpg";
	FILE* fp = fopen(read_path,"rb");//rb:读取字节模式
	FILE* fp1 = fopen(write_path,"wb");
	if (fp == NULL) {
	
		printf("文件打开失败");
		return;
	}


	int buffer[50];
	int len = 0;//每次读到的长度
	while ((len = fread(buffer,sizeof(int),50,fp) != 0)) {
		fwrite(buffer,sizeof(int),50,fp1);
	}

	fclose(fp);
	fclose(fp1);
	getchar();

}
*/

/*
//写入文件
void main() {

	char* path = "C:\\Users\\Administrator\\Desktop\\demo.txt";
	FILE * fp = fopen(path,"w");
	if (fp == NULL)
	{
		printf("open file failure");
		return;
	}

	char* text = "hello I am new Student!";
	fputs(text,fp);

	fclose(fp);
	getchar();

}
*/
/*
//读取文本文件
void main() {

	char* path = "C:\\Users\\Administrator\\Desktop\\demo.txt";

	//打开
	FILE *fp = fopen(path,"r");
	if (fp == NULL)
	{
		printf("文件打开失败");
		getchar();
		return;
	}

	//读取
	char buf[30];
	while (fgets(buf, 10, fp)) {
		printf("%s\n",buf);
	}

	//关闭
	fclose(fp);

	getchar();

}
*/

/*
枚举：固定的数据(列举所有的情况)
*/


/*

enum Color {
	Red,Yellow,Blue
};
*/

/*联合体(共用体)
不同类型的变量共同占用同一内存空间（互相覆盖），
任何时候只有一个成员存在，节省内存，
大小=最大的成员所占的字节数
最后一个赋值会覆盖前面的值

*/


/*

union JValue {
	int x;
	int y;
	double z;
};

void main() {

	union JValue value;
	value.x = 10;
	value.y = 20;
	value.z = 100.9;
	printf("%d,%d,%lf\n",value.x,value.y,value.z);
	getchar();

}
*/
//类型取别名
/*typedef int jint;

typedef struct WoMan {
	char* name;
	int age;
}W,*WP;//W 是woman结构体的别名，WP是woman结构体指针的别名

void main() {
	jint a = 0;

	W w = { "jack",11 };
	WP p = &w;
	printf("%s,%d\n", p->name,p->age); 
	getchar();

}
*/


/*
//结构体函数指针成员

typedef struct Girl {
	char* name;
	int age;
	void(*sayHi)(char*);
}Girl;

void sayHi(char* text) {

	printf("%s",text);
}

void main(){

	//struct Girl girl;
	Girl girl;
	girl.name = "Lucy";
	girl.age = 18;
	girl.sayHi = sayHi;
	girl.sayHi("hello I am Mack");
	getchar();
}
*/

//结构体是一种构造数据类型
//把不同的数据类型整合起来成为一个自定义的数据类型

//几种写法：

/*
1.
struct Man
{
	//成员
	//char* name;
	char name[20];
	int age;
};
*/
//2.
/*
struct Man
{
	//成员
	//char* name;
	char name[20];
	int age;
} m1, m2 = {"JackD",22};//m1是结构体的变量名，相当于定义的时候就初始化了

//3.匿名结构体,主要用于控制结构体变量的个数（限量版）
struct {
	char* name;
	int age;
} m3，m4;


//4.结构体嵌套
struct Teacher {
	char name[20];
	
};

//结构体指针

struct Student {

	char name[20];
	struct Teacher teacher;

	struct Book {
		char name[2];
	} book;
};

void main() {

	//初始化结构体变量
	//1、struct Man m1 = {"JackD",21};


	//2、
	struct Man m1;
	//m1.name = "Rose";
	strcpy(m1.name,"rose");
	m1.age = 20;

	printf("%s,%d\n",m1.name,m1.age);


	struct Student s1 = { "jack",{"rose"} };


	//结构体指针
	struct Man m6 = {"jack",22};
	struct Man* p = &m6;

	printf("%s,%d\n",m6.name,m6.age);
	printf("%s,%d\n",(*p).name,(*p).age);
	printf("%s,%d\n",p->name,p->age);


	//结构体数组(两种遍历方式)
	struct Man mans[] = { {"jack",21},{"Rose",19} };

	struct Man *ps = mans;
	for (; ps < mans + 2; ps++) {
		printf("%s,%d\n",ps->name,ps->age);
	}

	int i = 0;
	for (; i < 2; i++) {
		printf("%s,%d\n", mans[i].name, mans[i].age);
	}

	//结构体大小（字节对齐,必须是最宽基本数据类型的整数倍）
	struct WoMan {
		int age;
		double height;
	};//大小16个字节



	getchar();


}
*/
/*




//字符串(内存地址连续)
//http://www.kuqin.com/clib/string/strcpy.html
void main() {
	//字符数组，可以修改
	char str[] = {'c','h','i','n','a','\0'};
	char str1[10] = "china";
	//字符指针，不能修改
	char* str2 = "how are you";
	printf("%s", str2);
	getchar();

}
*/

//动态内存分配
/*
C语言内存分配：
栈：Windows下栈内存只有2M左右（确定的常数），超出了上限会包Stack Overflow错误，栈由系统自动分配和释放
堆：程序员手动分配和释放，可以分配操作系统80%的内存
内存分配注意事项：
1、不能释放多次
2、释放后需要置空，标志释放完成
3、内存泄漏（p重新赋值后，再free，并没有真正释放内存）
*//*
void main() {

	//静态内存分配（栈）
	//int a[1024 * 1024 * 10];
	//动态分配（堆）void*指任意类型的指针 
	//int* p = malloc(1024 * 1024 * 10 * sizeof(int));

	//释放内存
	//free(p);

	int len = 5;


	//两种方式
	int* p = malloc(len * sizeof(int));
	//int* p = calloc(len, sizeof(int));
	//此时p就是数组的首地址
	int i = 0;
	for (; i < len; i++) {
		p[i] = rand() % 100;
		printf("%d, %#x\n", p[i], &p[i]);
	}

	//内存不够用时，扩容
	//1.原来内存空间的指针，2.扩容后的内存空间总大小
	int addLen = len + 5;
	int* p1 = realloc(p, sizeof(int) * addLen);//从新分配
	if (p1 == NULL) {
	
		printf("重新分配失败");
	}
	//重新分配内存两种情况：
	//缩小：缩小的那一部分数据会丢失
	//扩大：（内存地址连续）
	//1.如果当前内存区域存在空闲的区域，则直接扩展这块内存，realloc()返回原指针
	//2.如果已经被占用，则寻找后面第一个可用的空间，并将数据复制到新空间，释放原空间
	//3.如果申请失败，返回null，但是第一个指针已然有效


	if (p != NULL)
	{
		free(p);
		p = NULL;
	}
	if (p1 != NULL)
	{
		free(p1);
		p1 = NULL;
	}
	

	getchar();




}*/



/*
//1、指针为什么有类型，
//指针有类型，地址没类型,指针只是开始的位置，类型决定读取到什么位置
//p是内存地址，*p是内存地址对应的值

//5、函数指针
void msg(char* title,char* msg) {
	MessageBox(0,title,msg,0);

}


int add(int a, int b) {

	return a + b;
}

int minus(int a, int b) {

	return a - b;
}

//传递一个返回值为int类型，参数为两个int类型数据的函数指针参数
void funF(int(*fun_p)(int a,int b),int m,int n) {
	int s = fun_p(m, n);
	printf("%d\n",s);
}

int* getMinPointer(int a[], int len) {
	int* p = &a[0];
	int i = 0;
	for (; i < len; i++) {
		if (a[i] < *p) {
			p = &a[i];
		}
	}
	return p;
}

void main() {

	//msg();

	//void(*fun)(char* title, char* msg) = msg;
	//fun("弹窗", "消息内容");

	//funF(add, 20, 10);
	//funF(minus, 10, 20);


	//初始化随机数发生器，设置种子，种子不一样，随机数就不一样
	//当前时间作为种子
	srand(time(NULL));

	int ids[10];
	int i = 0;
	for (; i < 10; i++) {
	
		ids[i] = rand() % 100;
		printf("%d\n", ids[i] % 100);
	}

	int *x = getMinPointer(ids, sizeof(ids) / sizeof(int));
	printf("最小值地址：%#x,最小值：%d\n",x,*x);
	getchar();

}*/



