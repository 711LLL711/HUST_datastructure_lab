# lab04--图
|content|url|
|:-:|:-:|
|function|[func.h](func.h)|
|main|[u4.cpp](u4.cpp)|
|test case|[input.txt](input.txt)|
|executable file|[u4.exe](u4.exe)|
## Description
函数定义在[func.h](func.h)文件中，main函数在[u4.cpp](u4.cpp)中。  

## Test case
5 线性表 8 集合 7 二叉树 6 无向图 -1 nil 5 6 5 7 8 7 7 6 -1 -1  
It is in [input.txt](test.txt) file.You can input it in the program.   
More description of the creation of a graph,see [test.bmp](test.bmp) file.   
You can load [test.txt](test.txt) in the program. Its format is a little different from the initialization of a graph.
## Typedef part
~~~cpp
/*队列*/
typedef int ElemType;
typedef struct node{
    ElemType data;
    struct node * next;
}node,*nodeptr;
typedef struct {
    nodeptr head;//表头结点,不存数据
    nodeptr rear;
}queue,*queueptr;

/*栈*/
typedef struct stack
{
    ElemType elem[MAX_VERTEX_NUM];
    int p;
} stack; //栈的定义

typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
        KeyType  key;
        char others[20];
} VertexType; //顶点类型定义

typedef struct ArcNode {         //表结点类型定义
        int adjvex;              //顶点位置编号 
        struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;

typedef struct VNode{				//头结点及其数组类型定义
        VertexType data;       	//顶点信息
        ArcNode *firstarc;      	 //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;
~~~
## Definition of const
~~~cpp
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -2
#define MAX_VERTEX_NUM 20
#define graphnum 10
#define MAX_VERTEX_NUM 20
#define MAX_ARC_NUM 40
#define ERROR -1
#define OK 1
#define OVERFLOW -2
~~~
## Declarion of functions
~~~cpp
status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
status LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
status FirstAdjVex(ALGraph G,KeyType u); 
status NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
void dfshelper(const ALGraph &G,int i ,int *visited,void (*visit)(VertexType));
status DFSTraverse(const ALGraph& G,void (*visit)(VertexType));
status BFSTraverse(const ALGraph& G,void (*visit)(VertexType));
void visit(VertexType v);
status SaveGraph(ALGraph G, char FileName[]);  
status LoadGraph(ALGraph &G, char FileName[]);
status VerticesSetLessThanK(ALGraph G,int v,int k,int *result,int *count);
int ShortestPathLength(ALGraph G, KeyType v, KeyType w) ;
void DFS(ALGraph G, int v, int visited[]);
int ConnectedComponentsNums(ALGraph G);

/*栈和队列的函数说明*/
void iniStack(stack &S);
int isEmptyStack(stack &S);
int push(stack &S, ElemType e);
int pop(stack &S);
void initqueue(queueptr q);
status enqueue(queueptr q,ElemType x);
status dequeue(queueptr q ,ElemType &e);
int isempty(queueptr q);
~~~