#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "Graph.h"
#include"Tourism.h"
#define MAX_VERTEX_NUM  20

//生成图
int CreatGraph(Graph &graph){
	Vex vex;
	Edge edge;
	int i,k;
	int ch;
	char buf[1024];
	int n=0,m;
	FILE *fp1,*fp2;
	
	Init(graph);

	//生成顶点
	fp1=fopen("Vex.txt","r");
	if(fp1==NULL){
	  printf("打开失败！\n");
	  return 0;
	}
	
	if(fscanf(fp1,"%d",&ch)!=-1)
	n=ch;             //顶点个数
	else {
	printf("文件读取失败\n");
	 return 0;
	}
	//初始化Vex[n]
	printf("顶点数目：%d\n",n);
    printf("-----顶点----\n");
	i=0;
	while(fscanf(fp1,"%d\n%s\n%s\n",&vex.num,&vex.name,&vex.desc)!=-1)
	{
		if(!InsertVex(vex,graph)){
		  printf("新增节点失败！\n");
		  return 0;
		}
	  printf("%d-%s\n",vex.num,vex.name);
	  i++;
	}
	fclose(fp1);

	//生成边 
	i=0;
	fp2=fopen("Edge.txt","rb");
	if(fp2==NULL){
	  printf("打开失败！\n");
	  return 0;
	}
	 printf("-----边----\n");
	while(fscanf(fp2,"%d\t%d\t%d\n",&edge.vex1,&edge.vex2,&edge.weight)!=-1)
	{	 
		if(!InsertEdge(edge,graph)){
		  printf("新增节点失败！\n");
		  return 0;
		}
		
	    printf("<v%d,v%d> %d\n",edge.vex1,edge.vex2,edge.weight);
	}
    fclose(fp2);
    printf("\n");	 
	return 1;
}
int GetSpotInfo(Graph &graph){
	//printf("graph.m_nVexNum：%d\n",GetVexNum(graph));
	for(int i=0;i<GetVexNum(graph);i++){
		printf("%d-%s\n",graph.m_aVex[i].num,graph.m_aVex[i].name);
	}

	int n=0;
	printf("请输入查询景点的编号：");
	scanf("%d",&n);

	Vex find;
    find=GetVex(n,graph);
	printf("%s\n%s\n",find.name,find.desc);

	//周边景区
	Edge fedge[20];
	int k;   //边的条数
	printf("----周边景区----\n");
	k=FindEdge(n,fedge,graph);

	return 1;
}
int TravelPath(Graph &graph)
{
	printf("======旅游景点导航======\n");
	//获得景点数
	int nVexNum=GetVexNum(graph);
	//列出所有景点编号的名称
	for(int i=0;i<nVexNum;i++)
	{
		Vex svex=GetVex(i,graph);
		printf("%d",svex.num);
		printf("-");
		printf("%s\n",svex.name);
	}

	//输入景点编号
	int nVex;
	printf("请输入起始点编号：");
	scanf("%d",&nVex);
	if(nVex<0||nVex>=20)
	{
		printf("输入错误！\n");
		return 0;
	}
	PathList pList=(PathList)malloc(sizeof(Path));
	PathList pHead=pList;
	DFSTraverse(nVex,pList,graph);
	printf("导游路线为：\n");
	int i=1;
	pList=pHead;
	while(pList->next)
	{
		Vex svex=GetVex(pList->vex[0],graph);
		printf("路线%d:",i);
		i++;
		printf("%s",svex.name);
		for(int j=1;j<nVexNum;j++)
		{
			svex=GetVex(pList->vex[j],graph);
			printf("->%s",svex.name);
		}
		printf("\n");

		Path *temp=pList;
		pList=pList->next;
		free(temp);
	}

	free(pList);
	pList=NULL;
	pHead=NULL;
	return 1;
}
int FindShortPath(Graph &graph){
	for(int i=0;i<GetVexNum(graph);i++){
		printf("%d-%s\n",graph.m_aVex[i].num,graph.m_aVex[i].name);
	}

	int start=0,end=0;
	int *path=(int *)malloc(sizeof(int)*graph.m_nVexNum);      //最短路径
	int *distance=(int *)malloc(sizeof(int)*graph.m_nVexNum);  //最短距离
	int *s=(int *)malloc(sizeof(int)*graph.m_nVexNum);         //标志
	int MaxWeight=100000;
	int u=0;
	int minDis;

	printf("请输入起点的编号：");
	scanf("%d",&start);
	printf("请输入终点的编号：");
	scanf("%d",&end);

	//初始化
	for(int i=0;i<graph.m_nVexNum;i++){
		distance[i]=graph.m_aAdjMatrix[start][i];
	
		s[i]=0;
		if(i!=start&&distance[i]<MaxWeight){
		   path[i]=start;
		}
		else{
		   path[i]=-1;
		}
	}
	s[start]=1;         //标记顶点start已从集合T加入到集合s当中
       
	printf("最短路线为：");
	printf("%s",graph.m_aVex[start].name);
	
    for(int i=1;i<graph.m_nVexNum;i++){
	   minDis=MaxWeight;
	   for(int j=0;j<graph.m_nVexNum;j++){
		   if((s[j]==0)&&(distance[j]<minDis)&&(distance[j]>0)){
			   u=j;
			   minDis=distance[j];
		   }
	   }
	  //  printf("u：%d",u);
		  //当前已不存在路径时算法结束
	   if(minDis==MaxWeight){
		   printf("为非连通图！\n");
	        return 0;
	   }		
	   s[u]=1;              //T->S
		   //printf("u%d\n",u);
		   //修改从start到其他顶点的最短路径
		   for(int j=0;j<graph.m_nVexNum;j++){
			   if((s[j]==0)&&(graph.m_aAdjMatrix[u][j]+distance[u]<distance[j])&&
				   (graph.m_aAdjMatrix[u][j]<MaxWeight)&&graph.m_aAdjMatrix[u][j]>0||((distance[j]==0)&&graph.m_aAdjMatrix[u][j]>0)){
			        distance[j]=graph.m_aAdjMatrix[u][j]+distance[u];
			        path[j]=u;
			   }
		   }
	}
	int t=end,n=0;
    char ch[20][10];
	while(t!=start){
		    //printf("->%s",graph.m_aVex[path[t]].name );	
			t=graph.m_aVex[path[t]].num;	
			strcpy(ch[n],graph.m_aVex[t].name); 
			//注意此处的t将graph.m_aVex[path[t]]的num取走，所以不可以直接用graph.m_aVex[path[t]]了
			n++;
		   }
	for(int j=n-2;j>=0;j--){
	       printf("->%s",ch[j]);	
	}
	printf("->%s",graph.m_aVex[end].name );	
	printf("\n最短距离为：%d\n\n",distance[end]);
	return 1;
}
int DesignPath(Graph &graph){
	 Edge aPath[MAX_VERTEX_NUM];    //定义边结构体数组用来保存铺设的线路
	 Prim(aPath,graph);

	 int nVexNum=GetVexNum(graph);
	 if(nVexNum==0)
	 {
		 printf("请先创建图!\n");	 
		 return 0;
	 }
	 int nAllLength=0;
	 printf("在以下两个顶点之间铺设电路\n");
	 
	 int i;
	 for(int i=0;i<nVexNum-1;i++)
	 { 
		 Vex sVex1=graph.m_aVex[aPath[i].vex1];  
		 Vex sVex2=graph.m_aVex[aPath[i].vex2];  
		 printf("%s%s\t%dm\n",sVex1.name,sVex2.name,aPath[i].weight);	 
		 nAllLength+=aPath[i].weight;
	 }
	 printf("铺设线路总长度为:%d\n",nAllLength);	
	 
	 return 1;
}