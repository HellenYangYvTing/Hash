#ifndef _HEADERNAME_H
#define _HEADERNAME_H
struct Vex{
	int num;          //������
	char name[20];    //��������
	char desc[1024];  //��������
};
typedef struct Edge{
	int vex1;          //�ߵĵ�һ������
	int vex2;          //�ߵĵڶ�������
	int weight;        //Ȩֵ
}Edge;
typedef struct Graph
{
	int m_aAdjMatrix[20][20];   //�ڽӾ���
	Vex m_aVex[20];             //������Ϣ����
	int m_nVexNum;              //��ǰͼ�Ķ������
}Graph;
typedef struct Path
{
	int vex[20];//����һ��·��
	Path *next;//��һ��·��
}*PathList;
#endif
void Init(Graph &graph); 
bool InsertVex(Vex vex,Graph &graph);
bool InsertEdge(Edge edge,Graph &graph);
Vex GetVex(int v,Graph &graph);
int FindEdge(int v,Edge aEdge[],Graph &graph);
int GetVexNum(Graph graph);
void DFS(int v,bool aVisited[],int &nIndex,PathList &pList,Graph &graph);
//����DFS�����������õ�����������������Ľ��
void DFSTraverse(int nVex,PathList &pList,Graph &graph);
void Prim(Edge aPath[],Graph &graph);