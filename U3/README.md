# lab03--二叉树
|content|url|
|:-:|:-:|
|function|[def.h](def.h)|
|main|[u3.cpp](u3.cpp)|
|test case|[test.txt](test.txt)|
|executable file|[u3.exe](u3.exe)|
## Description
函数定义在[def.h](def.h)文件中，main函数在[u3.cpp](u3.cpp)中。  
输入序列为二叉树带空子树的先序遍历结点序列，每个结点对应一个整型的关键字和一个字符串，当关键字为0时，表示空子树，为-1表示输入结束。
## Test case
 1  a  2  b  0  0  3  c  4  d  0  0  5  e  0  0 
It is in [test.txt](test.txt) file. It can be loaded in the program.
## Typedef part
~~~cpp
typedef int status;
typedef int KeyType; 
typedef struct {
		KeyType  key;
		char others[ARRSIZE];
} TElemType; //二叉树结点类型定义


typedef struct BiTNode{  //二叉链表结点的定义
		TElemType  data;
		struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

typedef struct {
	BiTree T;//创建二叉树用的指针T
	char name[ARRSIZE];//用于保存树的名称
}LElemType;

typedef struct {
	LElemType tree[LISTSIZE];//多个树进行操作
	int length;
	int listsize;
}SqList;//线性表保存多个树
~~~
## Definition of const
~~~cpp
#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR -1
#define INFEASIBLE -2
#define MAX 100
#define OVERFLOW -3
#define LISTSIZE 20
#define ARRSIZE 20
~~~
## Declarion of functions
~~~cpp
void create(BiTree &T,TElemType definition[]);
void DestroyBiTree(BiTree &T);
void FreeNode(BiTree &T);
status ClearBiTree(BiTree &T);
status BiTreeEmpty(BiTree T);
int max(int a ,int b);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
void locate_parent(BiTree T, BiTree parent, KeyType e, BiTree& p, BiTree& parent_p); 
status Assign(BiTree &T, KeyType e, TElemType value);
BiTNode* GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
status DeleteNode(BiTree &T,KeyType e);
void PreOrderTraverse(BiTree T,void (*visit)(BiTree));
void InOrderTraverse(BiTree T,void (*visit)(BiTree));
void PostOrderTraverse(BiTree T,void (*visit)(BiTree));
void LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
int MaxPathSum(BiTree T, int &maxSum);
BiTree LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2);
void InvertTree(BiTree T);
void read(BiTree &T,FILE *fp);
status SaveBiTree(BiTNode *T,char FileName[]);
status LoadBiTree(BiTree &T,char FileName[]);
void printTree(BiTree T, int type, int level);
~~~