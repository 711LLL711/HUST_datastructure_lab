#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

/*队列函数*/
void initqueue(queueptr q)
{
    q->head=(nodeptr)malloc(sizeof(node));
    q->head->next=NULL;
    q->rear=q->head;
}

status enqueue(queueptr q,ElemType x)
{
    nodeptr newnode=(nodeptr)malloc(sizeof(node));
    if(newnode==NULL){
        return OVERFLOW;
    }
    newnode->data=x;
    newnode->next=NULL;
    q->rear->next=newnode;
    q->rear=newnode;
    return OK;
}
status dequeue(queueptr q ,ElemType &e)
{
    if(q->head->next==NULL){
        return ERROR;
    }
    nodeptr p=q->head->next;
    e=p->data;
    q->head->next=p->next;
    if(q->rear==p){
        q->rear=q->head;
    }
    free(p);
    return OK;
}
int isempty(queueptr q)
{
    if(q->head->next==NULL){
        return 1;
    }
    return 0;
}

/*栈函数*/
void iniStack(stack &S)
//该函数初始化栈S
{
    S.p = 0;
}
int isEmptyStack(stack &S)
//判断是不是空栈，是则返回1，不是则返回0
{
    if (S.p)
        return 0;
    else
        return 1;
}
int push(stack &S, ElemType e)
//该函数将元素进栈，成功则返回1，失败返回0
{
    if (S.p == MAX_VERTEX_NUM - 1)
        return OVERFLOW;
    else
    {
        S.elem[++S.p] = e;
    }
    return OK;
}
int pop(stack &S)
//该函数将元素出栈，返回出栈的元素值
{
    if (S.p == 0)
        return ERROR;
    else
        return S.elem[S.p--];
}


/*************************
 * 函数名称: CreateGraph
 * 初始条件：图G不存在
 * 操作结果: 创建图G
 *************************/
status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]) {
	int m = 0,n,one = -1,two = -1 ;
    G.vexnum=G.arcnum=0;
    //添加头结点
    while(V[m].key != -1){
		G.vertices[m].data = V[m];
		G.vertices[m].firstarc = NULL;
        m++;
        if(m > MAX_VERTEX_NUM) return ERROR;
    }

	G.vexnum = m;
    if(G.vexnum==0){
        return ERROR;
    }
    for(m = 0; m < G.vexnum; m++) {
		for(n = m+1; n < G.vexnum ; n++) {
			if(V[m].key == V[n].key)
				return ERROR;
		}
	}
    
	m = 0;
	ArcNode *p;

    //保存VR边信息的数组，VR[i][0]和VR[i][1]分别表示第i条边的两个顶点的key值
	while (VR[m][0] != -1) {
		one = -1;two=-1;//one和two分别表示第i条边的两个顶点在头结点数组中的位置
		for(n = 0; n < G.vexnum; n++){
            if (VR[m][0] == G.vertices[n].data.key) {
				one = n;
				break;
			}
        }
        if(n==G.vexnum){
                return ERROR;
        }
		for(n = 0; n < G.vexnum; n++){
            if (VR[m][1] == G.vertices[n].data.key) {
				two = n;
				break;
			}
        }
        if(n==G.vexnum){
                return ERROR;
        }
        if(one==two){
            return ERROR;
        }

        G.arcnum++;
        //头插法	
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p -> adjvex = two;
		p -> nextarc = G.vertices[one].firstarc;
		G.vertices[one].firstarc = p;

		p = (ArcNode*)malloc(sizeof(ArcNode));
		p -> adjvex = one;
		p -> nextarc = G.vertices[two].firstarc;
		G.vertices[two].firstarc = p;
		m++;
	}
    G.kind = UDG;
    return OK;
}

/**************************
 * 函数名称: DestroyGraph
 * 初始条件：图G已存在
 * 操作结果: 销毁图G
 *************************/
status DestroyGraph(ALGraph &G) {
	int i;
	ArcNode *p, *q;//边类型的指针p,q
	for(i = 0; i < G.vexnum; i++) {
		p = G.vertices[i].firstarc;//p指向第i个节点的 第一条依附于该节点的指针
		while(p) { //p不为空,就依次将q指向下一条弧,释放p,最后再将p指向q，开始下一次循环
			q = p->nextarc;
			free(p);
			p = q;
		}
	}
	G.vexnum = 0;//之后将图的信息,顶点数目,边数目,kind置为DG
	G.arcnum = 0;
    G.kind=DG;
	return OK;
}

/******************************************************************
 * 函数名称: LocateVex
 * 初始条件：图G存在，u和G中的顶点具有相同特征
 * 函数功能: 若u在图G中存在，返回顶点u的索引，否则返回ERROR
 ******************************************************************/
status LocateVex(ALGraph G,KeyType u) {
	int i;
	for(i=0; i<G.vexnum; i++) {
		if(u == G.vertices[i].data.key)//判断节点名称是否相同
			return i;//如果查找成功，返回i的值
	}
	return ERROR;
}


/***************************************
 * 函数名称: PutVex
 * 初始条件：图G存在，v是G中的某个顶点
 * 函数功能: 根据u在图G中查找顶点v，对v赋值value
 * 返回值：如果v在图G中存在，返回OK，如果查找失败或关键字不唯一，返回ERROR
 **************************************/
status PutVex(ALGraph &G,KeyType u,VertexType value)
{
    int i ,j;
    for(i = 0 ;i < G.vexnum ;i++){
        if(G.vertices[i].data.key == u){
            for(j = 0 ; j < G.vexnum ;j++){
                if(G.vertices[j].data.key == value.key && i != j ){
                    return ERROR;
                }
            }
            G.vertices[i].data = value;
            return OK;
        }
    }
    return ERROR;
}

/********************************************************************
 * 函数名称: FirstAdjVex
 * 初始条件：图G存在，v是G中的某个顶点
 * 函数功能: 返回v的第一个邻接顶点，如果v没有邻接顶点，返回ERROR
 ********************************************************************/
int FirstAdjVex(ALGraph G,KeyType u)
{
    int i;
    ArcNode *p;
    i = LocateVex(G, u);
    if(i==-1){//如果没有找到该节点，返回ERROR
        return ERROR;
    }
    p = G.vertices[i].firstarc;
    if(p){
        return p->adjvex;
    }else{//如果没有邻接点，返回ERROR
        return ERROR;
    }
}

/***********************************************************************************
 * 函数名称: NextAdjVex
 * 初始条件：图G存在，v是G的一个顶点,w是v的邻接顶点
 * 函数功能: 返回v的（相对于w）下一个邻接顶点，如果w是最后一个邻接顶点，返回ERROR
 ***********************************************************************************/
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
{
    int i;
    for(i = 0 ;i < G.vexnum ;i++){
        if(G.vertices[i].data.key == v){//找到结点v
            ArcNode *p = G.vertices[i].firstarc;
            while(p){
                if(G.vertices[p->adjvex].data.key == w){//找到结点w
                    if(p->nextarc){//如果w不是最后一个邻接顶点
                        return p->nextarc->adjvex;
                    }else{
                        return ERROR;
                    }
                }
                p = p->nextarc;
            }
        }
    }
    return ERROR;
}


/*************************************************
 * 函数名称: InsertVex
 * 初始条件：图G存在，v和G中的顶点具有相同特征
 * 函数功能: 在图G中增加新顶点v
 * 返回值：成功返回OK,若插入后有重复或插入后节点个数超了，返回ERROR
 *************************************************/

status InsertVex(ALGraph &G,VertexType v)
{
    if(LocateVex(G,v.key)>=0) return ERROR;
    if(G.vexnum==MAX_VERTEX_NUM) return ERROR;
    G.vertices[G.vexnum].data=v;
    G.vertices[G.vexnum].firstarc=NULL;
    G.vexnum++;
    return OK;
}

/***************************************************
 * 函数名称: DeleteVex
 * 初始条件：图G存在，v是G的一个顶点
 * 函数功能: 在图G中删除顶点v和与v相关的弧
 ***************************************************/
status DeleteVex(ALGraph &G,KeyType v) {
	int i = 0, j;
	ArcNode *p, *q;
	if(G.vertices[0].data.key != -1 && G.vertices[1].data.key == -1){
        return ERROR;      
    } //如果图中只有一个顶点，删除失败
	j = LocateVex(G, v);
	if(j == -1)
		return ERROR;
	p = G.vertices[j].firstarc;
	while(p) {//删除与顶点v相关的弧
		q = p;
		p = p->nextarc;
		free(q);
		G.arcnum--;
		i++;
	}
	G.vexnum--;//顶点数--
	for(i = j; i < G.vexnum; i++)
		G.vertices[i] = G.vertices[i+1];
	for(i = 0; i < G.vexnum; i++) {
		p = G.vertices[i].firstarc;
		while(p) {//删除与顶点v相关的弧
			if(p->adjvex == j) {
				if(p == G.vertices[i].firstarc) {
					G.vertices[i].firstarc = p->nextarc;
					free(p);
					p = G.vertices[i].firstarc;
				} else {
					q -> nextarc = p -> nextarc;
					free(p);
					p = q -> nextarc;
				}
			} else {
				if(p->adjvex > j)//如果顶点编号大于j，编号减一
					p->adjvex--;
				q = p;
				p = p->nextarc;
			}
		}
	}
	return OK;
}



/********************************************************************
 * 函数名称: InsertArc
 * 初始条件:图G存在，v、w是G的顶点
 * 函数功能: 在图G中增加弧<v,w>，如果图G是无向图，还需要增加<w,v>
 ********************************************************************/
status InsertArc(ALGraph &G,KeyType v,KeyType w) {
	ArcNode *p;
	int  i, j;
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if(i == -1 || j == -1)
		return ERROR;
	p = G.vertices[i].firstarc;
	while(p) {
		if( p -> adjvex == j)return ERROR;//如果已经存在该边，返回ERROR
		p = p -> nextarc;
	}
	G.arcnum++;
    //添加弧
	p=(ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = j;
	p->nextarc = G.vertices[i].firstarc;
	G.vertices[i].firstarc = p;

	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = i;
	p->nextarc = G.vertices[j].firstarc;
	G.vertices[j].firstarc = p;
	return OK;
}

/*********************************************************************
 * 函数名称: DeleteArc
 * 初始条件:图G存在，v、w是G的顶点
 * 函数功能: 在图G中删除弧<v,w>，如果图G是无向图，还需要删除<w,v>
 *********************************************************************/
status DeleteArc(ALGraph &G, KeyType v, KeyType w) {
	ArcNode *p, *q;
	int i, j;
	// 查找v和w在G中的位置
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	// 如果未找到v或w，则删除操作失败
	if(i < 0 || j < 0)return ERROR;
	// 在顶点i的邻接表中查找指向顶点j的弧，并记录其前驱q和当前指针p
	p = G.vertices[i].firstarc;
	while(p && p->adjvex != j) {
		q = p;
		p = p->nextarc;
	}
	// 如果找到弧，则删除该弧
	if(p && p->adjvex == j) {
		if(p == G.vertices[i].firstarc){
			G.vertices[i].firstarc = p->nextarc;
		}else{
			q->nextarc = p->nextarc;
			free(p);
			G.arcnum--;
		}
	}else if(!p) return ERROR;	// 如果未找到弧，则删除操作失败

	// 在顶点j的邻接表中查找指向顶点i的弧，并记录其前驱q和当前指针p
	p = G.vertices[j].firstarc;
	while(p && p->adjvex != i) {
		q = p;
		p = p->nextarc;
	}
	// 如果找到弧，则删除该弧
	if(p && p->adjvex == i) {
		if(p == G.vertices[j].firstarc){
			G.vertices[j].firstarc=p->nextarc;
		}else{
			q->nextarc=p->nextarc;
			free(p);
		}
	}
	return OK;
}


/*************************************************
 * 函数名称: dfshelper
 * 初始条件：图G存在
 * 函数功能: 深度优先遍历，服务于DFSTraverse
 *************************************************/
void dfshelper(const ALGraph &G,int i ,int *visited,void (*visit)(VertexType)){
    visited[i] = 1;
    visit(G.vertices[i].data);
    ArcNode *p = G.vertices[i].firstarc;
    while(p){
        if(!visited[p->adjvex]){
            dfshelper(G,p->adjvex,visited,visit);
        }
        p = p->nextarc;
    }
    return;
}


/***********************************************************************************
 * 函数名称: DFSTraverse
 * 初始条件：图G存在
 * 函数功能: 进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
 ***********************************************************************************/
status DFSTraverse(const ALGraph &G,void (*visit)(VertexType))
{
    int k;
    if(G.vexnum == 0) return ERROR;
    int *visited;
	visited = (int*)malloc(sizeof(int)*G.vexnum);
    for(k = 0 ;k < G.vexnum ;k++){
        visited[k] = 0;
    }
    for(int i=0;i<G.vexnum;i++){
        if(!visited[i]){
            dfshelper(G,i,visited,visit);
        }
    }
    return OK;
}



/*************************************************************************************
 * 函数名称: BFSTraverse
 * 初始条件：图G存在
 * 函数功能: 进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
 *************************************************************************************/
status BFSTraverse(const ALGraph &G, void (*visit)(VertexType)) {
    if (G.vexnum == 0) return ERROR;

    int *visited;
    visited = (int*)malloc(sizeof(int) * G.vexnum);
    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            queueptr q = (queueptr)malloc(sizeof(queue));
            ArcNode *p;

            initqueue(q);
            visited[i] = 1;
            visit(G.vertices[i].data);
            enqueue(q, i);

            while (!isempty(q)) {
                dequeue(q, i);
                p = G.vertices[i].firstarc;

                while (p) {
                    if (!visited[p->adjvex]) {
                        visited[p->adjvex] = 1;
                        visit(G.vertices[p->adjvex].data);
                        enqueue(q, p->adjvex);
                    }
                    p = p->nextarc;
                }
            }

            free(q);
        }
    }

    free(visited);
    return OK;
}


/****************************
 * 函数名称: visit
 * 初始条件：图G存在
 * 函数功能: 访问节点一次
 ****************************/
void visit(VertexType v) {
	printf("               key = %d,others = %s\n",v.key,v.others);
}



/*****************************
 * 函数名称: SaveGraph
 * 初始条件：图G存在
 * 函数功能: 保存图为文件
 *****************************/
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE *fp;
    if(!G.vexnum)
        return INFEASIBLE;
    if (!(fp = fopen(FileName, "wb")))
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    { //写入每一个顶点
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
        for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc)
        { //顺序写入该顶点的每一个邻接点的位置
            fprintf(fp, "%d ", p->adjvex);
        }
        fprintf(fp, "%d ", -1); //邻接点结尾处写上-1
    }
    fprintf(fp, "%d %s ", -1, "nil"); //顶点结尾处写上-1
    fclose(fp);
    return OK;
}

/*****************************
 * 函数名称: LoadGraph
 * 初始条件:文件存在
 * 函数功能: 从文件中加载图
 *****************************/
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
//本函数调用栈的数据结构及其操作函数
{
    if (G.vexnum > 0)
        return  INFEASIBLE;
    FILE *fp;
    if (!(fp = fopen(FileName, "rb")))
        return ERROR;
    G.vexnum = G.arcnum = 0;
    KeyType key;          //存储从文件中读取顶点key值的临时变量
    int ConnectVerLocate; //存储读取的顶点邻接点的位置的临时变量
    char others[20];      //存储读取的顶点的data中others分量的临时变量
    stack S;              //定义栈
    iniStack(S);
    fscanf(fp, "%d ", &key);
    fscanf(fp, "%s ", others);
    for (int i = 0; key != -1 && G.vexnum < MAX_VERTEX_NUM; i++)
    { //创建顶点
        G.vertices[i].data.key = key;
        strcpy(G.vertices[i].data.others, others);
        G.vertices[i].firstarc = NULL;
        fscanf(fp, "%d ", &ConnectVerLocate);
        for (; ConnectVerLocate != -1;)
        { //建立顶点的邻接表
            //通过入栈出栈把顺序倒置，确保读取后顶点邻接表顺序与原图相同
            push(S, ConnectVerLocate);
            fscanf(fp, "%d ", &ConnectVerLocate);
        }
        for (ArcNode *p; !isEmptyStack(S);)
        {                              //栈不为空时循环
            ConnectVerLocate = pop(S); //出栈
            //从邻接表头部插入邻接点结点
            p = (ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex = ConnectVerLocate;
            p->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p;
            G.arcnum++; //图的边数自增
        }
        G.vexnum++;                        //图的顶点数自增
        fscanf(fp, "%d %s", &key, others); //读取下一顶点
    }
    G.arcnum/=2;
    G.kind=UDG;
    fclose(fp);
    return OK;
}

/*附加功能*/
/*****************************
 * 函数名称: VerticesSetLessThanK
 * 初始条件:图G存在
 * 函数功能: 返回与顶点v距离小于k的顶点集合result,并返回顶点个数count
 * 返回值：如果存在，返回OK，如果不存在，返回ERROR
 * 算法思路：BFS
 *****************************/
status VerticesSetLessThanK(ALGraph G,int v,int k,int *result,int *count){
    int dist[MAX_VERTEX_NUM];//dist[i]表示顶点v到顶点i的距离
    int visited[MAX_VERTEX_NUM];//visited[i]表示顶点i是否被访问过
    int i;
    for(i=0; i<G.vexnum; i++){
        dist[i] = -1;
        visited[i] = 0;
    }
    //v是结点关键字，要转换成数组索引
    v = LocateVex(G,v);
    if(v==-1)return ERROR;

    dist[v] = 0;
    visited[v] = 1;
    int queue[MAX_VERTEX_NUM];
    int front = 0,rear = 0;
    queue[rear++] = v;
    //BFS
    while(front < rear){
        int u = queue[front++];
        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL){
            int adjvex = p->adjvex;
            if(!visited[adjvex]){
                dist[adjvex] = dist[u] + 1;
                visited[adjvex] = 1;
                queue[rear++] = adjvex;
            }
            p = p->nextarc;
        }
    }
    *count = 0;
    for(i=0; i<G.vexnum; i++){
        if(dist[i]>=0 && dist[i]<k){
            result[(*count)++] = i;
        }
    }
    if(*count == 0){
        return ERROR;
    }
    return OK;
}
	
/*****************************
 * 函数名称: ShortestPathLength(G,v,w); 
 * 初始条件:图G存在
 * 函数功能: 返回顶点v与顶点w的最短路径的长度；
 * 算法思路：利用队列使用BFS，记录距离
 *****************************/

int ShortestPathLength(ALGraph G, KeyType v, KeyType w) {
    int visited[MAX_VERTEX_NUM] = {0}; // 用于记录每个顶点是否被访问过
    int distance[MAX_VERTEX_NUM] = {0}; // 用于记录起点到每个顶点的距离
    int queue[MAX_VERTEX_NUM] = {0}; // 队列用于BFS
    int front = -1, rear = -1;
    int i, j;
    ArcNode *p;

    // 首先找到v所在的顶点下标i
    for (i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == v) {
            break;
        }
    }
    if (i == G.vexnum) { // v不在图G中
        return -1;
    }

    visited[i] = 1; // 标记i已经被访问
    distance[i] = 0; // 起点到起点的距离为0
    queue[++rear] = i; // 将i入队

    while (front != rear) { // BFS主循环
        i = queue[++front]; // 取出队首元素

        // 遍历i的所有邻接点
        p = G.vertices[i].firstarc;
        while (p != NULL) {
            j = p->adjvex; // 邻接点j的下标
            if (!visited[j]) { // j没有被访问过
                visited[j] = 1; // 标记j已经被访问
                distance[j] = distance[i] + 1; // j到起点的距离比i到起点的距离多1
                if (G.vertices[j].data.key == w) { // 找到了终点
                    return distance[j];
                }
                queue[++rear] = j; // 将j入队
            }
            p = p->nextarc;
        }
    }

    return -1; // 没有找到从v到w的路径
}


void DFS(ALGraph G, int v, int visited[]) {
    visited[v] = true;
    ArcNode* p = G.vertices[v].firstarc;
    while (p != NULL) {
        int w = p->adjvex;
        if (!visited[w]) {
            DFS(G, w, visited);
        }
        p = p->nextarc;
    }
}
/*****************************
 * 函数名称: ConnectedComponentsNums
 * 初始条件:图G存在
 * 函数功能: 返回图G的所有连通分量的个数
 * 算法思路：使用DFS，每次遍历就是找到了一个连通分量
 *****************************/
int ConnectedComponentsNums(ALGraph G) {
    int count = 0;
    int visited[MAX_VERTEX_NUM];
    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            DFS(G, i, visited);
            count++;
        }
    }
    return count;
}

