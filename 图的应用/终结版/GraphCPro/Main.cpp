#include <stdio.h>
#include <stdlib.h>
#include "Tourism.h"
#include "Graph.h"
int main(){
	Graph graph;
    int sel=1;
	while(sel){

		//ѭ������˵�
		printf("-------������Ϣ����ϵͳ-------\n");
		printf("1.������������ͼ\n");
		printf("2.��ѯ������Ϣ\n");
		printf("3.���ξ��㵼��\n");
		printf("4.�������·��\n");
		printf("5.�����·�滮\n");
		printf("0.�˳�\n");
		printf("�����������ţ�0-5����");
		scanf("%d",&sel);
		switch(sel){
		
		    //����ѡ��sel������Ӧ�Ĳ���

		case 1:{
			   printf("\n--------������������ͼ------\n");
			   CreatGraph(graph);
			   break;
			   }		
		case 2:{
			   printf("\n---------��ѯ������Ϣ--------\n");
			   GetSpotInfo(graph);
			   break;
			   }		
		case 3:{
			   printf("\n----------���ξ��㵼��-------\n");
			   TravelPath(graph);
			   break;
			   }		
		case 4:{
			   printf("\n----------�������·��-------\n");
			   FindShortPath(graph);
			   break;
			   }		
		case 5:{
			   printf("\n----------�����·�滮--------\n");
			   DesignPath(graph);
			   break;
			   }		
		case 0:{
			   printf("�˳�ϵͳ����ӭ�´�ʹ�ã�\n");
			   break;
			   }		 
		}
	}
	system("pause");
    return 0;
}