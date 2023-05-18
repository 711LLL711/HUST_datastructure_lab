#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR -1
#define INFEASIBLE -2
#define MAX 100
#define OVERFLOW -3
#define LISTSIZE 20//支持在20个树中操作
#define ARRSIZE 20

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


static int j,end=0,fail=0;
static int check[MAX]={0};
int nowkey;

/****************function definition******************/
/**
 * 函数名称: InitBiTree
 * 初始条件：二叉树T不存在
 * 操作结果: 构造空树二叉树T
 *
 */
status InitBiTree(BiTree &T) {
	T = (BiTree)malloc(sizeof(BiTNode));
	T-> lchild = NULL;
	T -> rchild = NULL;
	strcpy(T -> data.others,"#");
	T -> data.key = 0;//初始化二叉树,将左右指针指向空
	return OK;
}

/**
 * 函数名称: create
 * 操作结果: 根据definition先序序列递归构造二叉树结点
 * 注释:     服务于CreateBiTree函数
 *
 */
void create(BiTree &T,TElemType definition[])
{
    if(end || fail){
        return;
    }
    nowkey=definition[j++].key;
    if(nowkey==0){
        T=NULL;
    }else if(nowkey==-1){
        end=1;
        return;
    }else{
        if(check[nowkey]){
            fail=1;
            return;
        }else{
            check[nowkey]=1;
            T = (BiTree)malloc(sizeof(BiTNode));
            T->data=definition[j-1];
            create(T->lchild,definition);
            create(T->rchild,definition);
        }
    }
    return;
}

/**
 * 函数名称: DestroyBiTree
 * 初始条件：二叉树T存在
 * 操作结果: 销毁二叉树T
 *
 */
void DestroyBiTree(BiTree &T)
{
    if(T){
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T=NULL;
    }
    return;
}

/**
 * 函数名称: CreateBiTree
 * 初始条件：二叉树T存在
 * 操作结果: 操作结果是按definition构造二叉树T
 *   返回值：status类型
 *          如果关键字重复返回ERROR，创建成功返回OK
 *
 */
status CreateBiTree(BiTree &T,TElemType definition[])
{
    nowkey=definition[0].key;
    j = 0;
    create(T,definition);
    if(fail){
        return ERROR;
    }
    return OK;
}

/**
 * 函数名称: FreeNode
 * 注释：服务于ClearBiTree函数
 *
 */
void FreeNode(BiTree &T)
{
    if(T==NULL){
        return;
    }
    FreeNode(T->lchild);
    FreeNode(T->rchild);
    free(T);
    T=NULL;
}

/**
 * 函数名称: ClearBiTree
 * 初始条件：二叉树T已存在
 * 操作结果: 清空二叉树
 *
 */
status ClearBiTree(BiTree &T)
{
    if(T==NULL){
        return ERROR;
    }
    FreeNode(T);
    InitBiTree(T);
    return OK;
}

/**
 * 函数名称: max
 * 操作结果:返回两数最大值 
 * 注释：服务于BiTreeDepth函数
 */
int max(int a ,int b)
{
    return a > b?a:b;
}

/**
 * 函数名称: BiTreeDepth
 * 初始条件：二叉树T存在
 * 操作结果: 返回二叉树的深度
 *
 */
int BiTreeDepth(BiTree T)
{
    if(T==NULL){
        return 0;
    }
    return 1+max(BiTreeDepth(T->lchild),BiTreeDepth(T->rchild));
}

/**
 * 函数名称: LocateNode
 * 初始条件：二叉树T存在
 * 操作结果: 操作结果是返回查找到的结点指针，如无关键字为e的结点，返回NULL；
 * 注释：e是和T中结点关键字类型相同的给定值；
 *
 */
BiTNode* LocateNode(BiTree T,KeyType e)
{
    BiTree result=NULL,queue[100],now;
    int front=0,rear=1;
    if(T==NULL){
        return result;
    }
    queue[front]=T;
    while(rear > front){
        now=queue[front++];
        if(now->data.key==e){
            return now;
        }
        if(now->lchild!=NULL){
            queue[rear++]=now->lchild;
        }
        if(now->rchild!=NULL){
            queue[rear++]=now->rchild;
        }
    }
    return result;
}

/**
 * 函数名称: locate_parent
 * 初始条件：二叉树T存在
 * 操作结果: 前序遍历搜索关键字为e的结点，保存在p中，并且把该节点的父节点存在parent_p中
 *
 */
void locate_parent(BiTree T, BiTree parent, KeyType e, BiTree& p, BiTree& parent_p) 
{
    if (T) {
        if (T->data.key == e) { 
            p = T; 
            parent_p = parent;
            return;
        }
        locate_parent(T->lchild, T, e, p, parent_p); 
        locate_parent(T->rchild, T, e, p, parent_p); 
    }
}

/**
 * 函数名称: Assign
 * 初始条件：二叉树T已存在
 * 操作结果: 关键字为e的结点赋值为value
 * 注释：e是和T中结点关键字类型相同的给定值
 * 返回值：如果赋值后出现关键字重复，返回ERROR，复制成功返回OK
 *
 */
status Assign(BiTree &T, KeyType e, TElemType value) {
    BiTNode* p = LocateNode(T, e);
    if (p == NULL) {
        return INFEASIBLE;
    }
    BiTNode* search = LocateNode(T, value.key);
    if (search != NULL && search != p) {
        return ERROR;
    }
    p->data = value;
    return OK;
}

/**
 * 函数名称: GetSibling
 * 初始条件：二叉树T存在
 * 操作结果: 获取关键字为e的节点的兄弟节点
 *
 */
BiTNode* GetSibling(BiTree T, KeyType e) {
    if (!T) { 
        return NULL;
    }
    BiTNode* p = NULL;
    BiTNode* parent_p = NULL;
    locate_parent(T, NULL, e, p, parent_p); 
    if (!p || !parent_p || !(parent_p->lchild && parent_p->rchild)) { 
        return NULL;
    }
    if (p == parent_p->lchild) {
        return parent_p->rchild;
    } else { 
        return parent_p->lchild;
    }
}
/**
 * 函数名称: BiTreeEmpty
 * 初始条件：无
 * 操作结果: 二叉树判空
 *
 */
status BiTreeEmpty(BiTree T) {
	if(strcmp(T->data.others ,"#")!=0) return FALSE;
	else return TRUE;
}

/**
 * 函数名称: InsertNode
 * 初始条件：二叉树T存在
 * 操作结果: 根据LR为0或者1，插入结点c到T中，
 *          作为关键字为e的结点的左或右孩子结点，
 *          结点e的原有左子树或右子树则为结点c的右子树；
 * 注释: e是和T中结点关键字类型相同的给定值，LR为0或1，c是待插入结点；
 *      LR为-1时，作为根结点插入，原根结点作为c的右子树。
 * 返回值：status类型
 *         二叉树为空/找不到目标节点/插入节点后关键字重复，返回ERROR
 *         插入成功返回OK
 * 
 */
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
{
    BiTree insert=NULL,newnode,repeat;
    newnode=(BiTNode*)malloc(sizeof(BiTNode));
    newnode->lchild=NULL;
    newnode->rchild=NULL;
    if(LR==-1){
        newnode->data=c;
        newnode->rchild=T;
        T=newnode;
        return OK;
    }
    insert=LocateNode(T,e);
    repeat=LocateNode(T,c.key);
    if(insert==NULL){
        return INFEASIBLE;
    }
    if(repeat!=NULL){
        return ERROR;
    }
    newnode->data=c;
    switch(LR){
        case 0:
            newnode->rchild=insert->lchild;
            insert->lchild=newnode;
            break;
        case 1:
            newnode->rchild=insert->rchild;
            insert->rchild=newnode;
            break;
    }
    return OK;
}

/**
 * 函数名称: DeleteNode
 * 初始条件：二叉树T已存在
 * 操作结果: 删除T中关键字为e的结点；
 *          同时，如果关键字为e的结点度为0，删除即可；
 *          如关键字为e的结点度为1，用关键字为e的结点孩子代替被删除的e位置；
 *          如关键字为e的结点度为2，用e的左孩子代替被删除的e位置，
 *          e的右子树作为e的左子树中最右结点的右子树；
 *
 */
status DeleteNode(BiTree &T,KeyType e)
{
    int du=0,LR=0,lchildflag=0, rchildflag=0;
    if(T==NULL){
        return ERROR;
    }
    BiTree p = NULL ,search;
    BiTNode* parent_p = NULL;
    locate_parent(T, NULL, e, p, parent_p); 
    if(parent_p && parent_p->rchild==p){//parent_p=NULL,p为根节点
        LR=1;
    }
    if(p==NULL){
        return ERROR;//找不到目标节点
    }

    if(p->lchild){
        du++;
        lchildflag++;
    }
    if(p->rchild){
        du++;
        rchildflag++;
    }
    if(p==T){//删除根节点的情况单独处理
        switch (du){
            case 0:
                free(T);
                T=NULL;
                break;
            case 1:
                if(lchildflag==1){
                    T=T->lchild;
                }else{
                    T=T->rchild;
                } 
                free(p);
                break;
            case 2:
                T=T->lchild;
                for(search=p->lchild;search->rchild;search=search->rchild);
                search->rchild=p->rchild;
                free(p);
                break; 
        }
        return OK;
    }
    switch(du){
        case 0:
            if(LR==0){
                parent_p->lchild=NULL;
            }else{
                parent_p->rchild=NULL;
            }
            free(p);
            break;
        case 1:
            if(LR==0){
                if(lchildflag){
                    parent_p->lchild=p->lchild;
                }else{
                    parent_p->lchild=p->rchild;
                }    
            }else{
                if(lchildflag){
                    parent_p->rchild=p->lchild;
                }else{
                    parent_p->rchild=p->rchild;     
                }
            }
            free(p);
            break;
        case 2:
            for(search=p->lchild;search->rchild;search=search->rchild);
            search->rchild=p->rchild;
            if(LR==0){
                parent_p->lchild=p->lchild;
            }else{
                parent_p->rchild=p->lchild;
            }
            free(p);
            break;
    }
    return OK;
}


/**
 * 函数名称: visit
 * 初始条件：二叉树存在
 * 操作结果: 打印结点关键字
 *
 */
void visit(BiTree T)
{
    if(T){
        printf("%d %s\n",T->data.key,T->data.others);
    } 
    return;
}
/**
 * 函数名称: PreOrderTraverse
 * 初始条件：二叉树T存在
 * 操作结果: 先序遍历，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败。
 *
 */
void PreOrderTraverse(BiTree t,void (*visit)(BiTree))
{
    BiTree stack[MAX],p;
    int top=0;//置空栈
    if(t!=NULL){
        stack[top++]=t;
        while(top){
            p = stack[--top];
            //根节点退栈，访问根节点，左右子树入栈
            visit(p);
            if(p->rchild!=NULL){
                stack[top++]=p->rchild;
            }
            if(p->lchild!=NULL){
                stack[top++]=p->lchild;
            }
        }
    }
}


/**
 * 函数名称: InOrderTraverse
 * 初始条件：二叉树T存在
 * 操作结果: 中序遍历t，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败；
 *
 */
void InOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T==NULL){
        return;
    }
    InOrderTraverse(T->lchild ,visit);
    visit(T);
    InOrderTraverse(T->rchild ,visit);
    return;
}

/**
 * 函数名称: PostOrderTraverse
 * 初始条件：二叉树T存在
 * 操作结果: 序遍历t，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败。
 *
 */
void PostOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T==NULL){
        return;
    }
    PostOrderTraverse(T->lchild,visit);
    PostOrderTraverse(T->rchild,visit);
    visit(T);
    return;
}

/**
 * 函数名称: LevelOrderTraverse
 * 初始条件：二叉树T存在
 * 操作结果: 层序遍历t，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败。
 *
 */

void LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    BiTree queue[100];
    BiTNode* now;
    int front=0,rear=1;
    if(T==NULL){
        return;
    }
    queue[front]=T;
    while(rear > front){
        now=queue[front++];
        visit(now);
        if(now->lchild!=NULL){
            queue[rear++]=now->lchild;
        }
        if(now->rchild!=NULL){
            queue[rear++]=now->rchild;
        }
    }
    return;
}

/***********added function*****************/


/**
 * 函数名称: SaveBiTree
 * 初始条件：二叉树T存在
 * 操作结果: 将二叉树T的数据一先序保存在文件中
 *
 */
status SaveBiTree(BiTNode *T,char FileName[]) { //非递归先序储存
	FILE *fp;
	BiTree pforsave=T;
	BiTree stack[100];
	int top=0;
	if((fp=fopen(FileName,"wb"))==NULL) {
		//printf("存储发生错误\n");
		return ERROR;
	}
	do {
		while(pforsave) {
			if(top==MAX){
                return OVERFLOW;
            } 
			stack[top++]=pforsave;
			fprintf(fp," %d ",pforsave->data.key);
			fprintf(fp," %s ",pforsave->data.others);
			pforsave=pforsave->lchild;
		}
		fprintf(fp," %d ",0);
		if(top) {
			top--;
			pforsave=stack[top]->rchild;
		}
	} while(top||pforsave);
	fprintf(fp," %d ",0);
	fclose(fp);
	return OK;
}

/**
 * 函数名称: read
 * 初始条件：文件存在
 * 操作结果: 递归将文件中的数据读取到二叉树T中
 * 注释：    服务于LoadBiTree
 */
void read(BiTree &T,FILE *fp) {
	int definition;
	fscanf(fp," %d ",&definition);
	if(!definition) T=NULL;
	else {
		T=(BiTNode*)malloc(sizeof(BiTNode));
		T->data.key=definition;
		fscanf(fp," %s ",T->data.others);
		read(T->lchild,fp);
		read(T->rchild,fp);
	}
}

/**
 * 函数名称: LoadBiTree
 * 初始条件：文件存在
 * 操作结果: 将文件中的数据读取到二叉树T中
 *
 */

status LoadBiTree(BiTree &T,char FileName[]) {
	FILE *fp;
	if ((fp=fopen(FileName,"rb"))==NULL) {
		//printf("读取发生错误\n");
		return ERROR;
	}
	read(T,fp);
	fclose(fp);
	return OK;
}

 /**
 * 函数名称: MaxPathSum
 * 初始条件：二叉树T存在
 * 操作结果: 返回二叉树中的最大路径和，从一个结点到另一个节点的路径
 * 实现思路：最大路径和的求法是：对于每个结点，
 *          求出以该结点为根的子树的最大路径和，
 *          然后比较所有结点的最大路径和，取最大的那个
 *          以该结点为根的子树的最大路径和的求法是：
 *          如果该结点的左子树的最大路径和小于0，
 *          则以该结点的左子树为根的子树的最大路径和为0
 *          如果该结点的右子树的最大路径和小于0，
 *          则以该结点的右子树为根的子树的最大路径和为0
 *          以该结点为根的子树的最大路径和为：
 *          该结点的值+左子树的最大路径和+右子树的最大路径和
 * 
 */
int MaxPathSum(BiTree T, int &maxSum)
{
    if (T == NULL){
         return 0;
    }    
    int left = MaxPathSum(T->lchild, maxSum);
    int right = MaxPathSum(T->rchild, maxSum);
    if(left < 0)left=0;
    if(right < 0)right=0;
    if(T->data.key+max(left,right) > maxSum){
        maxSum=T->data.key+max(left,right);
    }
    return T->data.key + max(left, right);
}

/**
 * 函数名称: LowestCommonAncestor
 * 初始条件：二叉树T存在
 * 函数输入：二叉树T，关键字e1，e2
 * 操作结果: 该二叉树中e1节点和e2节点的最近公共祖先
 * 函数思路：如果e1和e2分别是T的左右子树的节点，
 *          那么T就是他们的最近公共祖先
 *           如果e1和e2都是T的左子树的节点，
 *           则在T的左子树中继续寻找他们的最近公共祖先
 *           如果e1和e2都是T的右子树的节点，
 *           则在T的右子树中继续寻找他们的最近公共祖先
 */
BiTree LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2)
{
   if(T==NULL || T->data.key==e1 || T->data.key==e2)
       return T;
    BiTree left = LowestCommonAncestor(T->lchild, e1, e2);
    BiTree right = LowestCommonAncestor(T->rchild, e1, e2);
    if(left!=NULL && right!=NULL)
        return T;
    if(left!=NULL)
        return left;
    if(right!=NULL)
        return right;
    return NULL;
}

/**
 * 函数名称: InvertTree
 * 初始条件：线性表L已存在
 * 操作结果: 将T翻转，使其所有节点的左右节点互换
 *
 */
void InvertTree(BiTree T)
{
    if(T == NULL)
        return;
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
}


/**
 * 函数名称: printTree
 * 初始条件：线性表L已存在
 * 操作结果: 将树形图形象的打印出来
 *
 */
void printTree(BiTree T, int type, int level)
{
	int i;
	if (T==NULL){
        return;
    }
	printTree(T->rchild, 2, level+1);
	switch (type)
	{
        case 0:
            printf("%2d%s\n", T->data.key,T->data.others);
            break;
        case 1:
            for (i = 0; i < level; i++)	
                printf("\t");
            printf("\\%2d%s\n", T->data.key,T->data.others);
            break;
        case 2:
            for (i = 0; i < level; i++)	
                printf("\t");
            printf("/%2d%s\n", T->data.key,T->data.others);
            break;	
    }
	printTree(T->lchild,1,level+1);
}


