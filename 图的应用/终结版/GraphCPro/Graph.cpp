#include <stdio.h>
#include "Graph.h"
#include <stdlib.h>
#define MAX_VERTEX_NUM  20
void Init(Graph &graph){ //ͼ�ĳ�ʼ��
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
	   printf("����������\n");
	   return false;
	}
	 
	graph.m_aVex[graph.m_nVexNum]=vex;	 
	graph.m_nVexNum++;
	return true;
}
bool InsertEdge(Edge edge,Graph &graph){
	if(edge.vex1<0||edge.vex2<0||edge.vex1>=graph.m_nVexNum||edge.vex2>=graph.m_nVexNum){
		printf("graph.m_nVexNum:%d\n",graph.m_nVexNum);
	    printf("�±�Խ�磡\n");
		return false;
	}
	graph.m_aAdjMatrix[edge.vex1][edge.vex2]=edge.weight;
	graph.m_aAdjMatrix[edge.vex2][edge.vex1]=edge.weight;
	return true;
}
Vex GetVex(int v,Graph &graph){
	if(v>=graph.m_nVexNum){
	 printf("û�д˾���\n");	  
	}
	return graph.m_aVex[v];
}
int FindEdge(int v,Edge aEdge[],Graph &graph){
	int k=0;
	for(int i=0;i<graph.m_nVexNum;i++){
		//�õ��ߵ���Ϣ
		if(graph.m_aAdjMatrix[v][i]!=0){
			printf("%s->%s\t%d\n",graph.m_aVex[v].name,graph.m_aVex[i].name,graph.m_aAdjMatrix[v][i]);
		 k++;
		}
	   
	}
	return k;//���رߵ�����
}
int GetVexNum(Graph graph){
	
	return graph.m_nVexNum;
}
//ʹ��������������㷨����ͼ
void DFS(int v,bool aVisited[],int &nIndex,PathList &pList,Graph &graph)
{
	aVisited[v]=true;//��Ϊ�ѷ���
	pList->vex[nIndex++]=v;//���ʶ���nVex

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

//����DFS�����������õ�����������������Ľ��
void DFSTraverse(int nVex,PathList &pList,Graph &graph)
{
	int nIndex=0;
	bool aVisited[20]={false};
	DFS(nVex,aVisited,nIndex,pList,graph);
}
//Prim�㷨
void Prim(Edge aPath[],Graph &graph)
{
	//�ж�ĳ�����Ƿ�����С�������ļ�����
	bool aVisited[MAX_VERTEX_NUM];
	for(int i=0;i<MAX_VERTEX_NUM;i++)
	{
		aVisited[i]=false;
	}
	aVisited[0]=true;   //0������뼯����

	int min ;
	int nVex1,nVex2;
	for(int k=0;k<graph.m_nVexNum;k++)
	{
		min = 0x7FFFFFFF;
		for(int i=0;i<graph.m_nVexNum;i++)
		{
			if(aVisited[i]) //�Ӽ�����ȡһ����
			{
				for(int j=0;j<graph.m_nVexNum;j++)
				{
					if(!aVisited[j])     //�Ӳ��ڼ����еĶ�����ȡ��һ����
					{
						if((graph.m_aAdjMatrix[i][j]<min)&&(graph.m_aAdjMatrix[i][j]!=0))
						{
							nVex1=i;
							nVex2=j; 
							min=graph.m_aAdjMatrix[i][j];   //�ҳ���̵ı�
						}
					}
				}
			}
		}
		//������̱ߵ���������
		aPath[k].vex1=nVex1;
		aPath[k].vex2=nVex2;
		aPath[k].weight=graph.m_aAdjMatrix[nVex1][nVex2];
	 
		//������������뼯��
		aVisited[nVex1]=true;
		aVisited[nVex2]=true;
	}
 
}