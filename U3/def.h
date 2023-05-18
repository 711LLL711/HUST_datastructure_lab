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
#define LISTSIZE 20//֧����20�����в���
#define ARRSIZE 20

typedef int status;
typedef int KeyType; 
typedef struct {
		KeyType  key;
		char others[ARRSIZE];
} TElemType; //������������Ͷ���


typedef struct BiTNode{  //����������Ķ���
		TElemType  data;
		struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

typedef struct {
	BiTree T;//�����������õ�ָ��T
	char name[ARRSIZE];//���ڱ�����������
}LElemType;

typedef struct {
	LElemType tree[LISTSIZE];//��������в���
	int length;
	int listsize;
}SqList;//���Ա�������


static int j,end=0,fail=0;
static int check[MAX]={0};
int nowkey;

/****************function definition******************/
/**
 * ��������: InitBiTree
 * ��ʼ������������T������
 * �������: �������������T
 *
 */
status InitBiTree(BiTree &T) {
	T = (BiTree)malloc(sizeof(BiTNode));
	T-> lchild = NULL;
	T -> rchild = NULL;
	strcpy(T -> data.others,"#");
	T -> data.key = 0;//��ʼ��������,������ָ��ָ���
	return OK;
}

/**
 * ��������: create
 * �������: ����definition�������еݹ鹹����������
 * ע��:     ������CreateBiTree����
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
 * ��������: DestroyBiTree
 * ��ʼ������������T����
 * �������: ���ٶ�����T
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
 * ��������: CreateBiTree
 * ��ʼ������������T����
 * �������: ��������ǰ�definition���������T
 *   ����ֵ��status����
 *          ����ؼ����ظ�����ERROR�������ɹ�����OK
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
 * ��������: FreeNode
 * ע�ͣ�������ClearBiTree����
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
 * ��������: ClearBiTree
 * ��ʼ������������T�Ѵ���
 * �������: ��ն�����
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
 * ��������: max
 * �������:�����������ֵ 
 * ע�ͣ�������BiTreeDepth����
 */
int max(int a ,int b)
{
    return a > b?a:b;
}

/**
 * ��������: BiTreeDepth
 * ��ʼ������������T����
 * �������: ���ض����������
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
 * ��������: LocateNode
 * ��ʼ������������T����
 * �������: ��������Ƿ��ز��ҵ��Ľ��ָ�룬���޹ؼ���Ϊe�Ľ�㣬����NULL��
 * ע�ͣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��
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
 * ��������: locate_parent
 * ��ʼ������������T����
 * �������: ǰ����������ؼ���Ϊe�Ľ�㣬������p�У����ҰѸýڵ�ĸ��ڵ����parent_p��
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
 * ��������: Assign
 * ��ʼ������������T�Ѵ���
 * �������: �ؼ���Ϊe�Ľ�㸳ֵΪvalue
 * ע�ͣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ
 * ����ֵ�������ֵ����ֹؼ����ظ�������ERROR�����Ƴɹ�����OK
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
 * ��������: GetSibling
 * ��ʼ������������T����
 * �������: ��ȡ�ؼ���Ϊe�Ľڵ���ֵܽڵ�
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
 * ��������: BiTreeEmpty
 * ��ʼ��������
 * �������: �������п�
 *
 */
status BiTreeEmpty(BiTree T) {
	if(strcmp(T->data.others ,"#")!=0) return FALSE;
	else return TRUE;
}

/**
 * ��������: InsertNode
 * ��ʼ������������T����
 * �������: ����LRΪ0����1��������c��T�У�
 *          ��Ϊ�ؼ���Ϊe�Ľ�������Һ��ӽ�㣬
 *          ���e��ԭ������������������Ϊ���c����������
 * ע��: e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��LRΪ0��1��c�Ǵ������㣻
 *      LRΪ-1ʱ����Ϊ�������룬ԭ�������Ϊc����������
 * ����ֵ��status����
 *         ������Ϊ��/�Ҳ���Ŀ��ڵ�/����ڵ��ؼ����ظ�������ERROR
 *         ����ɹ�����OK
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
 * ��������: DeleteNode
 * ��ʼ������������T�Ѵ���
 * �������: ɾ��T�йؼ���Ϊe�Ľ�㣻
 *          ͬʱ������ؼ���Ϊe�Ľ���Ϊ0��ɾ�����ɣ�
 *          ��ؼ���Ϊe�Ľ���Ϊ1���ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�ã�
 *          ��ؼ���Ϊe�Ľ���Ϊ2����e�����Ӵ��汻ɾ����eλ�ã�
 *          e����������Ϊe�������������ҽ�����������
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
    if(parent_p && parent_p->rchild==p){//parent_p=NULL,pΪ���ڵ�
        LR=1;
    }
    if(p==NULL){
        return ERROR;//�Ҳ���Ŀ��ڵ�
    }

    if(p->lchild){
        du++;
        lchildflag++;
    }
    if(p->rchild){
        du++;
        rchildflag++;
    }
    if(p==T){//ɾ�����ڵ�������������
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
 * ��������: visit
 * ��ʼ����������������
 * �������: ��ӡ���ؼ���
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
 * ��������: PreOrderTraverse
 * ��ʼ������������T����
 * �������: �����������ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
 *
 */
void PreOrderTraverse(BiTree t,void (*visit)(BiTree))
{
    BiTree stack[MAX],p;
    int top=0;//�ÿ�ջ
    if(t!=NULL){
        stack[top++]=t;
        while(top){
            p = stack[--top];
            //���ڵ���ջ�����ʸ��ڵ㣬����������ջ
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
 * ��������: InOrderTraverse
 * ��ʼ������������T����
 * �������: �������t����ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܣ�
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
 * ��������: PostOrderTraverse
 * ��ʼ������������T����
 * �������: �����t����ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
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
 * ��������: LevelOrderTraverse
 * ��ʼ������������T����
 * �������: �������t����ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
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
 * ��������: SaveBiTree
 * ��ʼ������������T����
 * �������: ��������T������һ���򱣴����ļ���
 *
 */
status SaveBiTree(BiTNode *T,char FileName[]) { //�ǵݹ����򴢴�
	FILE *fp;
	BiTree pforsave=T;
	BiTree stack[100];
	int top=0;
	if((fp=fopen(FileName,"wb"))==NULL) {
		//printf("�洢��������\n");
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
 * ��������: read
 * ��ʼ�������ļ�����
 * �������: �ݹ齫�ļ��е����ݶ�ȡ��������T��
 * ע�ͣ�    ������LoadBiTree
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
 * ��������: LoadBiTree
 * ��ʼ�������ļ�����
 * �������: ���ļ��е����ݶ�ȡ��������T��
 *
 */

status LoadBiTree(BiTree &T,char FileName[]) {
	FILE *fp;
	if ((fp=fopen(FileName,"rb"))==NULL) {
		//printf("��ȡ��������\n");
		return ERROR;
	}
	read(T,fp);
	fclose(fp);
	return OK;
}

 /**
 * ��������: MaxPathSum
 * ��ʼ������������T����
 * �������: ���ض������е����·���ͣ���һ����㵽��һ���ڵ��·��
 * ʵ��˼·�����·���͵����ǣ�����ÿ����㣬
 *          ����Ըý��Ϊ�������������·���ͣ�
 *          Ȼ��Ƚ����н������·���ͣ�ȡ�����Ǹ�
 *          �Ըý��Ϊ�������������·���͵����ǣ�
 *          ����ý��������������·����С��0��
 *          ���Ըý���������Ϊ�������������·����Ϊ0
 *          ����ý��������������·����С��0��
 *          ���Ըý���������Ϊ�������������·����Ϊ0
 *          �Ըý��Ϊ�������������·����Ϊ��
 *          �ý���ֵ+�����������·����+�����������·����
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
 * ��������: LowestCommonAncestor
 * ��ʼ������������T����
 * �������룺������T���ؼ���e1��e2
 * �������: �ö�������e1�ڵ��e2�ڵ�������������
 * ����˼·�����e1��e2�ֱ���T�����������Ľڵ㣬
 *          ��ôT�������ǵ������������
 *           ���e1��e2����T���������Ľڵ㣬
 *           ����T���������м���Ѱ�����ǵ������������
 *           ���e1��e2����T���������Ľڵ㣬
 *           ����T���������м���Ѱ�����ǵ������������
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
 * ��������: InvertTree
 * ��ʼ���������Ա�L�Ѵ���
 * �������: ��T��ת��ʹ�����нڵ�����ҽڵ㻥��
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
 * ��������: printTree
 * ��ʼ���������Ա�L�Ѵ���
 * �������: ������ͼ����Ĵ�ӡ����
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


