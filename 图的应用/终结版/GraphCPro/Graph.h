#ifndef _HEADERNAME_H
#define _HEADERNAME_H
struct Vex{
	int num;          //景点编号
	char name[20];    //景点名字
	char desc[1024];  //景区介绍
};
typedef struct Edge{
	int vex1;          //边的第一个顶点
	int vex2;          //边的第二个顶点
	int weight;        //权值
}Edge;
typedef struct Graph
{
	int m_aAdjMatrix[20][20];   //邻接矩阵
	Vex m_aVex[20];             //顶点信息数组
	int m_nVexNum;              //当前图的定点个数
}Graph;
typedef struct Path
{
	int vex[20];//保存一条路径
	Path *next;//下一条路径
}*PathList;
#endif
void Init(Graph &graph); 
bool InsertVex(Vex vex,Graph &graph);
bool InsertEdge(Edge edge,Graph &graph);
Vex GetVex(int v,Graph &graph);
int FindEdge(int v,Edge aEdge[],Graph &graph);
int GetVexNum(Graph graph);
void DFS(int v,bool aVisited[],int &nIndex,PathList &pList,Graph &graph);
//调用DFS（）函数，得到深度优先搜索遍历的结果
void DFSTraverse(int nVex,PathList &pList,Graph &graph);
void Prim(Edge aPath[],Graph &graph);