#include "graph.h"
#include<stdio.h>
#include<malloc.h>
int LocateMGraphVex(MGraph *G,VertexType v)
{
	/*���ڽӾ���G�У���v��;�еĶ������֣�
	�򷵻�v��ͼG�е�λ�ã����򷵻�-1*/
	int i;
	for(i=0;i<G->vexnum;i++)
		if(G->vers[i]==v)
			return i;
	return -1;
}

//CreateUDNMGraph �������������ڽӾ���
int CreateUDNMGraph(MGraph *G)
{
	int i,j,k;
	VertexType v1,v2;
	printf("�������������ڽӾ���\n");
	printf("�����붨����,vexnum=");
	scanf("%d",&G->vexnum);
	printf("�����뻡��,arcnum=");
	scanf("%d",&G->arcnum);
	printf("���Ƿ�����Ϣ:IncInfo=");
	scanf("%d",&IncInfo);
	printf("�����붥����:");
	for(i=0;i<G->vexnum;i++)
		scanf("%d",&G->vers[i]);
	for(i=0;i<G->vexnum;i++)
	{
		for(j=0;j<G->arcnum;j++)
		{
			G->arcs[i][j].adj=INFINITY;
			G->arcs[i][j].info=NULL;
		}
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("�����%d���������Ķ��㼰Ȩֵ:",k+1);
		scanf("%d%d%d",&v1,&v2,&weight);
		i=LocateMGraphVex(G,v1);
		j=LocateMGraphVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			G->arcs[i][j].adj=weight;
			if(IncInfo)
			{
				printf("�����������Ϣ������û��������Ϣ:");
				scanf("%d",&G->arcs[i][j].info);
			}
			G->arcs[j][i]=G->arcs[i][j];
		}
	}
	printf("������G���ڽӾ��󴴽����\n");
	return OK;
}

void DispMat(MGraph G)
{
	int i,j;
	printf("�ڽӾ������±�ʾ:\n");
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
			if(G.arcs[i][j].adj==INFINITY)
				printf("%3s","��");
			else
				printf("%3d",G.arcs[i][j].adj);
		printf("\n");
	}
}
//Ѱ��lowcost�����з������Сֵ���������±�
int findmin(int lowcost[],int len)
{
	int m=INFINITY;
	int i,index=0;
	for(i=0;i<len;i++)
	{
		if(lowcost[i]!=0)
		{
			if(lowcost[i]<m)
			{
				index=i;
				m=lowcost[i];
			}
		}
	}
	return index;
}

//prim�㷨�����С������
void prim(MGraph *G,VertexType v)
{
	int lowcost[MAX_VERTEX];//
	VertexType closest[MAX_VERTEX];
	int i,j;
	j=LocateMGraphVex(G,v);
	for(i=0;i<G->vexnum;i++)
		closest[i]=v;//��ʼ��closest����Ϊ��ʼ��v
	for(i=0;i<G->vexnum;i++)
	{
		if(i==j)
			lowcost[i]=0;//�Լ����Լ��ľ���Ϊ0
		else
			lowcost[i]=G->arcs[j][i].adj;
	}
	int min=findmin(lowcost,G->vexnum);
	int count=1;//������������¼�Ѿ������ĵ�
	while(count<G->vexnum)
	{
		lowcost[min]=0;//��ǰ��СֵҲ��ӵ��Ѿ������ĵ�ļ�����
		for(i=0;i<G->vexnum;i++)
		{
			if(lowcost[i]!=0)
			{
				if(G->arcs[i][min].adj<lowcost[i])
				{
					lowcost[i]=G->arcs[i][min].adj;//���¸�С��ֵ
					closest[i]=G->vers[min];//����closest�ڽ���
				}
			}
		}
		min=findmin(lowcost,G->vexnum);//�ҵ���һ����Сֵ
		count++;
	}
	for(i=0;i<G->vexnum;i++)
	{
		if(G->vers[i]!=closest[i])
			printf("%d -- %d,weight=%d\n",G->vers[i],closest[i],G->arcs[i][LocateMGraphVex(G,closest[i])].adj);//��ӡ�������������ı��붥��
	}
}

int main()
{
	MGraph G;
	if(CreateUDNMGraph(&G))
	{
		DispMat(G);
		prim(&G,4);
	}
	return 0;
}