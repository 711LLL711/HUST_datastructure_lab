#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int op=1, i, i_num=1, key;
    VertexType e;//无向图中的节点
    ALGraph G[graphnum+1];//十个图,0号图不用
    VertexType V[MAX_VERTEX_NUM];
    KeyType VR[MAX_ARC_NUM][2];//用于创建图
    KeyType u;//用于查找顶点
	int result ,v1 ,v2 ,result1 ,result2 ,dis;
	char s[20];

	int arr[MAX_VERTEX_NUM];//用于附加功能中保存距离小于k的顶点
	int count;//用于附加功能中保存距离小于k的顶点的个数

    for (i = 0; i<=10; i++)
	{
        G[i].vexnum=0;
		G[i].arcnum=0;
		 G[i].kind = DG;//用来标记图的种类，DG说明未初始化，UDG说明初始化成了无向图
	}
    while(op){
	system("cls");	//用于清屏
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
	printf("\t\t\t请选择你的操作[0-18]: ");
	scanf("%d",&op);
    switch(op)
	{
	   case 1:
       //创建图
	   if(G[i_num].kind==UDG){
			printf("\t\t\t该图已经创建过了!\n");
			getchar();getchar();
			break;
	   }
	    printf("\t\t\t请输入数据：\n") ;
		i=0;
        do {
            scanf("%d%s",&V[i].key,V[i].others);
        } while(V[i++].key!=-1);
        i=0;
        do {
            scanf("%d%d",&VR[i][0],&VR[i][1]);
        } while(VR[i++][0]!=-1);

        if (CreateGraph(G[i_num],V,VR)==OK) {
			printf("\t\t\t%d号图表创建成功！\n",i_num);
           
        }else {
            printf("\t\t\t输入数据错，无法创建\n");
        }
        getchar();getchar();
        break;

	   case 2:
       //销毁图 
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	    if(DestroyGraph(G[i_num])==OK)
		printf("\t\t\t销毁无向图成功!\n");
        else{
			printf("\t\t\t销毁无向图失败!\n");
		}
		
		getchar();getchar();
		break;

	   case 3:
       //查找顶点
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	    printf("\t\t\t请输入需要查找结点的key值：");
        scanf("%d",&u);
        i = LocateVex(G[i_num],u);
        if(i != -1) {
            printf("\t\t\t查找成功！该结点信息为：\n");
            visit(G[i_num].vertices[i].data);
        } else printf("\t\t\t查找失败！\n");
        getchar();
        getchar();
        break;

	   case 4:
       //顶点赋值
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	   	printf("               请输入需要赋值的结点key值:");
        scanf("%d",&u);
        printf("               请输入赋值后的结点key值:");
        scanf("%d",&e.key);
        printf("               请输入赋值后的结点others值:");
        scanf("%s",e.others);
        if(PutVex(G[i_num],u,e)==OK) {
            printf("\t\t\t赋值成功！现在该结点的信息为：\n");
            visit(G[i_num].vertices[LocateVex(G[i_num],e.key)].data);
        }else printf("\t\t\t赋值失败！赋值后有重复\n");
        getchar(); getchar();
        break;

	   case 5:
       //获得第一邻接点
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	    printf("\t\t\t请输入要查找的顶点的key：");
	    scanf("%d",&key);
		result=LocateVex(G[i_num],key);
		if(result==-1){
			printf("\t\t\t该顶点不存在!\n");
			getchar();getchar();
			break;
		}
		result=FirstAdjVex(G[i_num],key);
		if(result==ERROR){
			printf("\t\t\t该顶点没有邻接顶点!\n");
		}else{
			printf("\t\t\t该顶点的第一个邻接顶点为:\n");
			visit(G[i_num].vertices[result].data);
		}
	    getchar();getchar();
		break;
	
	   case 6:
       //获得下一邻接点
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
        printf("\t\t\t请输入要查找的顶点 v 的key：");
	    scanf("%d",&key);
		printf("\t\t\t请输入和其相对的顶点 w 的key：");
		scanf("%d",&i);
		result=NextAdjVex(G[i_num],key,i);
	    if(result==ERROR){
			printf("\t\t\t查找失败!\n");
		}else{
			printf("\t\t\t该顶点v相对于w的下一个邻接顶点为:\n");
			visit(G[i_num].vertices[result].data);
		}
		getchar();getchar();
		break;

	   case 7:
       //插入顶点
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	   	if(G[i_num].vexnum >= MAX_VERTEX_NUM){
			printf("\t\t\t顶点数已达到最大值!不支持插入\n");
			getchar();getchar();
			break;
		}
		printf("\t\t\t请输入要插入的顶点的key值:\n");
		scanf("%d",&e.key);
		printf("\t\t\t请输入要插入的顶点的others值:\n");
		scanf("%s",e.others);
		if(InsertVex(G[i_num],e)==ERROR){
			printf("\t\t\t关键字重复插入失败!\n");
		}else{
			printf("\t\t\t插入成功!\n");
		}
		getchar();getchar();
		break;

	   case 8:
       //删除顶点
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
		printf("\t\t\t请输入要删除的顶点的key值:");
		scanf("%d",&key);
		result=LocateVex(G[i_num],key);
		if(result==-1){
			printf("\t\t\t该顶点不存在!\n");
			getchar();getchar();
			break;
		}
		if(DeleteVex(G[i_num],key)==ERROR){
			printf("\t\t\t删了就是空图了，不许删>?<");
		}else{
			printf("\t\t\t删除成功!\n");
		}
		getchar();getchar();
			break;

	   case 9:
       //插入弧
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	   	printf("\t\t\t请输入边的两个节点的关键字(空格作为间隔,如a1 a2):");
		scanf("%d %d" ,&v1,&v2);
		result1=LocateVex(G[i_num],v1);
		result2=LocateVex(G[i_num],v2);
		if(result1==-1||result2==-1){
			printf("\t\t\t顶点不存在!\n");
			getchar();getchar();
			break;
		}
		if(InsertArc(G[i_num],v1,v2)==ERROR){
			printf("\t\t\t添加失败 ,它们之间已经有弧!\n");
		}else{
			printf("\t\t\t添加成功!\n");
		}
		getchar();getchar();
		break;

	   case 10:
       //删除弧
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	   printf("\t\t\t请输入边的两个节点的关键字(空格作为间隔,如a1 a2):");
		scanf("%d %d" ,&v1,&v2);
		result1=LocateVex(G[i_num],v1);
		result2=LocateVex(G[i_num],v2);
		if(result1==-1||result2==-1){
			printf("\t\t\t顶点不存在!\n");
			getchar();getchar();
			break;
		}
		if(DeleteArc(G[i_num],v1,v2)==ERROR){
			printf("\t\t\t删除失败 ,它们之间没有弧!\n");
		}else{
			printf("\t\t\t删除成功!\n");
		}
		getchar();getchar();
		break;

	   case 11:
       //dfs
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	   	printf("\t\t\t该无向图的深度优先搜索遍历为：\n");
	   	DFSTraverse(G[i_num],visit);
	   	printf("\n");
		getchar();getchar();
		break;


	   case 12:
       //bfs
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	   	printf("\t\t\t该无向图的广度优先搜索遍历为：\n");
	   	BFSTraverse(G[i_num],visit);
	   	printf("\n");
		getchar();getchar();
		break;

	   case 13:
       //保存图
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
		printf("\t\t\t请输入保存文件的文件名(如a.txt):\n");
		scanf("%s",s);

	    if(SaveGraph(G[i_num] ,s)==OK){
			printf("\t\t\t保存成功!\n");
		}else{
			printf("\t\t\t保存失败!\n");
		}
		getchar();getchar();
		break;
	   	

	   case 14:
	   //读取图
	   if(G[i_num].kind==UDG){
		printf("\t\t\t该图已存在!\n");
		getchar();getchar();
        break;
	   }
	   	printf("\t\t\t请输入读取文件的文件名(如a.txt):\n");
		scanf("%s",s);
        if(LoadGraph(G[i_num] ,s)==OK){
			printf("\t\t\t读取成功!\n");
		}else{
			printf("\t\t\t读取失败!\n");
		}
		getchar();getchar();
		break;
	   
	   case 15:
       //距离小于k的顶点集合
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	   printf("\t\t\t请输入要查找的顶点的key值:\n");
	   scanf("%d",&key);
		printf("\t\t\t你想找的距离小于多少的顶点集合？\n");
		scanf("%d",&dis);
		count=0;
		if(VerticesSetLessThanK(G[i_num],key,dis,arr,&count)==ERROR){
			printf("\t\t\t一个也没有(?_?|||)\n");
		}else{
			printf("\t\t\t距离小于%d的顶点集合为:\n",dis);
			for(i=0;i<count;i++){
				visit(G[i_num].vertices[arr[i]].data);
			}
		}
		getchar();getchar();
		break;

	   case 16:
       //顶点间最短路径和长度
	   if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
	   printf("\t\t\t请输入要查找的两个顶点的key值,空格分隔:\n");
	   scanf("%d %d",&v1,&v2);
		result1=LocateVex(G[i_num],v1);
		result2=LocateVex(G[i_num],v2);
		if(result1==-1||result2==-1){
			printf("\t\t\t顶点不存在!\n");
			getchar();getchar();
			break;
		}
		result=ShortestPathLength(G[i_num],v1,v2);
		if(result==ERROR){
			printf("\t\t\t两个顶点之间没有路径!\n");
		}else{
			printf("\t\t\t两个顶点之间的最短路径长度为:%d\n",result);
		}
		getchar();getchar();
			break;

        case 17:
        //图的连通分量个数
		if(G[i_num].kind==DG){
		printf("\t\t\t该图还未创建!\n");
		getchar();getchar();
        break;
	   }
		printf("\t\t\t连通分量个数为:%d\n",ConnectedComponentsNums(G[i_num]));
		getchar();getchar();
			break;

        case 18:
        //choose
        printf("\t\t请输入要在第几个图操作,只支持在%d个图进行操作: " ,graphnum);
		scanf("%d",&i_num);
		if(i_num<1||i_num>20)
		{
		 	printf("\t\t\t不支持在该图上进行操作,已默认在第一个图!\n");
		 	i_num=1;
		}else{
			printf("\t\t\t已切换到第%d个图!\n",i_num);
		}
		getchar(); getchar();
		break;

	   case 0:
        break;
	}//end of switch
  }//end of while
    printf("\n");
	printf("\t\t\t欢迎下次使用本系统!\n\n");
}//end of main()