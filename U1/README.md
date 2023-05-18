# lab01--顺序表
|content|url|
|:-:|:-:|
|source code|[u1.cpp](u1.cpp)|
|test case|[TEST](TEST)|
|executable file|[u1.exe](u1.exe)|
## Description
函数定义和main函数都在u1.cpp文件中。
## Test case
-2 1 -3 4 -1 2 1 -5 4   
It is in [TEST](TEST) file. It can be loaded in the program.
## Typedef part
~~~cpp
typedef int status;
typedef int ElemType; 
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
}SqList;
~~~
## Definition of const
~~~cpp
#define TRUE 0
#define FALSE -3
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_NUM 10
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
~~~
## Declarion of functions
~~~cpp
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType &e);
int LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType e,ElemType &pre);
status NextElem(SqList L,ElemType e,ElemType &next);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L,int i,ElemType &e);
status ListTraverse(SqList L);
status  SaveList(SqList L,char FileName[]);
status  LoadList(SqList &L,char FileName[]);
int Maxsubarray(SqList L);
int subarraynum(SqList L ,ElemType k);
status sortlist(SqList L,int order);
~~~