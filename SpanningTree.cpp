#include "graph.h"
#include<stdio.h>
#include<malloc.h>
int LocateMGraphVex(MGraph *G,VertexType v)
{
	/*在邻接矩阵G中，若v是途中的顶点名字，
	则返回v在图G中的位置，否则返回-1*/
	int i;
	for(i=0;i<G->vexnum;i++)
		if(G->vers[i]==v)
			return i;
	return -1;
}

//CreateUDNMGraph 创建无向网的邻接矩阵
int CreateUDNMGraph(MGraph *G)
{
	int i,j,k;
	VertexType v1,v2;
	printf("创建无向网的邻接矩阵\n");
	printf("请输入定点数,vexnum=");
	scanf("%d",&G->vexnum);
	printf("请输入弧数,arcnum=");
	scanf("%d",&G->arcnum);
	printf("弧是否含有信息:IncInfo=");
	scanf("%d",&IncInfo);
	printf("请输入顶点名:");
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
		printf("输入第%d条边依附的顶点及权值:",k+1);
		scanf("%d%d%d",&v1,&v2,&weight);
		i=LocateMGraphVex(G,v1);
		j=LocateMGraphVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			G->arcs[i][j].adj=weight;
			if(IncInfo)
			{
				printf("弧含有相关信息，输入该弧的相关信息:");
				scanf("%d",&G->arcs[i][j].info);
			}
			G->arcs[j][i]=G->arcs[i][j];
		}
	}
	printf("无向网G的邻接矩阵创建完成\n");
	return OK;
}

void DispMat(MGraph G)
{
	int i,j;
	printf("邻接矩阵如下表示:\n");
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
			if(G.arcs[i][j].adj==INFINITY)
				printf("%3s","∞");
			else
				printf("%3d",G.arcs[i][j].adj);
		printf("\n");
	}
}
//寻找lowcost数组中非零的最小值，返回其下标
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

//prim算法求解最小生成树
void prim(MGraph *G,VertexType v)
{
	int lowcost[MAX_VERTEX];//
	VertexType closest[MAX_VERTEX];
	int i,j;
	j=LocateMGraphVex(G,v);
	for(i=0;i<G->vexnum;i++)
		closest[i]=v;//初始化closest数组为起始点v
	for(i=0;i<G->vexnum;i++)
	{
		if(i==j)
			lowcost[i]=0;//自己到自己的距离为0
		else
			lowcost[i]=G->arcs[j][i].adj;
	}
	int min=findmin(lowcost,G->vexnum);
	int count=1;//计数器用来记录已经经过的点
	while(count<G->vexnum)
	{
		lowcost[min]=0;//当前最小值也添加到已经经过的点的集合中
		for(i=0;i<G->vexnum;i++)
		{
			if(lowcost[i]!=0)
			{
				if(G->arcs[i][min].adj<lowcost[i])
				{
					lowcost[i]=G->arcs[i][min].adj;//更新更小的值
					closest[i]=G->vers[min];//更新closest邻近点
				}
			}
		}
		min=findmin(lowcost,G->vexnum);//找到下一个最小值
		count++;
	}
	for(i=0;i<G->vexnum;i++)
	{
		if(G->vers[i]!=closest[i])
			printf("%d -- %d,weight=%d\n",G->vers[i],closest[i],G->arcs[i][LocateMGraphVex(G,closest[i])].adj);//打印出构成生成树的边与顶点
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