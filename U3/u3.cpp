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
	char filename[30];//������������
	SqList L;//�൱�������鹹�����������Ŀ��
	BiTree p;
	int op=1;//op����case,�����û�����
	int e;//���ڴ���ҽ��Ĺؼ���
    int i, num=1 ,LR=0;
	FILE* fp;
	TElemType definition[MAX];//���ڴ���������
	int index=0 ,createkey;//����definition������
	TElemType newnode;//���ڲ�����
    BiTree commonancestor;
	int e1,e2;
    int maxsum =INT_MIN;
	status opreateresult;

	//���Ա��ʼ��
	L.length = 0;
	L.listsize=LISTSIZE;
    for(i=0;i<20;i++)
    {
        L.tree[i].T = NULL;//�൱�ڴ���20�����������͵�����ָ�룬ͬʱָ�գ���20������
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
	printf("\t**\t\t22. Choose(��������)      0.  Exit\t\t\t**\n");
	printf("\t**\t\t�������ļ�����ͨ������21���м���\t\t\t**\n");
	printf("\t**   ���в���ǰ������ѡ��Ҫ�����Ķ�������ţ�Ĭ���ڵ�һ�����Ͻ��в���\t**\n");
	printf("\t**************************************************************************\n");
	printf("\t\t\t��ѡ����Ĳ���[0~22]:\n");
	scanf("%d",&op);
    switch(op)
	{

	   case 1:
	   //��ʼ��������
	    InitBiTree((L.tree[num-1].T));
	    printf("\t\t\t�����������ɹ���\n");
		getchar();getchar();
		break;

	   case 2:
	   //����������
	   	if (L.tree[num-1].T == NULL){
	   		printf("\t\t\t�����������ڣ�\n");
	   		getchar();getchar();
	   		break;
		}else if(!BiTreeEmpty(L.tree[num-1].T)){
			printf("\t\t\t��������Ϊ�գ����ڿն�������ʼ������\n");
			getchar();getchar();
			break;
		}
		fflush(stdin);
	   	printf("����ǰ��ʽ�������й�����������\nÿ������Ӧһ�����͵Ĺؼ��ֺ�һ���ַ�����\n���ؼ���Ϊ0ʱ����ʾ��������Ϊ-1��ʾ�������\n");
		scanf("%d" ,&createkey);
		while(createkey!=-1){
			definition[index].key=createkey;
			scanf("%s" ,definition[index].others);
			index++;
			scanf("%d" ,&createkey);
		}
		fflush(stdin);
		printf("�������\n");
		if(CreateBiTree(L.tree[num-1].T,definition)==OK){
			L.length++;
			printf("\t\t\t����������ɹ���\n\t\t\t�����������������\n");
			scanf("%s",&L.tree[num-1].name);
			printf("OK!�㴴���Ķ�����������%s\n",L.tree[num-1].name);
		}else{
			ClearBiTree(L.tree[num-1].T);
			printf("�������ظ��ؼ��֣�����ʧ��\n");
		}
		for(j = 0 ;j < MAX ;j++){
			check[j]=0;
		}
		end=0;fail=0;
		getchar();getchar();
		break;

		case 3:
	   //���ٶ�����
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t�����������ڣ�\n");
	   		getchar();getchar();
	   		break;
		}
	    DestroyBiTree((L.tree[num-1].T));
		L.length--;
	    printf("\t\t\t���������ٳɹ�!\n");
		getchar();getchar();
		break;

	   case 4:
	   //��ն�����
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t�����������ڣ�\n");
	   		getchar();getchar();
	   		break;
		}
	    if(ClearBiTree(L.tree[num-1].T) == OK){
			printf("\t\t\t��������ճɹ���\n");
		}else{
			printf("\t\t\t���������ʧ�ܣ�\n");
		}
		getchar();getchar();
		break;

	   case 5:
	   //�������п�
	   	if (L.tree[num-1].T==NULL)
	   	{
	   		printf("\t\t\t�����������ڣ�\n");
	   		getchar();getchar();
	   		break;
		}
	    if(BiTreeEmpty(L.tree[num-1].T) == TRUE){
			printf("\t\t\t������Ϊ������\n");
		}else{
			printf("\t\t\t��������Ϊ������\n");
		}
		getchar();getchar();
		break;

	   case 6:
	   //����������
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t�����������ڣ�\n");
	   		getchar();getchar();
	   		break;
		}
		if(BiTreeEmpty(L.tree[num-1].T) == TRUE){
			printf("\t\t\t������Ϊ������\n");
		}else{
			printf("\t\t\t�����������Ϊ:%d\n", BiTreeDepth(L.tree[num-1].T));
		}
		getchar();getchar();
		break;

	   case 7:
	   //���ҹؼ���Ϊe�Ľ��
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t�����������ڣ�\n");
	   		getchar();getchar();
	   		break;
		}
		printf("������Ҫ���ҵĹؼ���(ע����int����)\n");
		scanf("%d" ,&e);
		p = LocateNode(L.tree[num-1].T,e);
	    if(p){
			printf("�ҵ��ˣ�\n");
			printf("�ý��ؼ���Ϊ%d,��ϢΪ%s" ,p->data.key,p->data.others);
		}else{
			printf("û�ҵ�o(�i�n�i)o\n");
		}
		getchar();getchar();
		break;

	   case 8:
	   //��㸳ֵ
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t�����������ڣ�\n");
	   		getchar();getchar();
	   		break;
		}
	    printf("\t\t\t��������Ҫ��ֵ��key:\n");
		scanf("%d", &e);
		printf("��������Ҫ�޸ĺ�Ĺؼ���\n");
		scanf("%d" ,&newnode.key);
		printf("��������Ҫ�޸ĺ����Ϣ\n");
		scanf("%s",newnode.others);
		opreateresult=Assign(L.tree[num-1].T,e,newnode);
		if(opreateresult==OK){
			printf("�޸ĳɹ�");
		}else if(opreateresult==ERROR){
			printf("�޸ĺ����ڹؼ����ظ����޸�ʧ��\n");
		}else{
			printf("Ҫ��ֵ�Ľ�㲻����");
		}
		getchar();getchar();
		break;

	   case 9:
	   //���ҽڵ���ֵ�
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t�����������ڣ�\n");
	   		getchar();getchar();
	   		break;
		}
	    printf("\t\t\t��������Ҫ���ҵ�key:\n");
		scanf("%d", &e);
		
		if(LocateNode(L.tree[num-1].T,e)==NULL){
			printf("�ýڵ㲻����\n");
			getchar();getchar();
			break;
		}
		p = GetSibling(L.tree[num-1].T,e);
		if(p==NULL){
			printf("�ýڵ㲻�����ֵܽڵ�\n");
		}else{
			printf("�ҵ��ˣ��ýڵ���ֵܽ��ؼ���Ϊ%d,��ϢΪ%s\n",p->data.key,p->data.others);
		}
		getchar();getchar();
		break;

	   case 10:
	   //������
	   	if (L.tree[num-1].T == NULL)
	   	{
	   		printf("\t\t\t�����������ڣ�\n");
	   		getchar();getchar();
	   		break;
		}
		printf("��������Ҫ����Ľ��ĸ����Ĺؼ���\n");
		scanf("%d" ,&e);
		printf("������LR��0-->��ߣ�1-->�ұߣ�-1-->�ڸ��ڵ����\n");
		scanf("%d" ,&LR);
		if(LR!=0 &&LR!=1 &&LR!=-1){
			printf("LR�������\n");
			getchar();getchar();
			break;
		}
		printf("��������Ҫ����Ľ��Ĺؼ���,���ͱ�����int\n");
		scanf("%d" ,&newnode.key);
		printf("��������Ҫ����Ľ�����Ϣ\n");
		scanf("%s" ,newnode.others);
		opreateresult=InsertNode(L.tree[num-1].T,e,LR,newnode);
	  	if(opreateresult==INFEASIBLE){
			printf("��Ҫ����ĸ��ڵ㲻����\n");
		}else if(opreateresult==ERROR){
			printf("��Ҫ����Ĺؼ������ظ�\n");
		}else{
			printf("����ɹ�\n");
		}
		getchar();getchar();
		break;

	   case 11:
        //ɾ�����
	   	if (L.tree[num-1].T == NULL){
	   		printf("\t\t\t�����������ڣ�\n");
	   		getchar();getchar();
	   		break;
		}
		printf("��������Ҫɾ���Ľ��Ĺؼ���\n");
		scanf("%d" ,&e);
		if(DeleteNode(L.tree[num-1].T,e)==ERROR){
			printf("��Ҫɾ���Ľ�㲻����\n");
		}else{
			printf("ɾ���ɹ�\n");
		}
		getchar();getchar();
		break;

	   case 12:
        //�������
		if(L.tree[num-1].T==NULL){
			printf("������������\n");
			getchar();getchar();
			break;
		}
		PreOrderTraverse(L.tree[num-1].T,visit);
		getchar();getchar();
			break;

	   case 13:
        //�������
		if(L.tree[num-1].T==NULL){
			printf("������������\n");
			getchar();getchar();
			break;
		}
		InOrderTraverse(L.tree[num-1].T,visit);
		getchar();getchar();
			break;
	   case 14:
       //�������
		if(L.tree[num-1].T==NULL){
			printf("������������\n");
			getchar();getchar();
			break;
		}
		PostOrderTraverse(L.tree[num-1].T,visit);
		getchar();getchar();
			break;

	   case 15:
        //�������
		if(L.tree[num-1].T==NULL){
			printf("�����������ڣ�\n");
			getchar();getchar();
			break;
		}
		LevelOrderTraverse(L.tree[num-1].T,visit);
		getchar();getchar();
			break;

	   case 16:
        //���·���ͣ��Ӹ��ڵ㵽Ҷ�ӽ������·����
		maxsum=INT_MIN;
		if(L.tree[num-1].T==NULL){
			printf("�����������ڣ�\n");
		}else{
			MaxPathSum(L.tree[num-1].T,maxsum);
			printf("���·����Ϊ%d\n",maxsum);
		}
		getchar();getchar();
			break;

	   case 17:
       //�����ڵ�������������
		if(L.tree[num-1].T==NULL){
			printf("�����������ڣ�\n");
		}else{
			printf("��������Ҫ���ҵ��������Ĺؼ���\n");
			scanf("%d %d",&e1,&e2);
			commonancestor=LowestCommonAncestor(L.tree[num-1].T,e1,e2);
			if(commonancestor==NULL){
				printf("��Ҫ���ҵ�������㲻���ڣ�\n");
			}else{
				printf("����������ȹؼ���Ϊ%d,��ϢΪ%s\n",commonancestor->data.key,commonancestor->data.others);
			}
		}
		getchar();getchar();
			break;

	   case 18:
        //�����������нڵ������������ת
		if(L.tree[num-1].T==NULL){
			printf("�����������ڣ�\n");
		}else{
			InvertTree(L.tree[num-1].T);
			printf("��ת�ɹ���\n");
		}
		getchar();getchar();
			break;

		case 19:
		//��ӡ������
		if(L.tree[num-1].T==NULL){
			printf("�����������ڣ�\n");
		}else if(BiTreeEmpty(L.tree[num-1].T)){
			printf("");
		}else{
			printTree(L.tree[num-1].T,0,0);
		}
		getchar();getchar();
			break;

			
	   case 20:
        //���������
		if(L.tree[num-1].T==NULL){
			printf("�����������ڣ�\n");
		}else{
			printf("��������Ҫ������ļ���\n");
			scanf("%s" ,filename);
			SaveBiTree(L.tree[num-1].T,filename);
			printf("����ɹ����ѽ����������������б������ļ�%s��\n",filename);
		}
		getchar();getchar();
			break;

	   case 21:
       //���ض�����
		printf("��������Ҫ���ص��ļ���\n");
		scanf("%s" ,filename);
		if((fp=fopen(filename,"r"))==NULL){
			printf("���ļ�ʧ�ܣ�\n");
		}else{
			LoadBiTree(L.tree[num-1].T,filename);
			printf("���سɹ����ѽ��ļ�%s�еĶ��������ص���%d�ö�������\n",filename,num);
		}
		getchar();getchar();
			break;

	   case 22:
	   //choose
	   	printf("\t\t\t�ڵڼ���������?ֻ֧��%d�������в���: \n",LISTSIZE);
		scanf("%d",&num);
		if(num<1||num>20){
			printf("\t\t\t��ѡ����ȷ��Χ����Ĭ���ڵ�һ��������\n");
			num=1;
		}else{
			printf("\t\t\t��ѡ���˵�%d����\n",num);
		}
		getchar(); getchar();
		break;
	   case 0:
        break;
	}//end of switch
  }//end of while
    printf("\n");
	printf("\t\t\t��ӭ�´���ʹ�ñ�ϵͳ��\n\n");
	getchar();
}//end of main()  

