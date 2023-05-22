/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 0
#define FALSE -3
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_NUM 10

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;
	int listsize;
}SqList;

/*-----page 19 on textbook ---------
*------functiom declaration---------*/
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

/*--------------------------------------------*/
int main(void){
    char filename[40];
    int op=1;//chosen option
    int i,order=0;
    int i_num=1;
    SqList L[MAX_NUM+1];
    for(i=0;i<MAX_NUM+1;i++)
    {
        L[i].elem = NULL;
        L[i].listsize = 0;
        L[i].length = 0;
    }
    //�����forѭ������������û�д洢�ռ�����Ա�
    ElemType e, cur_e , pre_e, next_e;
    int k;
  while(op){
      
	system("cls");	//��������
    printf("\n\n");
	printf("      \t\t\tMenu for Linear Table On Sequence Structure \n");
	printf("  ����%d��˳�����ж���������ʼ�����Ȳ�������15,Ĭ���ڵ�һ�����ϲ���\n", MAX_NUM);
	printf("  ------------------------------------------------------------------------------\n");
	printf("**\t\t\t1. IntiaList       7.  LocateElem\t\t\t**\n");
	printf("**\t\t\t2. DestroyList     8.  PriorElem\t\t\t**\n");
	printf("**\t\t\t3. ClearList       9.  NextElem \t\t\t**\n");
	printf("**\t\t\t4. ListEmpty       10. ListInsert\t\t\t**\n");
	printf("**\t\t\t5. ListLength      11. ListDelete\t\t\t**\n");
	printf("**\t\t\t6. GetElem         12. ListTraverse\t\t\t**\n");
	printf("**\t\t\t13.SaveList	   14. LoadList\t\t\t        **\n");
    printf("**\t\t\t15.Maxsubarray	   16. subarraynum\t\t\t**\n");
    printf("**\t\t\t17.sortlist	                   \t\t\t**\n");
	printf("**\t\t\t0. Exit            ����ʱ�䣺2023.4.6\t\t\t**\n");
	printf("**\t\t\t18.ChooseList(���Ƚ��д�ѡ����ѡ�����ĸ����Ͻ��в���)\t**\n");
	printf("**\t\t\t����ʵ�������ļ�����ͨ������14���м���\t\t\t**\n");
	printf("  -----------------------------------------------------------------------------\n");
	printf("��ѡ����Ĳ���[0--18]:\n");
	scanf("%d",&op);//ѡ��op��ֵ,����switch
    switch(op){
	   case 1:
         //��ʼ�����Ա�
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
		 //�������Ա�
		 if(L[i_num].elem==NULL)
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
		 //�������Ա�
		 if(L[i_num].elem==NULL)
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
		 if(L[i_num].elem==NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
         if(ListEmpty(L[i_num])==TRUE)
         {
             printf("���Ա�Ϊ�գ�\n");
         }
         else printf("���Ա��ǿձ�\n");
		 getchar();getchar();
		 break;

	   case 5:
	       //�õ����Ա���
	       if(L[i_num].elem==NULL)
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
	     if(L[i_num].elem==NULL)
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
	       //ȷ��Ԫ��λ��
           	if(L[i_num].elem==NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
         printf("����������Ԫ��ֵ��\n");
		 scanf("%d",&e);
         if(LocateElem(L[i_num],e)==ERROR){
            printf("��Ԫ�ز�����!\n");
         }else{
            i=LocateElem(L[i_num],e);
            printf("%dԪ�ص�һ�γ���λ�ڵ�%d��λ�ã�\n",e,i);
         }
		 getchar();getchar();
		 break;

	   case 8:
	       //���ǰ�����
           	if(L[i_num].elem==NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }

         printf("����������Ԫ�أ�\n");
		 scanf("%d",&cur_e);

		 if(PriorElem(L[i_num],cur_e,pre_e)==OK)
		 printf("��ǰ��Ԫ��Ϊ��%d\n",pre_e);
		 else if(PriorElem(L[i_num],cur_e,pre_e)==OVERFLOW)
		 printf("˳�����û�и�Ԫ�أ�\n");
		 else  printf("�䲻����ǰ��Ԫ�أ�\n");
		 getchar();getchar();
		 break;

	   case 9:
	       //������ýڵ�
         printf("����������Ԫ�أ�\n");
		 scanf("%d",&cur_e);

	     if(L[i_num].elem==NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
		 if(NextElem(L[i_num],cur_e,next_e)==OK){
		    printf("����Ԫ��Ϊ��%d\n",next_e);
         }
		 else if(NextElem(L[i_num],cur_e,pre_e)==FALSE){
		    printf("�䲻���ں��Ԫ�أ�\n");
         }
		 else{
            printf("˳�����û�и�Ԫ�أ�\n");
         }
		 getchar();getchar();
		 break;

	   case 10:
	       //����Ԫ��
	     if(L[i_num].elem==NULL)
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
	       if(L[i_num].elem==NULL)
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
            
	     if(L[i_num].elem==NULL)
         {
             printf("���Ա�����!\n");
             getchar();getchar();
             break;
         }
         if(L[i_num].length==0)
         {
            printf("���Ա��ǿձ�\n");
            getchar();getchar();
            break;
         }
        ListTraverse(L[i_num]);
		 getchar();getchar();
		 break;

       case 13:
           //�����ļ�
           if(L[i_num].elem == NULL)
         {
             printf("���Ա�����!�޷����棡\n");
             getchar();getchar();
             break;
         }
         if(SaveList(L[i_num], filename)==OK){
            printf("�ļ�����ɹ�\n�ļ���Ϊ%s\n",filename);
         }
		getchar();getchar();
         break;

       case 14:
        //�����ļ�����Ҫ������Ҫ���ص�����
        if(L[i_num].elem!=NULL){
            printf("���Ա��Ѵ��ڣ��޷����أ�");
            getchar();getchar();
            break;
        }
         printf("������Ҫ���ص��ļ���:\n ");
		 scanf("%s", filename);
		 if(LoadList(L[i_num], filename)==OK)
            {
                printf("�ļ����سɹ�\n");
		    }else{
                printf("�ļ�����ʧ�ܣ�");
            }
         break;

       case 15:
           //���������������
           if(L[i_num].elem==NULL){
                printf("���Ա����ڣ�");
                getchar(); getchar();
                break;
           }
           printf("�������������Ϊ%d" ,Maxsubarray(L[i_num]));
           getchar();getchar();
           break;

        case 16:
           //���Ϊk����������ĸ���
           if(L[i_num].elem==NULL){
                printf("���Ա����ڣ�");
                getchar(); getchar();
                break;
           }
           printf("������͵Ĵ�С\n");
           scanf("%d" ,&k);
           printf("��Ϊk����������ĸ���Ϊ%d" ,subarraynum(L[i_num] ,k));
           getchar(); getchar();
            break;

       case 17:
           //���Ա�����
           if(L[i_num].elem==NULL){
                printf("���Ա����ڣ�");
                getchar(); getchar();
                break;
           }
           printf("����������ʽ��0����С����1���Ӵ�С\n");
           scanf("%d" ,&order);
           sortlist(L[i_num],order);
           printf("������ɣ�");
           getchar(); getchar();
           break;

       case 18:
           //ѡ�����ĸ�����в���
           printf("������Ҫ�ڵڼ��������:\n ");
           printf("*ֻ֧����%d��˳����ϲ���*\n",MAX_NUM);
		   scanf("%d",&i_num);
           	 if((i_num<1)||(i_num>MAX_NUM))
		    {
		 	printf("��ѡ����ȷ��Χ��Ĭ�϶Ե�һ�����Ա���в���\n");
		 	i_num=1;
		    }
		   printf("���ڶԵ�%d������в���\n",i_num);
           getchar(); getchar();
         break;

	   case 0:
        //�˳��˵����˳���������
         break;
	}//end of switch
  }//end of while

  printf("��ӭ�´���ʹ�ñ�ϵͳ!\n");
  system("pause");
  return 0;
}//end of main()

/******************function defination*************************/

/***************************************************************
*�������ƣ�IntiaList
*�������ܣ�����һ���յ����Ա�
*ע�ͣ���ʼ���������Ա�L�������Ѵ��ڣ���������ǹ���һ���յ����Ա�
*����ֵ���ͣ�status����
****************************************************************/
status InitList(SqList& L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    if(L.elem){
        return INFEASIBLE;
    }
    L.elem =(ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    return OK;
}


/***************************************************************
*�������ƣ�DestoryList
*�������ܣ��������Ա�
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ�����������������Ա�L
*����ֵ���ͣ�status����
****************************************************************/
status DestroyList(SqList& L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    L.length=0;
    L.listsize=0;
    free(L.elem);
    L.elem=NULL;
    return OK;
}


/***************************************************************
*�������ƣ�ClearList
*�������ܣ�����˳���
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L����Ϊ�ձ�
*����ֵ���ͣ�status����
****************************************************************/
status ClearList(SqList& L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    L.length=0;
    free(L.elem);
    return OK;
    /********** End **********/
}



/***************************************************************
*�������ƣ�ListEmpty
*�������ܣ��ж����Ա��Ƿ�Ϊ��
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE��
*����ֵ���ͣ�status����
****************************************************************/
status ListEmpty(SqList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem==NULL){
        return INFEASIBLE;
    } 
    if(L.length==0){
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
status ListLength(SqList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if(L.elem==NULL){
        return INFEASIBLE;
    }
        return L.length;
}


/***************************************************************
*�������ƣ�GetElem
*�������ܣ��õ�ĳһ��Ԫ�ص�ֵ
*ע�ͣ���ʼ���������Ա��Ѵ��ڣ�1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ
*����ֵ���ͣ�status����
****************************************************************/
status GetElem(SqList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    if(i < 1 || i > L.length){
        return ERROR;
    }
        e = L.elem[i-1];
        return OK;
}


/***************************************************************
*�������ƣ�LocateElem
*�������ܣ�����Ԫ��
*ע�ͣ���ʼ���������Ա��Ѵ��ڣ���������Ƿ���L�е�1����e�����ϵcompare����
       ��ϵ������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0��
*����ֵ���ͣ�status����
****************************************************************/
int LocateElem(SqList L,ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
{
    int i;
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    for(i = 0 ;i < L.length ;i++){
        if(L.elem[i]==e){
            return i+1;
        }
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
status PriorElem(SqList L,ElemType e,ElemType &pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    int i;
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    for(i = 0 ;i < L.length ;i++){
        if(e==L.elem[i]){
            if(i==0){
                return ERROR;
            }
                pre=L.elem[i-1];
                return OK;
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
status NextElem(SqList L,ElemType e,ElemType &next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    
    int i;
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    for(i = 0 ;i < L.length ;i++){
        if(e==L.elem[i]){
            if(i==L.length-1){
                return FALSE;
            }
                next=L.elem[i+1];
                return OK;
        }
    }
    return ERROR;
}


/***************************************************************
*�������ƣ�ListInsert
*�������ܣ�����Ԫ��
*ע�ͣ���ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)+1��
*      �����������L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e
*����ֵ���ͣ�status����
****************************************************************/
status ListInsert(SqList &L,int i,ElemType e)
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    int j;
    ElemType* newbase;
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    if(i<1 || i > L.length+1){
        return ERROR;
    }
    if(L.length>=L.listsize){
        newbase=(ElemType*)realloc(L.elem,sizeof(ElemType)*(L.listsize+LISTINCREMENT));
        if(newbase==NULL){
            return OVERFLOW;
        }
        L.elem=newbase;
        L.listsize+=LISTINCREMENT;
    }
    for(j = L.length - 1; j>=i-1 ;j--){
        L.elem[j+1]=L.elem[j];
    }
    L.elem[i - 1]=e;
    L.length++;
    return OK;
}


/***************************************************************
*�������ƣ�ListDelete
*�������ܣ�ɾ��Ԫ��
*ע�ͣ���ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)��
*      ���������ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
*����ֵ���ͣ�status����
****************************************************************/
status ListDelete(SqList &L,int i,ElemType &e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    int j;
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    if(i<1 || i >L.length){
        return ERROR;
    }
    e=L.elem[i - 1];
    for(j = i - 1 ; j <L.length-1;j++){
        L.elem[j] = L.elem[j+1];
    }
    L.length--;
    return OK;
}


/***************************************************************
*�������ƣ�ListTraverse
*�������ܣ�����˳���
*ע�ͣ����˳����ֵ
*����ֵ���ͣ�status����
****************************************************************/
status ListTraverse(SqList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    int i;
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    if(L.length==0){
        return ERROR;
    }
    printf("\n-----------all elements -----------------------\n");
        for(i = 0 ; i < L.length ;i++){
            printf("%d" ,L.elem[i]);
            if(i < L.length-1){
                printf(" ");
            }
        }
    printf("\n------------------ end ------------------------\n");
    return OK;
}


/****************below are the added function*****************/

/***************************************************************
*�������ƣ�SaveList
*�������ܣ��������Ա�
*ע�ͣ������Ա��棬�ο���¼B
*����ֵ���ͣ�status
****************************************************************/
status  SaveList(SqList L,char FileName[])
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    FILE*p;
    int i;
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    p=fopen(FileName ,"wb");
    if(p!=NULL){
        for(i = 0 ;i < L.length ;i++){
            fprintf(p,"%d " ,L.elem[i]);
        }
    }else{
        return ERROR;
    }
    fclose(p);
    return OK;
}


/***************************************************************
*�������ƣ�LoadList
*�������ܣ������ļ�
*ע�ͣ������ļ����Ա㹦�ܵĲ��ԣ��ļ���Ҫ��ȷ
*����ֵ���ͣ�status����
****************************************************************/
status  LoadList(SqList &L,char FileName[])
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    FILE* p;
    int c,j=0;
    ElemType* newbase;

    if(L.elem){
        return INFEASIBLE;
    }
        L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L.length=0;
        L.listsize=LIST_INIT_SIZE;

        p=fopen(FileName ,"rb");
       while((fscanf(p,"%d",&c))!=EOF)   {
            if(L.length>=L.listsize){
                newbase=(ElemType*)realloc(L.elem,sizeof(ElemType)*(L.listsize+LISTINCREMENT));
                if(newbase==NULL){
                    return OVERFLOW;
                }
                L.elem=newbase;
                L.listsize+=LISTINCREMENT;
            }
            L.elem[j++]=c;
            L.length++;
        }
    fclose(p);
    return OK;
}


/***************************************************************
*�������ƣ�Maxsubarray
*�������ܣ��ҳ������͵�����������
*ע�ͣ��������Ա��е�Ԫ�أ�����̰���㷨�������ǰ�ۼӺ�Ϊ0�����½����
       �����ǰ�ۼӺ�Ϊ��������ǰ�ۼӺ�����Ϊ0����ʾ�Ӹ�λ�����¿�ʼ���
*����ֵ���ͣ�int����,����������
****************************************************************/
int Maxsubarray(SqList L)
{
    int maxsum=INT_MIN ,cursum=0;
    int i;
    for(i = 0 ;i < L.length ;i++){
        cursum+=L.elem[i];
        if(cursum > maxsum){
            maxsum=cursum;
        }
        if(cursum < 0){
            cursum=0;
        }
    }
    return maxsum;
}


/***************************************************************
*�������ƣ�subarraynum
*�������ܣ��ҳ���Ϊk����������ĸ���
*ע�ͣ��������ҵķ���
*����ֵ���ͣ�int����,���غ�Ϊk����������ĸ���
****************************************************************/
int subarraynum(SqList L ,ElemType k)
{
    int i ,j ,sum=0,cnt=0;
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    for(i = 0 ;i < L.length ;i++){
        for(j = i ;j < L.length ;j++){
            sum+=L.elem[j];
            if(sum==k){
                cnt++;
            }
        }
        sum=0;
    }
    return cnt;
}


/***************************************************************
*�������ƣ�sortlist
*�������ܣ���L��С��������
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L��С�������򣻲��õ���ð������ķ���
*����ֵ���ͣ�status
****************************************************************/
status sortlist(SqList L,int order)
{
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    int i ,j; 
    ElemType t;
    //order=1�Ӵ�С����order=0��С��������
    if(order==1){
        for(i = 0 ;i < L.length - 1;i++){
            for(j  = 0 ;j < L.length - 1 - i ;j++){
                if(L.elem[j] < L.elem[j+1]){
                    t = L.elem[j];
                    L.elem[j] =L.elem[j+1];
                    L.elem[j+1]=t;
                }
            }
        }
    }else{
        for(i = 0 ;i < L.length - 1;i++){
            for(j  = 0 ;j < L.length - 1 - i ;j++){
                if(L.elem[j] > L.elem[j+1]){
                    t = L.elem[j];
                    L.elem[j] =L.elem[j+1];
                    L.elem[j+1]=t;
                }
            }
        }
    }
    return OK;
}


