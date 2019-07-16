#include <stdio.h>
#include <stdlib.h>
#include "Tourism.h"
#include "Graph.h"
int main(){
	Graph graph;
    int sel=1;
	while(sel){

		//循环输出菜单
		printf("-------景区信息管理系统-------\n");
		printf("1.创建景区景点图\n");
		printf("2.查询景点信息\n");
		printf("3.旅游景点导航\n");
		printf("4.搜索最短路径\n");
		printf("5.铺设电路规划\n");
		printf("0.退出\n");
		printf("请输入操作编号（0-5）：");
		scanf("%d",&sel);
		switch(sel){
		
		    //跟据选项sel进行相应的操作

		case 1:{
			   printf("\n--------创建景区景点图------\n");
			   CreatGraph(graph);
			   break;
			   }		
		case 2:{
			   printf("\n---------查询景点信息--------\n");
			   GetSpotInfo(graph);
			   break;
			   }		
		case 3:{
			   printf("\n----------旅游景点导航-------\n");
			   TravelPath(graph);
			   break;
			   }		
		case 4:{
			   printf("\n----------搜索最短路径-------\n");
			   FindShortPath(graph);
			   break;
			   }		
		case 5:{
			   printf("\n----------铺设电路规划--------\n");
			   DesignPath(graph);
			   break;
			   }		
		case 0:{
			   printf("退出系统，欢迎下次使用！\n");
			   break;
			   }		 
		}
	}
	system("pause");
    return 0;
}