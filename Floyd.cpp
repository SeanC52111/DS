#include "graph.h"
#include<stdio.h>

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

/*CreateDNMGraph:创建有向网的邻接矩阵*/
int CreateDNMGraph(MGraph *G)
{
	int i,j,k;
	VertexType v1,v2;
	printf("创建有向网的邻接矩阵\n");
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
			if(i==j)
				G->arcs[i][j].adj=0;
		}
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("输入第%d条弧依附的顶点及权值:",k+1);
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
		}
	}
	printf("有向网G的邻接矩阵创建完成\n");
	return OK;
}

//ppath_Floyd 递归输出一条最短路径
void ppath_Floyd(int path[][MAX_VERTEX],int i,int j,MGraph G)
{
	int k;
	k=path[i][j];
	if(k==-1)
		return ;
	ppath_Floyd(path,i,k,G);
	printf("%d-->",G.vers[k]);
	ppath_Floyd(path,k,j,G);
}

//DisPath_Floyd 输出源点到其他各顶点的最短距离
void DisPath_Floyd(AdjMatrix A,int path[][MAX_VERTEX],MGraph G)
{
	int i,j;
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			if(A[i][j].adj==INFINITY)
			{
				if(i!=j)
					printf("从%d到%d没有路径\n",G.vers[i],G.vers[j]);
			}
			else if(i!=j)
			{
				printf("从%d到%d的最短路径长度为:%d\t 路径为:",G.vers[i],G.vers[j],A[i][j].adj);
				printf("%d-->",G.vers[i]);
				ppath_Floyd(path,i,j,G);
				printf("%d\n",G.vers[j]);
			}
}


void Floyd(MGraph G)
{
	AdjMatrix adj;
	int path[MAX_VERTEX][MAX_VERTEX];
	int n=G.vexnum;
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			adj[i][j].adj=G.arcs[i][j].adj;
			path[i][j]=-1;
		}
	}
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(adj[i][j].adj>(adj[i][k].adj+adj[k][j].adj))
				{
					adj[i][j].adj=adj[i][k].adj+adj[k][j].adj;
					path[i][j]=k;
				}
			}
		}
	}
	printf("\n输出最短路径:\n");
	DisPath_Floyd(adj,path,G);
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

int main()
{
	MGraph MG;
	if(CreateDNMGraph(&MG))
	{
		//DispMat(MG);
		Floyd(MG);
	}
	return 0;
}