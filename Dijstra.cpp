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

void ppath_Dijkstra(int path[],int i,VertexType v,MGraph G)
{
	int k;
	k=path[i];
	if(k==LocateMGraphVex(&G,v))
		return ;
	ppath_Dijkstra(path,k,v,G);
	printf("%d-->",G.vers[k]);
}

void DisPath_Dijkstra(int dist[],int path[],int final[],MGraph G,VertexType v)
{
	int i,k;
	k=LocateMGraphVex(&G,v);
	printf("\n");
	for(i=0;i<G.vexnum;i++)
		if(final[i]==TRUE && i!=k)
		{
			printf("从%d到%d的最短路径长度为:%d\t 路径为:",v,G.vers[i],dist[i]);
			printf("%d-->",v);
			ppath_Dijkstra(path,i,v,G);
			printf("%d\n",G.vers[i]);
		}
		else
			printf("从%d到%d不存在路径\n",v,G.vers[i]);
}

void Dijkstra(MGraph G,VertexType v)
{
	int dist[MAX_VERTEX];
	int path[MAX_VERTEX];
	int final[MAX_VERTEX];
	int mindis,u;
	int i,j,k;
	k=LocateMGraphVex(&G,v);
	for(i=0;i<G.vexnum;i++)
	{
		dist[i]=G.arcs[k][i].adj;
		final[i]=FALSE;
		if(G.arcs[k][i].adj<INFINITY)
			path[i]=k;
		else
			path[i]=-1;
	}
	final[k]=TRUE;
	path[k]=0;
	for(i=0;i<G.vexnum;i++)
	{
		mindis=INFINITY;
		u=-1;
		for(j=0;j<G.vexnum;j++)
		{
			if(final[j]==FALSE && dist[j]<mindis)
			{
				u=j;
				mindis=dist[j];
			}
		}
		final[u]=TRUE;
		for(j=0;j<G.vexnum;j++)
		{
			if(final[j]==FALSE)
				if(G.arcs[u][j].adj<INFINITY &&
					(mindis+G.arcs[u][j].adj)<dist[j])
				{
					dist[j]=mindis+G.arcs[u][j].adj;
					path[j]=u;
				}
		}
	}
	printf("输出最短路径:\n");
	DisPath_Dijkstra(dist,path,final,G,v);
}

int main()
{
	MGraph G;
	if(CreateDNMGraph(&G))
	{
		printf("Dijkstra:\n");
		Dijkstra(G,G.vers[0]);
	}
	return 0;
}
