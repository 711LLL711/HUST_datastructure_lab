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
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
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
    //上面的for循环是用来生成没有存储空间的线性表
    ElemType e, cur_e , pre_e, next_e;
    int k;
  while(op){
      
	system("cls");	//用于清屏
    printf("\n\n");
	printf("      \t\t\tMenu for Linear Table On Sequence Structure \n");
	printf("  可在%d个顺序表进行多表操作，初始化请先操作功能15,默认在第一个表上操作\n", MAX_NUM);
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
	printf("**\t\t\t0. Exit            制作时间：2023.4.6\t\t\t**\n");
	printf("**\t\t\t18.ChooseList(请先进行此选项以选择在哪个表上进行操作)\t**\n");
	printf("**\t\t\t若本实验已有文件，可通过函数14进行加载\t\t\t**\n");
	printf("  -----------------------------------------------------------------------------\n");
	printf("请选择你的操作[0--18]:\n");
	scanf("%d",&op);//选择op的值,用于switch
    switch(op){
	   case 1:
         //初始化线性表
		 if(InitList(L[i_num])==OK)
         {

             printf("请输入要保存的线性表名称\n");
             scanf("%s", filename);
             printf("线性表创建成功\n");
         }
		     else printf("线性表创建失败！\n");
		 getchar();getchar();
		 break;

	   case 2:
		 //销毁线性表
		 if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }
		 if(DestroyList(L[i_num])==OK)
         {
             printf("销毁线性表成功!\n");
         }
         else printf("销毁线性表失败！\n");
		 getchar();getchar();
		 break;

	   case 3:
		 //重置线性表
		 if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }
         if(ClearList(L[i_num])==OK)
         {
            printf("线性表重置成功！\n");
         }
         else printf("线性表重置失败！\n");
		 getchar();getchar();
		 break;

	   case 4:
		 //判断是否为空
		 if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }
         if(ListEmpty(L[i_num])==TRUE)
         {
             printf("线性表为空！\n");
         }
         else printf("线性表不是空表！\n");
		 getchar();getchar();
		 break;

	   case 5:
	       //得到线性表长度
	       if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }
         printf("线性表表长为%d\n",ListLength(L[i_num]));
		 getchar();getchar();
		 break;

	   case 6:
	       //得到某个元素
	     if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }

         printf("请输入要取结点的位置：\n");
		 scanf("%d",&i);
		 if(GetElem(L[i_num],i,e)==OK)
		 printf("第%d个结点的元素是：%d\n",i,e);
		 else  printf("输入位置错误！\n");
		 getchar();getchar();
		 break;

	   case 7:
	       //确定元素位置
           	if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }
         printf("请输入数据元素值：\n");
		 scanf("%d",&e);
         if(LocateElem(L[i_num],e)==ERROR){
            printf("该元素不存在!\n");
         }else{
            i=LocateElem(L[i_num],e);
            printf("%d元素第一次出现位于第%d个位置！\n",e,i);
         }
		 getchar();getchar();
		 break;

	   case 8:
	       //求出前驱结点
           	if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }

         printf("请输入数据元素：\n");
		 scanf("%d",&cur_e);

		 if(PriorElem(L[i_num],cur_e,pre_e)==OK)
		 printf("其前驱元素为：%d\n",pre_e);
		 else if(PriorElem(L[i_num],cur_e,pre_e)==OVERFLOW)
		 printf("顺序表中没有该元素！\n");
		 else  printf("其不存在前驱元素！\n");
		 getchar();getchar();
		 break;

	   case 9:
	       //求出后置节点
         printf("请输入数据元素：\n");
		 scanf("%d",&cur_e);

	     if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }
		 if(NextElem(L[i_num],cur_e,next_e)==OK){
		    printf("其后继元素为：%d\n",next_e);
         }
		 else if(NextElem(L[i_num],cur_e,pre_e)==FALSE){
		    printf("其不存在后继元素！\n");
         }
		 else{
            printf("顺序表中没有该元素！\n");
         }
		 getchar();getchar();
		 break;

	   case 10:
	       //插入元素
	     if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }
		 printf("请输入您要插入的数据元素：\n");
		 scanf("%d",&e);
		 printf("请输入您要插入的数据元素的位置：\n");
		 scanf("%d",&i);
		 if(ListInsert(L[i_num],i,e)==OK)
		 printf("插入数据元素成功！\n");
		 else
		 printf("插入数据元素失败！\n");
		 getchar();getchar();
		 break;

	   case 11:
	       //删除元素
	       if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }
		 printf("请输入您要删除的数据元素的位置：\n");
		 scanf("%d",&i);
		 if(ListDelete(L[i_num],i,e)==OK)
		 printf("删除数据元素成功！\n");
		 else
		 printf("删除数据元素失败！\n");
		 getchar();getchar();
		 break;

	   case 12:
	       //遍历线性表中的元素
            
	     if(L[i_num].elem==NULL)
         {
             printf("线性表不存在!\n");
             getchar();getchar();
             break;
         }
         if(L[i_num].length==0)
         {
            printf("线性表是空表！\n");
            getchar();getchar();
            break;
         }
        ListTraverse(L[i_num]);
		 getchar();getchar();
		 break;

       case 13:
           //保存文件
           if(L[i_num].elem == NULL)
         {
             printf("线性表不存在!无法保存！\n");
             getchar();getchar();
             break;
         }
         if(SaveList(L[i_num], filename)==OK){
            printf("文件保存成功\n文件名为%s\n",filename);
         }
		getchar();getchar();
         break;

       case 14:
        //加载文件，需要输入需要加载的名称
        if(L[i_num].elem!=NULL){
            printf("线性表已存在！无法加载！");
            getchar();getchar();
            break;
        }
         printf("请输入要加载的文件名:\n ");
		 scanf("%s", filename);
		 if(LoadList(L[i_num], filename)==OK)
            {
                printf("文件加载成功\n");
		    }else{
                printf("文件加载失败！");
            }
         break;

       case 15:
           //求连续子组的最大和
           if(L[i_num].elem==NULL){
                printf("线性表不存在！");
                getchar(); getchar();
                break;
           }
           printf("连续子组的最大和为%d" ,Maxsubarray(L[i_num]));
           getchar();getchar();
           break;

        case 16:
           //求和为k的连续子组的个数
           if(L[i_num].elem==NULL){
                printf("线性表不存在！");
                getchar(); getchar();
                break;
           }
           printf("请输入和的大小\n");
           scanf("%d" ,&k);
           printf("和为k的连续子组的个数为%d" ,subarraynum(L[i_num] ,k));
           getchar(); getchar();
            break;

       case 17:
           //线性表排序
           if(L[i_num].elem==NULL){
                printf("线性表不存在！");
                getchar(); getchar();
                break;
           }
           printf("请输入排序方式，0：从小到大，1：从大到小\n");
           scanf("%d" ,&order);
           sortlist(L[i_num],order);
           printf("排序完成！");
           getchar(); getchar();
           break;

       case 18:
           //选择在哪个表进行操作
           printf("请输入要在第几个表操作:\n ");
           printf("*只支持在%d个顺序表上操作*\n",MAX_NUM);
		   scanf("%d",&i_num);
           	 if((i_num<1)||(i_num>MAX_NUM))
		    {
		 	printf("请选择正确范围！默认对第一个线性表进行操作\n");
		 	i_num=1;
		    }
		   printf("正在对第%d个表进行操作\n",i_num);
           getchar(); getchar();
         break;

	   case 0:
        //退出菜单，退出整个程序
         break;
	}//end of switch
  }//end of while

  printf("欢迎下次再使用本系统!\n");
  system("pause");
  return 0;
}//end of main()

/******************function defination*************************/

/***************************************************************
*函数名称：IntiaList
*函数功能：构造一个空的线性表
*注释：初始条件是线性表L不存在已存在；操作结果是构造一个空的线性表。
*返回值类型：status类型
****************************************************************/
status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
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
*函数名称：DestoryList
*函数功能：销毁线性表
*注释：初始条件是线性表L已存在；操作结果是销毁线性表L
*返回值类型：status类型
****************************************************************/
status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
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
*函数名称：ClearList
*函数功能：重置顺序表
*注释：初始条件是线性表L已存在；操作结果是将L重置为空表。
*返回值类型：status类型
****************************************************************/
status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
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
*函数名称：ListEmpty
*函数功能：判断线性表是否为空
*注释：初始条件是线性表L已存在；操作结果是若L为空表则返回TRUE,否则返回FALSE。
*返回值类型：status类型
****************************************************************/
status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
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
*函数名称：ListLength
*函数功能：求线性表的表长
*注释：初始条件是线性表已存在；操作结果是返回L中数据元素的个数。
*返回值类型：status类型
****************************************************************/
status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(L.elem==NULL){
        return INFEASIBLE;
    }
        return L.length;
}


/***************************************************************
*函数名称：GetElem
*函数功能：得到某一个元素的值
*注释：初始条件是线性表已存在，1≤i≤ListLength(L)；操作结果是用e返回L中第i个数据元素的值
*返回值类型：status类型
****************************************************************/
status GetElem(SqList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
*函数名称：LocateElem
*函数功能：查找元素
*注释：初始条件是线性表已存在；操作结果是返回L中第1个与e满足关系compare（）
       关系的数据元素的位序，若这样的数据元素不存在，则返回值为0。
*返回值类型：status类型
****************************************************************/
int LocateElem(SqList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
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
*函数名称：PriorElem
*函数功能：求元素的前驱
*注释：初始条件是线性表L已存在；操作结果是若cur_e是L的数据元素，且不是第一个，
       则用pre_e返回它的前驱，否则操作失败，pre_e无定义。
*返回值类型：status类型
****************************************************************/
status PriorElem(SqList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
*函数名称：NextElem
*函数功能：求后继节点
*输入输出：初始条件是线性表L已存在；操作结果是若cur_e是L的数据元素，且不是最后一个，
           则用next_e返回它的后继，否则操作失败，next_e无定义。
*返回值类型：status类型
****************************************************************/
status NextElem(SqList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
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
*函数名称：ListInsert
*函数功能：插入元素
*注释：初始条件是线性表L已存在且非空，1≤i≤ListLength(L)+1；
*      操作结果是在L的第i个位置之前插入新的数据元素e
*返回值类型：status类型
****************************************************************/
status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
*函数名称：ListDelete
*函数功能：删除元素
*注释：初始条件是线性表L已存在且非空，1≤i≤ListLength(L)；
*      操作结果：删除L的第i个数据元素，用e返回其值。
*返回值类型：status类型
****************************************************************/
status ListDelete(SqList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
*函数名称：ListTraverse
*函数功能：遍历顺序表
*注释：输出顺序表的值
*返回值类型：status类型
****************************************************************/
status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
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
*函数名称：SaveList
*函数功能：保存线性表
*注释：将线性表保存，参考附录B
*返回值类型：status
****************************************************************/
status  SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
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
*函数名称：LoadList
*函数功能：加载文件
*注释：加载文件，以便功能的测试，文件名要正确
*返回值类型：status类型
****************************************************************/
status  LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
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
*函数名称：Maxsubarray
*函数功能：找出有最大和的连续子数组
*注释：遍历线性表中的元素，运用贪心算法，如果当前累加和为0，更新结果，
       如果当前累加和为负，将当前累加和重置为0，表示从该位置重新开始求和
*返回值类型：int类型,返回其最大和
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
*函数名称：subarraynum
*函数功能：找出和为k的连续子组的个数
*注释：暴力查找的方法
*返回值类型：int类型,返回和为k的连续子组的个数
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
*函数名称：sortlist
*函数功能：将L由小到大排序；
*注释：初始条件是线性表L已存在；操作结果是将L由小到大排序；采用的是冒泡排序的方法
*返回值类型：status
****************************************************************/
status sortlist(SqList L,int order)
{
    if(L.elem==NULL){
        return INFEASIBLE;
    }
    int i ,j; 
    ElemType t;
    //order=1从大到小排序，order=0从小到大排序
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


