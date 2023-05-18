/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_NUM 10

typedef int status;
typedef int ElemType;

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

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

int main(){
	char filename[40];
	int op=1;
    int i,i_num=1,len,order=0;
    LinkList L[MAX_NUM];
    for (i = 0; i<MAX_NUM; i++)
	{
        L[i]=NULL;
	}
	ElemType e, cur_e, pre_e, next_e;
    while(op){
	system("cls");
    printf("\n\n");
    printf("      \t\t\tMenu for Linear Table On Sequence Structure \n");
	printf("  ����%d��˳�����ж���������ʼ�����Ȳ�������18,Ĭ���ڵ�һ�����ϲ���\n", MAX_NUM);
	printf("  ------------------------------------------------------------------------------\n");
	printf("**\t\t\t1. InitList        9.  NextElem\t\t\t         **\n");
	printf("**\t\t\t2. DestroyList     10. ListInsert\t\t\t **\n");
	printf("**\t\t\t3. ClearList       11. ListDelete \t\t\t **\n");
	printf("**\t\t\t4. ListEmpty       12. ListTraverse\t\t\t **\n");
	printf("**\t\t\t5. ListLength      13. reverseList\t\t\t **\n");
	printf("**\t\t\t6. GetElem         14. RemoveNthFromEnd\t\t\t **\n");
    printf("**\t\t\t7. LocateElem      15. sortlist\t\t\t         **\n");
    printf("**\t\t\t8. PriorElem       16. SaveList\t\t\t         **\n");
	printf("**\t\t\t17.LoadList                        \t\t\t **\n");
	printf("**\t\t\t0. Exit            ����ʱ��2023.4.12\t\t\t **\n");
	printf("**\t\t\t18.ChooseList(���Ƚ��д�ѡ����ѡ�����ĸ����Ͻ��в���)\n");
	printf("**\t\t\t��ʵ�������ļ�sss����ͨ������17���м���\n");
	printf("  ------------------------------------------------------------------------------\n");
	printf("��ѡ����Ĳ���[0-18]:\n");
	scanf("%d",&op);
    switch(op)
	{
	   case 1:
         //��һ������ǳ�ʼ�����Ա�
		 if(InitList(L[i_num])==OK)
         {

             printf("������Ҫ��������Ա�����\n");
             scanf("%s", filename);
             printf("���Ա����ɹ�\n");
         }
		     else printf("���Ա���ʧ�ܣ�\n");
		 getchar();getchar();
		 break;

	   case 2:
		 //�ڶ�������������������Ա�
		 if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
		 if(DestroyList(L[i_num])==OK)
         {
             printf("�������Ա�ɹ�!\n");
         }
         else printf("�������Ա�ʧ�ܣ�\n");
		 getchar();getchar();
		 break;

	   case 3:
		 //�����������Ա�
		 if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
         if(ClearList(L[i_num])==OK)
         {
            printf("���Ա����óɹ���\n");
         }
         else printf("���Ա�����ʧ�ܣ�\n");
		 getchar();getchar();
		 break;

	   case 4:
		 //�ж��Ƿ�Ϊ��
		 if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
         if(ListEmpty(L[i_num]))
         {
             printf("���Ա�Ϊ�գ�\n");
         }
         else printf("���Ա��ǿձ�\n");
		 getchar();getchar();
		 break;

	   case 5:
	       //�õ����Ա���
	       if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
         printf("���Ա��Ϊ%d\n",ListLength(L[i_num]));
		 getchar();getchar();
		 break;

	   case 6:
		 //�õ�ĳ��Ԫ��
	       if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
		 printf("������Ҫȡ����λ�ã�\n");
		 scanf("%d",&i);
		 if(GetElem(L[i_num],i,e)==OK)
		 printf("��%d������Ԫ���ǣ�%d\n",i,e);
		 else  printf("����λ�ô���\n");
		 getchar();getchar();
		 break;

	   case 7:
       //����eԪ�������Ա��е�λ��
		 if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
		 printf("����������Ԫ��ֵ��\n");
		 scanf("%d",&e);
         i = LocateElem(L[i_num],e);
		 if(i!=ERROR){
            printf("%dԪ�ص�һ�γ���λ�ڵ�%d��λ�ã�\n",e,i);
         }
		 else  printf("��Ԫ�ز�����!\n");
		 getchar();getchar();
		 break;

	   case 8:
	       //���ǰ�����
	       if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
		 printf("����������Ԫ�أ�\n");
		 scanf("%d",&cur_e);
		 PriorElem(L[i_num],cur_e,pre_e);
		 if(PriorElem(L[i_num],cur_e,pre_e)==OK)
		 printf("��ǰ��Ԫ��Ϊ��%d\n",pre_e);
		 else if(PriorElem(L[i_num],cur_e,pre_e)==OVERFLOW)
		 printf("˳�����û�и�Ԫ�أ�\n");
		 else  printf("�䲻����ǰ��Ԫ�أ�\n");
		 getchar();getchar();
		 break;


	   case 9:
	       //������ýڵ�
	       if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
         printf("����������Ԫ�أ�\n");
		 scanf("%d",&cur_e);
		 if(NextElem(L[i_num],cur_e,next_e)==OK){
            printf("����Ԫ��Ϊ��%d\n",next_e);
         }else if(NextElem(L[i_num],cur_e,pre_e)==OVERFLOW){
            printf("˳�����û�и�Ԫ�أ�\n");
         }else{
            printf("�䲻���ں��Ԫ�أ�\n");
         }
		 getchar();getchar();
		 break;

	   case 10:
	       //����Ԫ��
	       if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
		 printf("��������Ҫ���������Ԫ�أ�\n");
		 scanf("%d",&e);
		 printf("��������Ҫ���������Ԫ�ص�λ�ã�\n");
		 scanf("%d",&i);
		 if(ListInsert(L[i_num],i,e)==OK)
		 printf("��������Ԫ�سɹ���\n");
		 else
		 printf("��������Ԫ��ʧ�ܣ�\n");
		 getchar();getchar();
		 break;

	   case 11:
	       //ɾ��Ԫ��
	       if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
		 printf("��������Ҫɾ��������Ԫ�ص�λ�ã�\n");
		 scanf("%d",&i);
		 if(ListDelete(L[i_num],i,e)==OK)
		 printf("ɾ������Ԫ�سɹ���\n");
		 else
		 printf("ɾ������Ԫ��ʧ�ܣ�\n");
		 getchar();getchar();
		 break;

	   case 12:
	       //�������Ա��е�Ԫ��
	       if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
         if(ListEmpty(L[i_num])) {
            printf("���Ա��ǿձ�\n");
            getchar();getchar();
		    break;
         }
         ListTraverse(L[i_num]);
		 getchar();getchar();
		 break;

       case 13:
         //��ת���Ա�
         if(L[i_num]==NULL){
            printf("���Ա����ڣ�");
            getchar();getchar();
		    break;
         }
         if(reverseList(L[i_num])==OK){
            printf("��ת���");
         }
         getchar();getchar();
		 break;

       case 14:
       //ɾ��������n��Ԫ��
       if(L[i_num]==NULL){
        printf("���Ա��ǿձ�");
        getchar();getchar();
		 break;
       }
       len=ListLength(L[i_num]);
       printf("������Ҫɾ���ĵ����ڼ���λ��\n");
       scanf("%d" ,&i);
       if(i < 1 || i > len){
        printf("Ҫɾ����λ�ò��Ϸ�!");
        getchar();getchar();
		 break;
       }
       RemoveNthFromEnd(L[i_num] ,i);
       printf("ɾ���ɹ���");
       getchar();getchar();
		break;

       case 15:
       //���Ա�����
       if(L[i_num]==NULL){
        printf("���Ա��ǿձ�");
        getchar();getchar();
		break;
       }
       printf("����������ʽ��0����С����1���Ӵ�С\n");
        scanf("%d" ,&order);
        sortlist(L[i_num],order);
       printf("����ɹ�");
        getchar();getchar();
		break;

	  case 16:
           //�����ļ�
           if(L[i_num] == NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
         if(SaveList(L[i_num], filename)==OK){
            printf("�ļ�����ɹ�!�ļ���Ϊ%s\n",filename);
         }
		 getchar();getchar();
         break;

	   case 17:
        //�����ļ�����Ҫ������Ҫ���ص�����
        if((L[i_num]!=NULL)){
            printf("˳����Ѵ��ڣ��޷����أ�");
        }else{
            printf("������Ҫ���ص��ļ���:\n ");
		    scanf("%s", filename);
		    if(LoadList(L[i_num], filename)==OK){
                printf("�ļ����سɹ�\n");
		    }
        }
		getchar();getchar();
         break;

	   case 18:
           //ѡ�����ĸ�����в���
           printf("������Ҫ�ڵڼ��������:\n ");
           printf("*ֻ֧����%d��˳����ϲ���*\n",MAX_NUM);
		   scanf("%d",&i_num);
		   printf("���ڶԵ�%d������в���\n",i_num);
		 if((i_num<1)||(i_num>10))
		 {
		 	printf("��ѡ����ȷ��Χ��\n");
		 	i_num=1;
		 }
		 getchar(); getchar();
         break;

	   case 0:
         break;
	}//end of switch
  }//end of while
	printf("\t\t��ӭ�ٴ�ʹ�ñ�ϵͳ��\n");
}//end of main()
/*--------page 23 on textbook --------------------*/


/***************************************************************
*�������ƣ�IntiaList
*�������ܣ�����һ���յ����Ա�
*ע�ͣ���ʼ���������Ա�L�������Ѵ��ڣ���������ǹ���һ���յ����Ա�
*����ֵ���ͣ�status����
****************************************************************/
status InitList(LinkList &L)
{
    if(L!=NULL){
        return INFEASIBLE;
    }
    LNode *p;
    p = (LNode*)malloc(sizeof(LNode));
    p->next=NULL;
    L=p;
    return OK;
}

/***************************************************************
*�������ƣ�DestoryList
*�������ܣ��������Ա�
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ�����������������Ա�L
*����ֵ���ͣ�status����
****************************************************************/
status DestroyList(LinkList &L)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    LNode*p;
    for(p=L->next;p;p=L->next){
        L->next=p->next;
        free(p);
    }
    free(L);
    L=NULL;
    return OK;
}

/***************************************************************
*�������ƣ�ClearList
*�������ܣ�����˳���
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L����Ϊ�ձ�
*����ֵ���ͣ�status����
****************************************************************/

status ClearList(LinkList &L)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    LNode* p;
    for(p=L->next;p;p=L->next){
        L->next=p->next;
        free(p);
    }
    return OK;
}

/***************************************************************
*�������ƣ�ListEmpty
*�������ܣ��ж����Ա��Ƿ�Ϊ��
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE��
*����ֵ���ͣ�status����
****************************************************************/
status ListEmpty(LinkList L)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    if(L->next==NULL){
        return TRUE;
    }
    return FALSE;
}

/***************************************************************
*�������ƣ�ListLength
*�������ܣ������Ա�ı�
*ע�ͣ���ʼ���������Ա��Ѵ��ڣ���������Ƿ���L������Ԫ�صĸ�����
*����ֵ���ͣ�status����
****************************************************************/
int ListLength(LinkList L)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    LNode* p;
    int cnt=0;
    for(p = L->next ;p;p=p->next){
        cnt++;
    }
    return cnt;
}


/***************************************************************
*�������ƣ�GetElem
*�������ܣ��õ�ĳһ��Ԫ�ص�ֵ
*ע�ͣ���ʼ���������Ա��Ѵ��ڣ�1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ
*����ֵ���ͣ�status����
****************************************************************/
status GetElem(LinkList L,int i,ElemType &e)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    int index=1;
    LNode* p;
    if(i < 1){
        return ERROR; 
    }
    for(p=L->next;p ;p=p->next){
        if(index==i){
            e = p->data;
            return OK;
        }
        index++;
    }
    return ERROR;
}
/***************************************************************
*�������ƣ�LocateElem
*�������ܣ�����Ԫ��
*ע�ͣ���������Ա��д��ڣ����������Ա��е�λ��
*����ֵ���ͣ�status����
****************************************************************/
status LocateElem(LinkList L,ElemType e)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    LNode* p;
    int index=1;
    for(p =L->next ;p ;p=p->next){
        if(p->data==e){
            return index;
        }
        index++;
    }
    return ERROR;
}


/***************************************************************
*�������ƣ�PriorElem
*�������ܣ���Ԫ�ص�ǰ��
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ������������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ����
       ����pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶��塣
*����ֵ���ͣ�status����
****************************************************************/
status PriorElem(LinkList L,ElemType e,ElemType &pre)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    LNode* p ,*prior;
    for(p =L->next;p ;prior=p,p = p->next){
        if(p->data==e){
            if(p==L->next){
                return ERROR;
            }else{
                pre=prior->data;
                return OK;
            }
        }
    }
    return OVERFLOW;
}
/***************************************************************
*�������ƣ�NextElem
*�������ܣ����̽ڵ�
*�����������ʼ���������Ա�L�Ѵ��ڣ������������cur_e��L������Ԫ�أ��Ҳ������һ����
           ����next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶��塣
*����ֵ���ͣ�status����
****************************************************************/
status NextElem(LinkList L,ElemType e,ElemType &next)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    LNode* p;
    for(p =L->next;p ;p = p->next){
        if(p->data==e){
            if(p->next==NULL){
                return ERROR;
            }else{
                next=p->next->data;
                return OK;
            }
        }
    }
    return OVERFLOW;
}


/***************************************************************
*�������ƣ�ListInsert
*�������ܣ�����Ԫ��
*ע�ͣ���ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)+1��
*      �����������L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e
*����ֵ���ͣ�status����
****************************************************************/
status ListInsert(LinkList &L,int i,ElemType e)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    if(i<1){
        return ERROR;
    }
    LNode* p ,*newnode;
    newnode=(LNode*)malloc(sizeof(LNode));
    newnode->data=e;
    if(i==1){
        newnode->next=L->next;
        L->next=newnode;
        return OK;
    }
    int cnt=0;
    for(p = L->next ;p;p=p->next){
        cnt++;
        if(cnt==i -1){
           newnode->next = p->next;
            p->next=newnode;
            return OK;
        }
    }
    free(newnode);
    return ERROR;
}

/***************************************************************
*�������ƣ�ListDelete
*�������ܣ�ɾ��Ԫ��
*ע�ͣ���ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)��
*      ���������ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
*����ֵ���ͣ�status����
****************************************************************/
status ListDelete(LinkList &L,int i,ElemType &e)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    if(i<1){
        return ERROR;
    }
    LNode* p ,*del;
    int cnt=0;
    for(p=L ;p->next && cnt<i -1;){
        p=p->next;
        cnt++;
    }
    if(p->next==NULL){
        return ERROR;
    }
    del=p->next;
    e=del->data;
    p->next=del->next;
    free(del);
    return OK;
}

/***************************************************************
*�������ƣ�ListTraverse
*�������ܣ�����˳���
*ע�ͣ����˳����ֵ
*����ֵ���ͣ�status����
****************************************************************/
status ListTraverse(LinkList L)
{
    if(L==NULL){
        return INFEASIBLE;
    }
    if(L->next==NULL){
        return ERROR;
    }
    LNode* p;
    printf("\n---------------------------- all elements -------------------------------------\n");
    for(p =L->next ;p ;p =p->next){
        printf("%d" ,p->data);
        if(p->next){
            printf(" ");
        }
    }
    printf("\n--------------------------------- end -----------------------------------------\n");
    return OK;
}

/***************************************************************
*�������ƣ�SaveList
*�������ܣ��������Ա�
*ע�ͣ������Ա��棬�ο���¼B
*����ֵ���ͣ�status
****************************************************************/
status SaveList(LinkList L,char FileName[])
{
    if(L==NULL){
        return INFEASIBLE;
    }
    FILE* fp;
    LNode* p;
    fp=fopen(FileName,"wb");
    if(fp==NULL){
        return ERROR;
    }
    for(p=L->next ;p ;p=p->next){
        fprintf(fp,"%d " ,p->data);
    }
    fclose(fp);
    return OK;
}

/***************************************************************
*�������ƣ�LoadList
*�������ܣ������ļ�
*ע�ͣ������ļ����Ա㹦�ܵĲ��ԣ��ļ���Ҫ��ȷ
*����ֵ���ͣ�status����
****************************************************************/
status LoadList(LinkList &L,char FileName[]){
    if(L!=NULL){
        return INFEASIBLE;
    }
    LNode* p ,*now;
    p=(LNode*)malloc(sizeof(LNode));
    p->next=NULL;
    L=p;
    now=L;
    FILE* fp;
    int c;
    fp=fopen(FileName,"rb");
    if(fp==NULL){
        return ERROR;
    }
    while(fscanf(fp,"%d " ,&c)==1){
        LNode* node=(LNode*)malloc(sizeof(LNode));
        node->data=c;
        node->next=NULL;
        now->next=node;
        now=node;
    }
    fclose(fp);
    return OK;
}
/***************************************************************
*�������ƣ�reverseList
*�������ܣ���ת���Ա�
*ע�ͣ����Ա����ڻ�ձ���INFEASIBLE,��ת�ɹ�����OK
*����ֵ���ͣ�status����
****************************************************************/
status reverseList(LinkList L)
{
    LinkList p ,prior,post;
    if(L==NULL ||ListEmpty(L)){
        return INFEASIBLE;
    }
    if(ListLength(L)==1){
        return OK;
    }
    prior=L->next;
    p=prior->next;
    post=p->next;
    while(1){
        p->next=prior;
        if(post==NULL){
            break;
        }
        prior=p;
        p = post;
        post =post->next;
    } 
    L->next->next=NULL;
    L->next=p;
    return OK;
}
/***************************************************************
*�������ƣ�RemoveNthFromEnd
*�������ܣ�ɾ��������n��Ԫ��
*ע�ͣ����Ա����ڷ���INFEASIBLE,
ɾ��λ�ò��Ϸ�����ERROR
ɾ���ɹ�����OK
*����ֵ���ͣ�status����
****************************************************************/
status RemoveNthFromEnd(LinkList L,int n)
{
    int temp;
    int length=ListLength(L);
    if(L==NULL||L->next==NULL){
        return INFEASIBLE;
    }
    if(n < 1 || n > length){
        return ERROR;
    }
    ListDelete(L, length+1-n, temp);
    return OK;
}

/***************************************************************
*�������ƣ�sortlist
*�������ܣ����Ա��С��������
*ע�ͣ�
*����ֵ���ͣ�status����
****************************************************************/
status sortlist(LinkList L,int order)
{
	int t;
    if(L==NULL){
        return INFEASIBLE;
    }
    if(L->next==NULL){
        return OK;
    }
    LinkList ptr,done;
    if(order){
        //order=1,�Ӵ�С����
        for(done=NULL;L->next->next!=done;done=ptr){
            for(ptr =L->next ;ptr->next!=done ;){
                if(ptr->data < ptr->next->data){
                    t = ptr->data;
                    ptr->data=ptr->next->data;
                    ptr->next->data=t;
                }
                ptr = ptr->next;
            }
        }
    }else{
        //order=0,��С��������
        for(done=NULL;L->next->next!=done;done=ptr){
            for(ptr =L->next ;ptr->next!=done ;){
                if(ptr->data > ptr->next->data){
                    t = ptr->data;
                    ptr->data=ptr->next->data;
                    ptr->next->data=t;
                }
                ptr = ptr->next;
            }
        }
    }
    return OK;
}


