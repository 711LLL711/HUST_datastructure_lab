#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "def.h"

/*function delclaration*/
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

// /**********global var(for creating the BiTree)**********/
// static int j,end=0,fail=0;
// static int check[MAX]={0};
// int nowkey;

int main(){
	char filename[30];//保存树的名称
	SqList L;//相当于用数组构建多树操作的框架
	BiTree p;
	int op=1;//op用来case,便于用户操作
	int e;//用于存查找结点的关键字
    int i, num=1 ,LR=0;
	FILE* fp;
	TElemType definition[MAX];//用于创建二叉树
	int index=0 ,createkey;//用于definition的索引
	TElemType newnode;//用于插入结点
    BiTree commonancestor;
	int e1,e2;
    int maxsum =INT_MIN;
	status opreateresult;

	//线性表初始化
	L.length = 0;
	L.listsize=LISTSIZE;
    for(i=0;i<20;i++)
    {
        L.tree[i].T = NULL;//相当于创建20个定义中类型的树的指针，同时指空，即20个树；
    }
     while(op){
	system("cls");
    printf("\n\n");
	printf("\t\t      Menu for Binary Tree On Binary Linked List \n");
	printf("\t**************************************************************************\n");
	printf("\t**\t\t1.  InitBiTree         \t  2.  CreateBiTree \t\t**\n");
	printf("\t**\t\t3.  DestroyBiTree      \t  4.  ClearBiTree  \t\t**\n");
	printf("\t**\t\t5.  BiTreeEmpty        \t  6.  BiTreeDepth\t\t**\n");
	printf("\t**\t\t7.  LocateNode         \t  8.  Assign \t\t\t**\n");
	printf("\t**\t\t9.  GetSibling        \t  10. InsertNode\t\t**\n");
	printf("\t**\t\t11. DeleteNode         \t  12. PreOrderTraverse\t\t**\n");
	printf("\t**\t\t13. InOrderTraverse    \t  14. PostOrderTraverse\t\t**\n");
	printf("\t**\t\t15. LevelOrderTraverse \t  16. MaxPathSum\t\t**\n");
	printf("\t**\t\t17. LowestCommonAncestor  18. InvertTree\t\t**\n");
	printf("\t**\t\t19. printTree                            \t\t**\n");
	printf("\t**\t\t20. SaveBiTree     \t  21. LoadBiTree\t\t**\n");
	printf("\t**\t\t22. Choose(多树操作)      0.  Exit\t\t\t**\n");
	printf("\t**\t\t若已有文件，可通过函数21进行加载\t\t\t**\n");
	printf("\t**   进行操作前，请先选择要操作的二叉树序号，默认在第一个树上进行操作\t**\n");
	printf("\t**************************************************************************\n");
	printf("\t\t\t请选择你的操作[0~22]:\n");
	scanf("%d",&op);
    switch(op)
	{

	   case 1:
	   //初始化二叉树
	    InitBiTree((L.tree[num-1].T));
	    printf("\t\t\t二叉树创建成功！\n");
		getchar();getchar();
		break;

	   case 2:
	   //创建二叉树
	   	if (L.tree[num-1].T == NULL){
	   		printf("\t\t\t二叉树不存在！\n");
	   		getchar();getchar();
	   		break;
		}else if(!BiTreeEmpty(L.tree[num-1].T)){
			printf("\t\t\t二叉树不为空，请在空二叉树开始创建！\n");
			getchar();getchar();
			break;
		}
		fflush(stdin);
	   	printf("请用前序方式输入序列构建二叉树，\n每个结点对应一个整型的关键字和一个字符串，\n当关键字为0时，表示空子树，为-1表示输入结束\n");
		scanf("%d" ,&createkey);
		while(createkey!=-1){
			definition[index].key=createkey;
			scanf("%s" ,definition[index].others);
			index++;
			scanf("%d" ,&createkey);
		}
		fflush(stdin);
		printf("输入结束\n");
		if(CreateBiTree(L.tree[num-1].T,definition)==OK){
			L.length++;
			printf("\t\t\t二叉树构造成功！\n\t\t\t请输入二叉树的名字\n");
			scanf("%s",&L.tree[num-1].name);
			printf("OK!你创建的二叉树名字是%s\n",L.tree[num-1].name);
		}else{
			ClearBiTree(L.tree[num-1].T);
			printf("输入了重复关键字，构造失败\n");
		}
		for(j = 0 ;j < MAX ;j++){
			check[j]=0;
		}
		end=0;fail=0;
		getchar();getchar();
		break;

		case 3:
	   //销毁二叉树
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t二叉树不存在！\n");
	   		getchar();getchar();
	   		break;
		}
	    DestroyBiTree((L.tree[num-1].T));
		L.length--;
	    printf("\t\t\t二叉树销毁成功!\n");
		getchar();getchar();
		break;

	   case 4:
	   //清空二叉树
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t二叉树不存在！\n");
	   		getchar();getchar();
	   		break;
		}
	    if(ClearBiTree(L.tree[num-1].T) == OK){
			printf("\t\t\t二叉树清空成功！\n");
		}else{
			printf("\t\t\t二叉树清空失败！\n");
		}
		getchar();getchar();
		break;

	   case 5:
	   //二叉树判空
	   	if (L.tree[num-1].T==NULL)
	   	{
	   		printf("\t\t\t二叉树不存在！\n");
	   		getchar();getchar();
	   		break;
		}
	    if(BiTreeEmpty(L.tree[num-1].T) == TRUE){
			printf("\t\t\t二叉树为空树！\n");
		}else{
			printf("\t\t\t二叉树不为空树！\n");
		}
		getchar();getchar();
		break;

	   case 6:
	   //求二叉树深度
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t二叉树不存在！\n");
	   		getchar();getchar();
	   		break;
		}
		if(BiTreeEmpty(L.tree[num-1].T) == TRUE){
			printf("\t\t\t二叉树为空树！\n");
		}else{
			printf("\t\t\t二叉树的深度为:%d\n", BiTreeDepth(L.tree[num-1].T));
		}
		getchar();getchar();
		break;

	   case 7:
	   //查找关键字为e的结点
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t二叉树不存在！\n");
	   		getchar();getchar();
	   		break;
		}
		printf("请输入要查找的关键字(注意是int类型)\n");
		scanf("%d" ,&e);
		p = LocateNode(L.tree[num-1].T,e);
	    if(p){
			printf("找到了！\n");
			printf("该结点关键字为%d,信息为%s" ,p->data.key,p->data.others);
		}else{
			printf("没找到o(╥﹏╥)o\n");
		}
		getchar();getchar();
		break;

	   case 8:
	   //结点赋值
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t二叉树不存在！\n");
	   		getchar();getchar();
	   		break;
		}
	    printf("\t\t\t请输入你要赋值的key:\n");
		scanf("%d", &e);
		printf("请输入你要修改后的关键字\n");
		scanf("%d" ,&newnode.key);
		printf("请输入你要修改后的信息\n");
		scanf("%s",newnode.others);
		opreateresult=Assign(L.tree[num-1].T,e,newnode);
		if(opreateresult==OK){
			printf("修改成功");
		}else if(opreateresult==ERROR){
			printf("修改后会存在关键字重复，修改失败\n");
		}else{
			printf("要赋值的结点不存在");
		}
		getchar();getchar();
		break;

	   case 9:
	   //查找节点的兄弟
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t二叉树不存在！\n");
	   		getchar();getchar();
	   		break;
		}
	    printf("\t\t\t请输入你要查找的key:\n");
		scanf("%d", &e);
		
		if(LocateNode(L.tree[num-1].T,e)==NULL){
			printf("该节点不存在\n");
			getchar();getchar();
			break;
		}
		p = GetSibling(L.tree[num-1].T,e);
		if(p==NULL){
			printf("该节点不存在兄弟节点\n");
		}else{
			printf("找到了，该节点的兄弟结点关键字为%d,信息为%s\n",p->data.key,p->data.others);
		}
		getchar();getchar();
		break;

	   case 10:
	   //插入结点
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t二叉树不存在！\n");
	   		getchar();getchar();
	   		break;
		}
		printf("请输入你要插入的结点的父结点的关键字\n");
		scanf("%d" ,&e);
		printf("请输入LR：0-->左边，1-->右边，-1-->在根节点插入\n");
		scanf("%d" ,&LR);
		if(LR!=0 &&LR!=1 &&LR!=-1){
			printf("LR输入错误！\n");
			getchar();getchar();
			break;
		}
		printf("请输入你要插入的结点的关键字,类型必须是int\n");
		scanf("%d" ,&newnode.key);
		printf("请输入你要插入的结点的信息\n");
		scanf("%s" ,newnode.others);
		opreateresult=InsertNode(L.tree[num-1].T,e,LR,newnode);
	  	if(opreateresult==INFEASIBLE){
			printf("你要插入的父节点不存在\n");
		}else if(opreateresult==ERROR){
			printf("你要插入的关键字有重复\n");
		}else{
			printf("插入成功\n");
		}
		getchar();getchar();
		break;

	   case 11:
        //删除结点
	   	if (L.tree[num-1].T == NULL){
	   		printf("\t\t\t二叉树不存在！\n");
	   		getchar();getchar();
	   		break;
		}
		printf("请输入你要删除的结点的关键字\n");
		scanf("%d" ,&e);
		if(DeleteNode(L.tree[num-1].T,e)==ERROR){
			printf("你要删除的结点不存在\n");
		}else{
			printf("删除成功\n");
		}
		getchar();getchar();
		break;

	   case 12:
        //先序遍历
		if(L.tree[num-1].T==NULL){
			printf("二叉树不存在\n");
			getchar();getchar();
			break;
		}
		PreOrderTraverse(L.tree[num-1].T,visit);
		getchar();getchar();
			break;

	   case 13:
        //中序遍历
		if(L.tree[num-1].T==NULL){
			printf("二叉树不存在\n");
			getchar();getchar();
			break;
		}
		InOrderTraverse(L.tree[num-1].T,visit);
		getchar();getchar();
			break;
	   case 14:
       //后序遍历
		if(L.tree[num-1].T==NULL){
			printf("二叉树不存在\n");
			getchar();getchar();
			break;
		}
		PostOrderTraverse(L.tree[num-1].T,visit);
		getchar();getchar();
			break;

	   case 15:
        //层序遍历
		if(L.tree[num-1].T==NULL){
			printf("二叉树不存在！\n");
			getchar();getchar();
			break;
		}
		LevelOrderTraverse(L.tree[num-1].T,visit);
		getchar();getchar();
			break;

	   case 16:
        //最大路径和，从根节点到叶子结点的最大路径和
		maxsum=INT_MIN;
		if(L.tree[num-1].T==NULL){
			printf("二叉树不存在！\n");
		}else{
			MaxPathSum(L.tree[num-1].T,maxsum);
			printf("最大路径和为%d\n",maxsum);
		}
		getchar();getchar();
			break;

	   case 17:
       //两个节点的最近公共祖先
		if(L.tree[num-1].T==NULL){
			printf("二叉树不存在！\n");
		}else{
			printf("请输入你要查找的两个结点的关键字\n");
			scanf("%d %d",&e1,&e2);
			commonancestor=LowestCommonAncestor(L.tree[num-1].T,e1,e2);
			if(commonancestor==NULL){
				printf("你要查找的两个结点不存在！\n");
			}else{
				printf("最近公共祖先关键字为%d,信息为%s\n",commonancestor->data.key,commonancestor->data.others);
			}
		}
		getchar();getchar();
			break;

	   case 18:
        //将二叉树所有节点的左右子树反转
		if(L.tree[num-1].T==NULL){
			printf("二叉树不存在！\n");
		}else{
			InvertTree(L.tree[num-1].T);
			printf("反转成功！\n");
		}
		getchar();getchar();
			break;

		case 19:
		//打印二叉树
		if(L.tree[num-1].T==NULL){
			printf("二叉树不存在！\n");
		}else if(BiTreeEmpty(L.tree[num-1].T)){
			printf("");
		}else{
			printTree(L.tree[num-1].T,0,0);
		}
		getchar();getchar();
			break;

			
	   case 20:
        //保存二叉树
		if(L.tree[num-1].T==NULL){
			printf("二叉树不存在！\n");
		}else{
			printf("请输入你要保存的文件名\n");
			scanf("%s" ,filename);
			SaveBiTree(L.tree[num-1].T,filename);
			printf("保存成功！已将二叉树以先序序列保存在文件%s中\n",filename);
		}
		getchar();getchar();
			break;

	   case 21:
       //加载二叉树
		printf("请输入你要加载的文件名\n");
		scanf("%s" ,filename);
		if((fp=fopen(filename,"r"))==NULL){
			printf("打开文件失败！\n");
		}else{
			LoadBiTree(L.tree[num-1].T,filename);
			printf("加载成功！已将文件%s中的二叉树加载到第%d棵二叉树中\n",filename,num);
		}
		getchar();getchar();
			break;

	   case 22:
	   //choose
	   	printf("\t\t\t在第几个树操作?只支持%d个树进行操作: \n",LISTSIZE);
		scanf("%d",&num);
		if(num<1||num>20){
			printf("\t\t\t请选择正确范围！已默认在第一个树操作\n");
			num=1;
		}else{
			printf("\t\t\t你选择了第%d个树\n",num);
		}
		getchar(); getchar();
		break;
	   case 0:
        break;
	}//end of switch
  }//end of while
    printf("\n");
	printf("\t\t\t欢迎下次再使用本系统！\n\n");
	getchar();
}//end of main()  

