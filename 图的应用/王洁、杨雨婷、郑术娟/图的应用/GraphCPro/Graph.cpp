#include <stdio.h>
#include "Graph.h"
#include <stdlib.h>
#define MAX_VERTEX_NUM  20
void Init(Graph &graph){ //图的初始化
	int i=0,j=0;
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
		graph.m_aAdjMatrix[i][j]=0;
		}
	}
	graph.m_nVexNum=0;
}
bool InsertVex(Vex vex,Graph &graph){
	if(graph.m_nVexNum==MAX_VERTEX_NUM){
	   printf("景点已满！\n");
	   return false;
	}
	 
	graph.m_aVex[graph.m_nVexNum]=vex;	 
	graph.m_nVexNum++;
	return true;
}
bool InsertEdge(Edge edge,Graph &graph){
	if(edge.vex1<0||edge.vex2<0||edge.vex1>=graph.m_nVexNum||edge.vex2>=graph.m_nVexNum){
		printf("graph.m_nVexNum:%d\n",graph.m_nVexNum);
	    printf("下标越界！\n");
		return false;
	}
	graph.m_aAdjMatrix[edge.vex1][edge.vex2]=edge.weight;
	graph.m_aAdjMatrix[edge.vex2][edge.vex1]=edge.weight;
	return true;
}
Vex GetVex(int v,Graph &graph){
	if(v>=graph.m_nVexNum){
	 printf("没有此景点\n");	  
	}
	return graph.m_aVex[v];
}
int FindEdge(int v,Edge aEdge[],Graph &graph){
	int k=0;
	for(int i=0;i<graph.m_nVexNum;i++){
		//得到边的信息
		if(graph.m_aAdjMatrix[v][i]!=0){
			printf("%s->%s\t%d\n",graph.m_aVex[v].name,graph.m_aVex[i].name,graph.m_aAdjMatrix[v][i]);
		 k++;
		}
	   
	}
	return k;//返回边的条数
}
int GetVexNum(Graph graph){
	
	return graph.m_nVexNum;
}
//使用深度优先搜索算法遍历图
void DFS(int v,bool aVisited[],int &nIndex,PathList &pList,Graph &graph)
{
	aVisited[v]=true;//改为已访问
	pList->vex[nIndex++]=v;//访问顶点nVex

	int nVexNum=0;
	for(int i=0;i<graph.m_nVexNum;i++)
	{
		if(aVisited[i])
		{
			nVexNum++;
		}
	}
	if(nVexNum==graph.m_nVexNum)
	{
		pList->next=(PathList)malloc(sizeof(Path));
		for(int i=0;i<graph.m_nVexNum;i++)
		{
			pList->next->vex[i]=pList->vex[i];
		}
		pList=pList->next;
		pList->next=NULL;
	}
	else
	{
		for(int i=0;i<graph.m_nVexNum;i++)
		{
			if((!aVisited[i])&&(graph.m_aAdjMatrix[v][i]>0))
			{
				DFS(i,aVisited,nIndex,pList,graph);
				aVisited[i]=false;
				nIndex--;
			}
		}
	}

}

//调用DFS（）函数，得到深度优先搜索遍历的结果
void DFSTraverse(int nVex,PathList &pList,Graph &graph)
{
	int nIndex=0;
	bool aVisited[20]={false};
	DFS(nVex,aVisited,nIndex,pList,graph);
}
//Prim算法
void Prim(Edge aPath[],Graph &graph)
{
	//判断某顶点是否在最小生成树的集合里
	bool aVisited[MAX_VERTEX_NUM];
	for(int i=0;i<MAX_VERTEX_NUM;i++)
	{
		aVisited[i]=false;
	}
	aVisited[0]=true;   //0顶点加入集合中

	int min ;
	int nVex1,nVex2;
	for(int k=0;k<graph.m_nVexNum;k++)
	{
		min = 0x7FFFFFFF;
		for(int i=0;i<graph.m_nVexNum;i++)
		{
			if(aVisited[i]) //从集合中取一个点
			{
				for(int j=0;j<graph.m_nVexNum;j++)
				{
					if(!aVisited[j])     //从不在集合中的顶点中取出一个点
					{
						if((graph.m_aAdjMatrix[i][j]<min)&&(graph.m_aAdjMatrix[i][j]!=0))
						{
							nVex1=i;
							nVex2=j; 
							min=graph.m_aAdjMatrix[i][j];   //找出最短的边
						}
					}
				}
			}
		}
		//保存最短边的两个顶点
		aPath[k].vex1=nVex1;
		aPath[k].vex2=nVex2;
		aPath[k].weight=graph.m_aAdjMatrix[nVex1][nVex2];
	 
		//将两个顶点加入集合
		aVisited[nVex1]=true;
		aVisited[nVex2]=true;
	}
 
}