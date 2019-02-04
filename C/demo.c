#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "a.h"
#include "JNIMain.h"



//�ļ����
JNIEXPORT void JNICALL Java_jni_JNIMain_diff
(JNIEnv* env,jclass clazz,jstring jsource_path,jstring jformat,jint file_num) {

	const char* source_path = (*env)->GetStringUTFChars(env, jsource_path,NULL);
	const char* format_pattern = (*env)->GetStringUTFChars(env, jformat, NULL);

	//�����ֺ���ļ�·�����飬��������ڴ�

	char** patches = malloc(sizeof(char*) * file_num);
	int i = 0;
	for (; i < file_num; i++) {
	
		//��������Ԫ���ڴ�
		patches[i] = malloc(sizeof(char) * 100);
		//��ֵ
		sprintf(patches[i], format_pattern, i + 1);
		printf("%s\n",patches[i]);
		
	}

	//�õ�ԭ�ļ�����
	FILE* fp = fopen(source_path, "rb");//�ļ�ָ������Ŷ�д�Զ��ƶ�
	fseek(fp, 0, SEEK_END);
	long file_length = ftell(fp);
	fseek(fp, 0, 0);

	if (file_length % file_num == 0) {
		//ÿһ���ֵĳ���
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
		//ÿһ���ֵĳ���
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


//�ļ��ϲ��Ͳ��ͬ�������ļ���д�����ļ�
JNIEXPORT void JNICALL Java_jni_JNIMain_diff
(JNIEnv* env, jclass clazz, jstring jsource_path, jstring jformat, jint file_num) {


}



/*

//�������

JNIEXPORT void JNICALL Java_jni_JNIMain_cache(JNIEnv* env, jclass clazz) {

	//jclass clazz = (*env)->GetObjectClass(env, obj);

	//fid ֻ��ȡһ��
	//�ֲ���̬���������򲻱䣬���ǵ����������Ժ���Ȼ�����ڴ���,�������ں�����������ͬ
	static jfieldID fid = NULL;

	if (fid == NULL) {
	
		fid = (*env)->GetFieldID(env, clazz, "key", "Ljava/lang/String;");
		printf("--------fid----------\n");

	}
	
}


//��ʼ��ȫ�ֱ�������̬�ּ�����ɺ����̻�������

jfieldID fid = NULL;
jmethodID mid = NULL;


JNIEXPORT void JNICALL Java_jni_JNIMain(JNIEnv* env, jclass clazz) {

	jfieldID fid = (*env)->GetFieldID(env, clazz, "key", "Ljava/lang/String");
	jmethodID mid = (*env)->GetMethodID(env, clazz, "accessMetod", "()V");

	printf("��ʼ�����");

}

*/


/*
//�쳣����
//1.��֤Java�����������
//2.���ȴ�ʩ��֤C�����������
//JNI�Լ��׳����쳣����java��ʹ��Throwable��׽
//�û�ͨ��ThrowNew�׳����쳣������java�㲶׽����

void catchException(JNIEnv* env,jobject obj) {

	jclass clazz = (*env)->GetObjectClass(env,obj);

	jfieldID fid = (*env)->GetFieldID(env,clazz,"key1","Ljava/lang/String;");

	//����Ƿ����쳣
	jthrowable exception = (*env)->ExceptionOccurred(env);
	if (exception != NULL) {
	
		//�������쳣
		//��Ҫ�������쳣����java������Լ�������
		(*env)->ExceptionClear(env);

		//���ȴ�ʩ
		fid = (*env)->GetFieldID(env, clazz, "key", "Ljava/lang/String;");

	}

	//��ȡ���Ե�ֵ
	jstring jstr = (*env)->GetObjectField(env,obj,fid);
	char* str = (*env)->GetStringUTFChars(env, jstr, NULL);

	//�Ա�����ֵ�Ƿ�Ϸ�
	if (_stricmp(str, "hello world") != 0) {
	
		//�׳��쳣����java�㴦��

		jclass excp_clazz = (*env)->FindClass(env,"java/lang/Exception");

		(*env)->ThrowNew(env, excp_clazz,"�����쳣������ֵ�����");

	}

}

*/


//JNI���ñ��������ͣ��ֲ����ã�ȫ������
//���ã�JNI��֪�������ʱ����һ��JNI����
















/*

//����

int compare(int* a, int* b) {
	return (*a) - (*b) ;
}

JNIEXPORT jintArray JNICALL Java_jni_JNIMain_sortArray
(JNIEnv *env, jobject jobj, jintArray intarray) {

	jint* elements = (*env)->GetIntArrayElements(env,intarray,JNI_FALSE);

	int len = (*env)->GetArrayLength(env, intarray);
	printf("array length:%d", len);
	//����
	qsort(elements,len,sizeof(jint),compare);

	//ͬ�������룩
	//0:java������£������ͷ�C/C++����
	//JNI_ABORT:java���鲻���£������ͷ�C/C++����
	//JNI_COMMIT��java������£����ͷ�C/C++����
	(*env)->ReleaseIntArrayElements(env,intarray,elements,0);

	//����һ������
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



//���ʹ��췽��
//ʹ��java/util/Date��ȡ��ǰʱ��
void accessConstructMethod(JNIEnv *env, jobject obj) {


	jclass clazz = (*env)->FindClass(env,"java/util/Dat");


	//���췽������Ϊ<init>
	jmethodID construct_methodid = (*env)->GetMethodID(env,clazz,"<init>","()V");


	//ʵ����Date����,�൱��java��new
	jobject object = (*env)->NewObject(env,clazz,construct_methodid);


	//����getTime����
	jmethodID mid = (*env)->GetMethodID(env,clazz,"getTime","()J");
	jlong time = (*env)->CallLongMethod(env,object,mid);
	printf("��ǰʱ�䣺%lld",time);


}


//���ʸ���ķ���
void accessConstructMethod(JNIEnv *env, jobject obj) {
	jclass cls = (*env)->GetObjectClass(env, obj);
	//��ȡman���ԣ�����
	jfieldID fid = (*env)->GetFieldID(env, cls, "human", "Lcom/dongnaoedu/jni/Human;");
	//��ȡ
	jobject human_obj = (*env)->GetObjectField(env, obj, fid);

	//ִ��sayHi����
	jclass human_cls = (*env)->FindClass(env, "com/dongnaoedu/jni/Human"); //ע�⣺�����������
	jmethodID mid = (*env)->GetMethodID(env, human_cls, "sayHi", "()V");

	//ִ��
	//(*env)->CallObjectMethod(env, human_obj, mid);
	//���õĸ���ķ���
	(*env)->CallNonvirtualObjectMethod(env, human_obj, human_cls, mid);

}


// ��������
JNIEXPORT jstring JNICALL Java_com_dongnaoedu_jni_JniTest_chineseChars
(JNIEnv *env, jobject jobj, jstring in) {
	//���
	//char *c_str = (*env)->GetStringUTFChars(env, in, JNI_FALSE);
	//printf("%s\n",c_str);

	//c -> jstring
	char *c_str = "�������ν�";
	//char c_str[] = "�������Ά�";
	//jstring jstr = (*env)->NewStringUTF(env, c_str);
	//ִ��String(byte bytes[], String charsetName)���췽����Ҫ������
	//1.jmethodID
	//2.byte����
	//3.�ַ�����jstring

	jclass str_cls = (*env)->FindClass(env, "java/lang/String");
	jmethodID constructor_mid = (*env)->GetMethodID(env, str_cls, "<init>", "([BLjava/lang/String;)V");

	//jbyte -> char 
	//jbyteArray -> char[]
	jbyteArray bytes = (*env)->NewByteArray(env, strlen(c_str));
	//byte���鸳ֵ
	//0->strlen(c_str)����ͷ��β
	//�Ե��ڣ���c_str����ַ����飬���Ƶ�bytes����ַ�����
	(*env)->SetByteArrayRegion(env, bytes, 0, strlen(c_str), c_str);

	//�ַ�����jstring
	jstring charsetName = (*env)->NewStringUTF(env, "GB2312");

	//���ù��캯�������ر���֮���jstring
	return (*env)->NewObject(env, str_cls, constructor_mid, bytes, charsetName);
}



JNIEXPORT jstring JNICALL Java_jni_JNIMain_accessField
(JNIEnv *env, jobject obj) {
	accessConstructMethod(env, obj);

	return (*env)->NewStringUTF(env,"hello");
}
*/

/*

//���ʷ��� ����java�ķ�������һ�������

void accessMethod(JNIEnv *env, jobject obj) {

	jclass clz = (*env)->GetObjectClass(env, obj);
	jmethodID mid = (*env)->GetMethodID(env, clz, "accessMethod", "(I)I");
	jint num = (*env)->CallIntMethod(env, obj, mid, 100);
	printf("%ld", num);

}

//��������
//�޸ĳ�Ա����ֵ

JNIEXPORT jstring JNICALL Java_jni_JNIMain_accessField
(JNIEnv *env, jobject obj) {

	accessMethod(env,obj);


	//�õ��ֽ������
	jclass cls = (*env)->GetObjectClass(env,obj);

	//��ȡ����ID
	jfieldID id = (*env)->GetFieldID(env,cls,"key","Ljava/lang/String;");



	//����ID��ȡ����
	jstring jstr = (*env)->GetObjectField(env,obj,id);
	


	//ת����C���Ե��ַ�����
	char* str = (*env)->GetStringUTFChars(env,jstr,JNI_FALSE);
	
	
	char text[20] = "C++";

	//ƴ���ַ���
	strcat(text,str);

	//��c�ַ���ת����jstring����
	jstring jstrs = (*env)->NewStringUTF(env, text);
	
	(*env)->SetObjectField(env,obj,id, jstrs);
	return jstrs;

}



*/






//JNIEnv :�ṹ��ָ�루C�������Ƕ���ָ�룬C++����һ��ָ��,���ǽṹ���������
//����java���л���������Java�еĴ���
//jclass/jobject:
//��native����Ϊ��̬����ʱ������java��native�������������class����
//��native����Ϊ�Ǿ�̬����ʱ������java��native����������ʵ������





//JNIEnvģ��

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

	//�ṹ��һ��ָ��
	JNIEnvs env_p = &jni_env;

	//�ṹ�����ָ��
	JNIEnvs* env = &env_p;

	//����
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

//ͷ�ļ�a.h�еľ���ʵ��
void printA() {
	printf("printA\n");

}

*/



//Ԥ����/�궨��/���滻
//C����ִ�����̣�
//���룺�γ�Ŀ����루.obj��
//���ӣ���Ŀ�������C���������Ӻϲ����γ����տ�ִ���ļ�
//ִ�У�

//Ԥ���룺Ϊ������׼����������ɴ����ı����滻

/*define����
1.�����ʶ #ifdef _cplusplus ��ʶ֧��c++�﷨
2.��ֹ�ļ��ظ����루ѭ�����룩
3.���峣��
4.����꺯��


*/

/*

#define MAX 100//������

void java_jni_read() {
	printf("read\n");

}


//�꺯��
#define jni(NAME) java_jni_##NAME();

//__VA_ARGS_:�ɱ�������߳�����
#define LOG(FORMAT,...) printf(##FORMAT,__VA_ARGS__);
#define LOG_I(FORMAT,...) printf("INFO---|");printf(##FORMAT,__VA_ARGS__);

//������
#define LOG(LEVEL,FORMAT,...) printf(LEVEL);printf(FORMAT,__VA_ARGS__);
#define LOG_D(FORMAT,...) LOG("DEBUG---|",FORMAT,__VA_ARGS__);

void main() {
	//#include "head.txt";//Ԥ�����滻Ϊͷ�ļ������� printf("hello world");

	printA();

	jni(read);

	LOG_I("%s\n","hello");
	LOG_D("%s\n","hello world");


	getchar();

}

*/

/*IO����


*/

/*
//�������ļ��ļ����ܺͽ���

void main() {
	char* filepath = "C:\\Users\\Administrator\\Desktop\\timg.jpg";
	char* encrpypt_filepath = "C:\\Users\\Administrator\\Desktop\\encrpyptimg.jpg";
	FILE* normal_fp = fopen(filepath, "rb");
	FILE* encrpypt_ftp = fopen(encrpypt_filepath, "wb");
	//����
	char* password = "8500721";
	int i = 0;//ѭ��ʹ�������е��ַ������������
	int strlens = strlen(password);

	//һ�ζ�һ���ַ�
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
//�ļ����ܺͽ���

void encrpypt(char normal_path[],char encrpypt_path[]) {

	FILE* normal_fp = fopen(normal_path,"r");
	FILE* encrpypt_ftp = fopen(encrpypt_path,"w");

	//һ�ζ�һ���ַ�
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
//�ļ���С
void main() {

	char* filepath = "C:\\Users\\Administrator\\Desktop\\timg.jpg";
	FILE* fp = fopen(filepath,"r");

	//��ָ���ƶ���ĩβ
	fseek(fp,0,SEEK_END);

	//���ص�ǰ�ļ�ָ������ļ���ͷ��λ����
	long len = ftell(fp);

	fclose(fp);
	printf("�ļ����ȣ�%ld�ֽ�",len);
	getchar();
}
*/

/*

//�������ļ������������ļ���
void main() {

	char* read_path = "C:\\Users\\Administrator\\Desktop\\timg.jpg";
	char* write_path = "C:\\Users\\Administrator\\Desktop\\timg2.jpg";
	FILE* fp = fopen(read_path,"rb");//rb:��ȡ�ֽ�ģʽ
	FILE* fp1 = fopen(write_path,"wb");
	if (fp == NULL) {
	
		printf("�ļ���ʧ��");
		return;
	}


	int buffer[50];
	int len = 0;//ÿ�ζ����ĳ���
	while ((len = fread(buffer,sizeof(int),50,fp) != 0)) {
		fwrite(buffer,sizeof(int),50,fp1);
	}

	fclose(fp);
	fclose(fp1);
	getchar();

}
*/

/*
//д���ļ�
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
//��ȡ�ı��ļ�
void main() {

	char* path = "C:\\Users\\Administrator\\Desktop\\demo.txt";

	//��
	FILE *fp = fopen(path,"r");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��");
		getchar();
		return;
	}

	//��ȡ
	char buf[30];
	while (fgets(buf, 10, fp)) {
		printf("%s\n",buf);
	}

	//�ر�
	fclose(fp);

	getchar();

}
*/

/*
ö�٣��̶�������(�о����е����)
*/


/*

enum Color {
	Red,Yellow,Blue
};
*/

/*������(������)
��ͬ���͵ı�����ͬռ��ͬһ�ڴ�ռ䣨���า�ǣ���
�κ�ʱ��ֻ��һ����Ա���ڣ���ʡ�ڴ棬
��С=���ĳ�Ա��ռ���ֽ���
���һ����ֵ�Ḳ��ǰ���ֵ

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
//����ȡ����
/*typedef int jint;

typedef struct WoMan {
	char* name;
	int age;
}W,*WP;//W ��woman�ṹ��ı�����WP��woman�ṹ��ָ��ı���

void main() {
	jint a = 0;

	W w = { "jack",11 };
	WP p = &w;
	printf("%s,%d\n", p->name,p->age); 
	getchar();

}
*/


/*
//�ṹ�庯��ָ���Ա

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

//�ṹ����һ�ֹ�����������
//�Ѳ�ͬ��������������������Ϊһ���Զ������������

//����д����

/*
1.
struct Man
{
	//��Ա
	//char* name;
	char name[20];
	int age;
};
*/
//2.
/*
struct Man
{
	//��Ա
	//char* name;
	char name[20];
	int age;
} m1, m2 = {"JackD",22};//m1�ǽṹ��ı��������൱�ڶ����ʱ��ͳ�ʼ����

//3.�����ṹ��,��Ҫ���ڿ��ƽṹ������ĸ����������棩
struct {
	char* name;
	int age;
} m3��m4;


//4.�ṹ��Ƕ��
struct Teacher {
	char name[20];
	
};

//�ṹ��ָ��

struct Student {

	char name[20];
	struct Teacher teacher;

	struct Book {
		char name[2];
	} book;
};

void main() {

	//��ʼ���ṹ�����
	//1��struct Man m1 = {"JackD",21};


	//2��
	struct Man m1;
	//m1.name = "Rose";
	strcpy(m1.name,"rose");
	m1.age = 20;

	printf("%s,%d\n",m1.name,m1.age);


	struct Student s1 = { "jack",{"rose"} };


	//�ṹ��ָ��
	struct Man m6 = {"jack",22};
	struct Man* p = &m6;

	printf("%s,%d\n",m6.name,m6.age);
	printf("%s,%d\n",(*p).name,(*p).age);
	printf("%s,%d\n",p->name,p->age);


	//�ṹ������(���ֱ�����ʽ)
	struct Man mans[] = { {"jack",21},{"Rose",19} };

	struct Man *ps = mans;
	for (; ps < mans + 2; ps++) {
		printf("%s,%d\n",ps->name,ps->age);
	}

	int i = 0;
	for (; i < 2; i++) {
		printf("%s,%d\n", mans[i].name, mans[i].age);
	}

	//�ṹ���С���ֽڶ���,�������������������͵���������
	struct WoMan {
		int age;
		double height;
	};//��С16���ֽ�



	getchar();


}
*/
/*




//�ַ���(�ڴ��ַ����)
//http://www.kuqin.com/clib/string/strcpy.html
void main() {
	//�ַ����飬�����޸�
	char str[] = {'c','h','i','n','a','\0'};
	char str1[10] = "china";
	//�ַ�ָ�룬�����޸�
	char* str2 = "how are you";
	printf("%s", str2);
	getchar();

}
*/

//��̬�ڴ����
/*
C�����ڴ���䣺
ջ��Windows��ջ�ڴ�ֻ��2M���ң�ȷ���ĳ����������������޻��Stack Overflow����ջ��ϵͳ�Զ�������ͷ�
�ѣ�����Ա�ֶ�������ͷţ����Է������ϵͳ80%���ڴ�
�ڴ����ע�����
1�������ͷŶ��
2���ͷź���Ҫ�ÿգ���־�ͷ����
3���ڴ�й©��p���¸�ֵ����free����û�������ͷ��ڴ棩
*//*
void main() {

	//��̬�ڴ���䣨ջ��
	//int a[1024 * 1024 * 10];
	//��̬���䣨�ѣ�void*ָ�������͵�ָ�� 
	//int* p = malloc(1024 * 1024 * 10 * sizeof(int));

	//�ͷ��ڴ�
	//free(p);

	int len = 5;


	//���ַ�ʽ
	int* p = malloc(len * sizeof(int));
	//int* p = calloc(len, sizeof(int));
	//��ʱp����������׵�ַ
	int i = 0;
	for (; i < len; i++) {
		p[i] = rand() % 100;
		printf("%d, %#x\n", p[i], &p[i]);
	}

	//�ڴ治����ʱ������
	//1.ԭ���ڴ�ռ��ָ�룬2.���ݺ���ڴ�ռ��ܴ�С
	int addLen = len + 5;
	int* p1 = realloc(p, sizeof(int) * addLen);//���·���
	if (p1 == NULL) {
	
		printf("���·���ʧ��");
	}
	//���·����ڴ����������
	//��С����С����һ�������ݻᶪʧ
	//���󣺣��ڴ��ַ������
	//1.�����ǰ�ڴ�������ڿ��е�������ֱ����չ����ڴ棬realloc()����ԭָ��
	//2.����Ѿ���ռ�ã���Ѱ�Һ����һ�����õĿռ䣬�������ݸ��Ƶ��¿ռ䣬�ͷ�ԭ�ռ�
	//3.�������ʧ�ܣ�����null�����ǵ�һ��ָ����Ȼ��Ч


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
//1��ָ��Ϊʲô�����ͣ�
//ָ�������ͣ���ַû����,ָ��ֻ�ǿ�ʼ��λ�ã����;�����ȡ��ʲôλ��
//p���ڴ��ַ��*p���ڴ��ַ��Ӧ��ֵ

//5������ָ��
void msg(char* title,char* msg) {
	MessageBox(0,title,msg,0);

}


int add(int a, int b) {

	return a + b;
}

int minus(int a, int b) {

	return a - b;
}

//����һ������ֵΪint���ͣ�����Ϊ����int�������ݵĺ���ָ�����
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
	//fun("����", "��Ϣ����");

	//funF(add, 20, 10);
	//funF(minus, 10, 20);


	//��ʼ����������������������ӣ����Ӳ�һ����������Ͳ�һ��
	//��ǰʱ����Ϊ����
	srand(time(NULL));

	int ids[10];
	int i = 0;
	for (; i < 10; i++) {
	
		ids[i] = rand() % 100;
		printf("%d\n", ids[i] % 100);
	}

	int *x = getMinPointer(ids, sizeof(ids) / sizeof(int));
	printf("��Сֵ��ַ��%#x,��Сֵ��%d\n",x,*x);
	getchar();

}*/



