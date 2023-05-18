#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int op=1, i, i_num=1, key;
    VertexType e;//����ͼ�еĽڵ�
    ALGraph G[graphnum+1];//ʮ��ͼ,0��ͼ����
    VertexType V[MAX_VERTEX_NUM];
    KeyType VR[MAX_ARC_NUM][2];//���ڴ���ͼ
    KeyType u;//���ڲ��Ҷ���
	int result ,v1 ,v2 ,result1 ,result2 ,dis;
	char s[20];

	int arr[MAX_VERTEX_NUM];//���ڸ��ӹ����б������С��k�Ķ���
	int count;//���ڸ��ӹ����б������С��k�Ķ���ĸ���

    for (i = 0; i<=10; i++)
	{
        G[i].vexnum=0;
		G[i].arcnum=0;
		 G[i].kind = DG;//�������ͼ�����࣬DG˵��δ��ʼ����UDG˵����ʼ����������ͼ
	}
    while(op){
	system("cls");	//��������
	printf("\n\n");
	printf("\t\t      Menu for Undirected Graph On Chain Structure \n");
	printf("\t******************************************************************************\n");
	printf("\t\t\t1.  CreateGraph               2.  DestroyGraph\n");
	printf("\t\t\t3.  LocateVex                 4.  PutVex\n");
	printf("\t\t\t5.  FirstAdjVex               6.  NextAdjVex\n");
	printf("\t\t\t7.  InsertVex                 8.  DeleteVex\n");
	printf("\t\t\t9.  InsertArc                 10. DeleteArc\n");
	printf("\t\t\t11. DFSTraverse               12. BFSTraverse\n");
	printf("\t\t\t13. SaveGraph                 14. LoadGraph\n");
	printf("\t\t\t15. VerticesSetLessThanK      16. ShortestPathLength\n");
	printf("\t\t\t17. ConnectedComponentsNums   18. choose\n");
    printf("\t\t\t0.Exit   \n");
	printf("\t****************************************************************************\n");
	printf("\t\t\t��ѡ����Ĳ���[0-18]: ");
	scanf("%d",&op);
    switch(op)
	{
	   case 1:
       //����ͼ
	   if(G[i_num].kind==UDG){
			printf("\t\t\t��ͼ�Ѿ���������!\n");
			getchar();getchar();
			break;
	   }
	    printf("\t\t\t���������ݣ�\n") ;
		i=0;
        do {
            scanf("%d%s",&V[i].key,V[i].others);
        } while(V[i++].key!=-1);
        i=0;
        do {
            scanf("%d%d",&VR[i][0],&VR[i][1]);
        } while(VR[i++][0]!=-1);

        if (CreateGraph(G[i_num],V,VR)==OK) {
			printf("\t\t\t%d��ͼ�����ɹ���\n",i_num);
           
        }else {
            printf("\t\t\t�������ݴ��޷�����\n");
        }
        getchar();getchar();
        break;

	   case 2:
       //����ͼ 
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	    if(DestroyGraph(G[i_num])==OK)
		printf("\t\t\t��������ͼ�ɹ�!\n");
        else{
			printf("\t\t\t��������ͼʧ��!\n");
		}
		
		getchar();getchar();
		break;

	   case 3:
       //���Ҷ���
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	    printf("\t\t\t��������Ҫ���ҽ���keyֵ��");
        scanf("%d",&u);
        i = LocateVex(G[i_num],u);
        if(i != -1) {
            printf("\t\t\t���ҳɹ����ý����ϢΪ��\n");
            visit(G[i_num].vertices[i].data);
        } else printf("\t\t\t����ʧ�ܣ�\n");
        getchar();
        getchar();
        break;

	   case 4:
       //���㸳ֵ
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	   	printf("               ��������Ҫ��ֵ�Ľ��keyֵ:");
        scanf("%d",&u);
        printf("               �����븳ֵ��Ľ��keyֵ:");
        scanf("%d",&e.key);
        printf("               �����븳ֵ��Ľ��othersֵ:");
        scanf("%s",e.others);
        if(PutVex(G[i_num],u,e)==OK) {
            printf("\t\t\t��ֵ�ɹ������ڸý�����ϢΪ��\n");
            visit(G[i_num].vertices[LocateVex(G[i_num],e.key)].data);
        }else printf("\t\t\t��ֵʧ�ܣ���ֵ�����ظ�\n");
        getchar(); getchar();
        break;

	   case 5:
       //��õ�һ�ڽӵ�
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	    printf("\t\t\t������Ҫ���ҵĶ����key��");
	    scanf("%d",&key);
		result=LocateVex(G[i_num],key);
		if(result==-1){
			printf("\t\t\t�ö��㲻����!\n");
			getchar();getchar();
			break;
		}
		result=FirstAdjVex(G[i_num],key);
		if(result==ERROR){
			printf("\t\t\t�ö���û���ڽӶ���!\n");
		}else{
			printf("\t\t\t�ö���ĵ�һ���ڽӶ���Ϊ:\n");
			visit(G[i_num].vertices[result].data);
		}
	    getchar();getchar();
		break;
	
	   case 6:
       //�����һ�ڽӵ�
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
        printf("\t\t\t������Ҫ���ҵĶ��� v ��key��");
	    scanf("%d",&key);
		printf("\t\t\t�����������ԵĶ��� w ��key��");
		scanf("%d",&i);
		result=NextAdjVex(G[i_num],key,i);
	    if(result==ERROR){
			printf("\t\t\t����ʧ��!\n");
		}else{
			printf("\t\t\t�ö���v�����w����һ���ڽӶ���Ϊ:\n");
			visit(G[i_num].vertices[result].data);
		}
		getchar();getchar();
		break;

	   case 7:
       //���붥��
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	   	if(G[i_num].vexnum >= MAX_VERTEX_NUM){
			printf("\t\t\t�������Ѵﵽ���ֵ!��֧�ֲ���\n");
			getchar();getchar();
			break;
		}
		printf("\t\t\t������Ҫ����Ķ����keyֵ:\n");
		scanf("%d",&e.key);
		printf("\t\t\t������Ҫ����Ķ����othersֵ:\n");
		scanf("%s",e.others);
		if(InsertVex(G[i_num],e)==ERROR){
			printf("\t\t\t�ؼ����ظ�����ʧ��!\n");
		}else{
			printf("\t\t\t����ɹ�!\n");
		}
		getchar();getchar();
		break;

	   case 8:
       //ɾ������
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
		printf("\t\t\t������Ҫɾ���Ķ����keyֵ:");
		scanf("%d",&key);
		result=LocateVex(G[i_num],key);
		if(result==-1){
			printf("\t\t\t�ö��㲻����!\n");
			getchar();getchar();
			break;
		}
		if(DeleteVex(G[i_num],key)==ERROR){
			printf("\t\t\tɾ�˾��ǿ�ͼ�ˣ�����ɾ>?<");
		}else{
			printf("\t\t\tɾ���ɹ�!\n");
		}
		getchar();getchar();
			break;

	   case 9:
       //���뻡
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	   	printf("\t\t\t������ߵ������ڵ�Ĺؼ���(�ո���Ϊ���,��a1 a2):");
		scanf("%d %d" ,&v1,&v2);
		result1=LocateVex(G[i_num],v1);
		result2=LocateVex(G[i_num],v2);
		if(result1==-1||result2==-1){
			printf("\t\t\t���㲻����!\n");
			getchar();getchar();
			break;
		}
		if(InsertArc(G[i_num],v1,v2)==ERROR){
			printf("\t\t\t���ʧ�� ,����֮���Ѿ��л�!\n");
		}else{
			printf("\t\t\t��ӳɹ�!\n");
		}
		getchar();getchar();
		break;

	   case 10:
       //ɾ����
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	   printf("\t\t\t������ߵ������ڵ�Ĺؼ���(�ո���Ϊ���,��a1 a2):");
		scanf("%d %d" ,&v1,&v2);
		result1=LocateVex(G[i_num],v1);
		result2=LocateVex(G[i_num],v2);
		if(result1==-1||result2==-1){
			printf("\t\t\t���㲻����!\n");
			getchar();getchar();
			break;
		}
		if(DeleteArc(G[i_num],v1,v2)==ERROR){
			printf("\t\t\tɾ��ʧ�� ,����֮��û�л�!\n");
		}else{
			printf("\t\t\tɾ���ɹ�!\n");
		}
		getchar();getchar();
		break;

	   case 11:
       //dfs
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	   	printf("\t\t\t������ͼ�����������������Ϊ��\n");
	   	DFSTraverse(G[i_num],visit);
	   	printf("\n");
		getchar();getchar();
		break;


	   case 12:
       //bfs
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	   	printf("\t\t\t������ͼ�Ĺ��������������Ϊ��\n");
	   	BFSTraverse(G[i_num],visit);
	   	printf("\n");
		getchar();getchar();
		break;

	   case 13:
       //����ͼ
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
		printf("\t\t\t�����뱣���ļ����ļ���(��a.txt):\n");
		scanf("%s",s);

	    if(SaveGraph(G[i_num] ,s)==OK){
			printf("\t\t\t����ɹ�!\n");
		}else{
			printf("\t\t\t����ʧ��!\n");
		}
		getchar();getchar();
		break;
	   	

	   case 14:
	   //��ȡͼ
	   if(G[i_num].kind==UDG){
		printf("\t\t\t��ͼ�Ѵ���!\n");
		getchar();getchar();
        break;
	   }
	   	printf("\t\t\t�������ȡ�ļ����ļ���(��a.txt):\n");
		scanf("%s",s);
        if(LoadGraph(G[i_num] ,s)==OK){
			printf("\t\t\t��ȡ�ɹ�!\n");
		}else{
			printf("\t\t\t��ȡʧ��!\n");
		}
		getchar();getchar();
		break;
	   
	   case 15:
       //����С��k�Ķ��㼯��
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	   printf("\t\t\t������Ҫ���ҵĶ����keyֵ:\n");
	   scanf("%d",&key);
		printf("\t\t\t�����ҵľ���С�ڶ��ٵĶ��㼯�ϣ�\n");
		scanf("%d",&dis);
		count=0;
		if(VerticesSetLessThanK(G[i_num],key,dis,arr,&count)==ERROR){
			printf("\t\t\tһ��Ҳû��(?_?|||)\n");
		}else{
			printf("\t\t\t����С��%d�Ķ��㼯��Ϊ:\n",dis);
			for(i=0;i<count;i++){
				visit(G[i_num].vertices[arr[i]].data);
			}
		}
		getchar();getchar();
		break;

	   case 16:
       //��������·���ͳ���
	   if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
	   printf("\t\t\t������Ҫ���ҵ����������keyֵ,�ո�ָ�:\n");
	   scanf("%d %d",&v1,&v2);
		result1=LocateVex(G[i_num],v1);
		result2=LocateVex(G[i_num],v2);
		if(result1==-1||result2==-1){
			printf("\t\t\t���㲻����!\n");
			getchar();getchar();
			break;
		}
		result=ShortestPathLength(G[i_num],v1,v2);
		if(result==ERROR){
			printf("\t\t\t��������֮��û��·��!\n");
		}else{
			printf("\t\t\t��������֮������·������Ϊ:%d\n",result);
		}
		getchar();getchar();
			break;

        case 17:
        //ͼ����ͨ��������
		if(G[i_num].kind==DG){
		printf("\t\t\t��ͼ��δ����!\n");
		getchar();getchar();
        break;
	   }
		printf("\t\t\t��ͨ��������Ϊ:%d\n",ConnectedComponentsNums(G[i_num]));
		getchar();getchar();
			break;

        case 18:
        //choose
        printf("\t\t������Ҫ�ڵڼ���ͼ����,ֻ֧����%d��ͼ���в���: " ,graphnum);
		scanf("%d",&i_num);
		if(i_num<1||i_num>20)
		{
		 	printf("\t\t\t��֧���ڸ�ͼ�Ͻ��в���,��Ĭ���ڵ�һ��ͼ!\n");
		 	i_num=1;
		}else{
			printf("\t\t\t���л�����%d��ͼ!\n",i_num);
		}
		getchar(); getchar();
		break;

	   case 0:
        break;
	}//end of switch
  }//end of while
    printf("\n");
	printf("\t\t\t��ӭ�´�ʹ�ñ�ϵͳ!\n\n");
}//end of main()