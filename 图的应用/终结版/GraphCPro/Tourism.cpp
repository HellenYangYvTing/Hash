#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "Graph.h"
#include"Tourism.h"
#define MAX_VERTEX_NUM  20

//����ͼ
int CreatGraph(Graph &graph){
	Vex vex;
	Edge edge;
	int i,k;
	int ch;
	char buf[1024];
	int n=0,m;
	FILE *fp1,*fp2;
	
	Init(graph);

	//���ɶ���
	fp1=fopen("Vex.txt","r");
	if(fp1==NULL){
	  printf("��ʧ�ܣ�\n");
	  return 0;
	}
	
	if(fscanf(fp1,"%d",&ch)!=-1)
	n=ch;             //�������
	else {
	printf("�ļ���ȡʧ��\n");
	 return 0;
	}
	//��ʼ��Vex[n]
	printf("������Ŀ��%d\n",n);
    printf("-----����----\n");
	i=0;
	while(fscanf(fp1,"%d\n%s\n%s\n",&vex.num,&vex.name,&vex.desc)!=-1)
	{
		if(!InsertVex(vex,graph)){
		  printf("�����ڵ�ʧ�ܣ�\n");
		  return 0;
		}
	  printf("%d-%s\n",vex.num,vex.name);
	  i++;
	}
	fclose(fp1);

	//���ɱ� 
	i=0;
	fp2=fopen("Edge.txt","rb");
	if(fp2==NULL){
	  printf("��ʧ�ܣ�\n");
	  return 0;
	}
	 printf("-----��----\n");
	while(fscanf(fp2,"%d\t%d\t%d\n",&edge.vex1,&edge.vex2,&edge.weight)!=-1)
	{	 
		if(!InsertEdge(edge,graph)){
		  printf("�����ڵ�ʧ�ܣ�\n");
		  return 0;
		}
		
	    printf("<v%d,v%d> %d\n",edge.vex1,edge.vex2,edge.weight);
	}
    fclose(fp2);
    printf("\n");	 
	return 1;
}
int GetSpotInfo(Graph &graph){
	//printf("graph.m_nVexNum��%d\n",GetVexNum(graph));
	for(int i=0;i<GetVexNum(graph);i++){
		printf("%d-%s\n",graph.m_aVex[i].num,graph.m_aVex[i].name);
	}

	int n=0;
	printf("�������ѯ����ı�ţ�");
	scanf("%d",&n);

	Vex find;
    find=GetVex(n,graph);
	printf("%s\n%s\n",find.name,find.desc);

	//�ܱ߾���
	Edge fedge[20];
	int k;   //�ߵ�����
	printf("----�ܱ߾���----\n");
	k=FindEdge(n,fedge,graph);

	return 1;
}
int TravelPath(Graph &graph)
{
	printf("======���ξ��㵼��======\n");
	//��þ�����
	int nVexNum=GetVexNum(graph);
	//�г����о����ŵ�����
	for(int i=0;i<nVexNum;i++)
	{
		Vex svex=GetVex(i,graph);
		printf("%d",svex.num);
		printf("-");
		printf("%s\n",svex.name);
	}

	//���뾰����
	int nVex;
	printf("��������ʼ���ţ�");
	scanf("%d",&nVex);
	if(nVex<0||nVex>=20)
	{
		printf("�������\n");
		return 0;
	}
	PathList pList=(PathList)malloc(sizeof(Path));
	PathList pHead=pList;
	DFSTraverse(nVex,pList,graph);
	printf("����·��Ϊ��\n");
	int i=1;
	pList=pHead;
	while(pList->next)
	{
		Vex svex=GetVex(pList->vex[0],graph);
		printf("·��%d:",i);
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
	int *path=(int *)malloc(sizeof(int)*graph.m_nVexNum);      //���·��
	int *distance=(int *)malloc(sizeof(int)*graph.m_nVexNum);  //��̾���
	int *s=(int *)malloc(sizeof(int)*graph.m_nVexNum);         //��־
	int MaxWeight=100000;
	int u=0;
	int minDis;

	printf("���������ı�ţ�");
	scanf("%d",&start);
	printf("�������յ�ı�ţ�");
	scanf("%d",&end);

	//��ʼ��
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
	s[start]=1;         //��Ƕ���start�ѴӼ���T���뵽����s����
       
	printf("���·��Ϊ��");
	printf("%s",graph.m_aVex[start].name);
	
    for(int i=1;i<graph.m_nVexNum;i++){
	   minDis=MaxWeight;
	   for(int j=0;j<graph.m_nVexNum;j++){
		   if((s[j]==0)&&(distance[j]<minDis)&&(distance[j]>0)){
			   u=j;
			   minDis=distance[j];
		   }
	   }
	  //  printf("u��%d",u);
		  //��ǰ�Ѳ�����·��ʱ�㷨����
	   if(minDis==MaxWeight){
		   printf("Ϊ����ͨͼ��\n");
	        return 0;
	   }		
	   s[u]=1;              //T->S
		   //printf("u%d\n",u);
		   //�޸Ĵ�start��������������·��
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
			//ע��˴���t��graph.m_aVex[path[t]]��numȡ�ߣ����Բ�����ֱ����graph.m_aVex[path[t]]��
			n++;
		   }
	for(int j=n-2;j>=0;j--){
	       printf("->%s",ch[j]);	
	}
	printf("->%s",graph.m_aVex[end].name );	
	printf("\n��̾���Ϊ��%d\n\n",distance[end]);
	return 1;
}
int DesignPath(Graph &graph){
	 Edge aPath[MAX_VERTEX_NUM];    //����߽ṹ���������������������·
	 Prim(aPath,graph);

	 int nVexNum=GetVexNum(graph);
	 if(nVexNum==0)
	 {
		 printf("���ȴ���ͼ!\n");	 
		 return 0;
	 }
	 int nAllLength=0;
	 printf("��������������֮�������·\n");
	 
	 int i;
	 for(int i=0;i<nVexNum-1;i++)
	 { 
		 Vex sVex1=graph.m_aVex[aPath[i].vex1];  
		 Vex sVex2=graph.m_aVex[aPath[i].vex2];  
		 printf("%s%s\t%dm\n",sVex1.name,sVex2.name,aPath[i].weight);	 
		 nAllLength+=aPath[i].weight;
	 }
	 printf("������·�ܳ���Ϊ:%d\n",nAllLength);	
	 
	 return 1;
}