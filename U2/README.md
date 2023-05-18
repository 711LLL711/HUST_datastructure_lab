# lab02--单链表
|content|url|
|:-:|:-:|
|source code|[u2.cpp](u2.cpp)|
|test case|[TEST](TEST)|
|executable file|[u2.exe](u2.exe)|
## Description
函数定义和main函数都在[u2.cpp](u2.cpp)文件中。
## Test case
-5 -3 -2 -1 1 2 4 4  
It is in [TEST](TEST) file. It can be loaded in the program.
## Typedef part
~~~cpp
typedef int status;
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;
~~~
## Definition of const
~~~cpp
#define TRUE 1
#define FALSE 0
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
status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
status LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status reverseList(LinkList L);
status RemoveNthFromEnd(LinkList L,int n);
status sortlist(LinkList L,int order);
status SaveList(LinkList L,char FileName[]);
status LoadList(LinkList &L,char FileName[]);
~~~