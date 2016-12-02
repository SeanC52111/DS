#include "graph.h"
#include<stdio.h>

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

/*CreateDNMGraph:�������������ڽӾ���*/
int CreateDNMGraph(MGraph *G)
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
			if(i==j)
				G->arcs[i][j].adj=0;
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
		}
	}
	printf("������G���ڽӾ��󴴽����\n");
	return OK;
}

//ppath_Floyd �ݹ����һ�����·��
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

//DisPath_Floyd ���Դ�㵽�������������̾���
void DisPath_Floyd(AdjMatrix A,int path[][MAX_VERTEX],MGraph G)
{
	int i,j;
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			if(A[i][j].adj==INFINITY)
			{
				if(i!=j)
					printf("��%d��%dû��·��\n",G.vers[i],G.vers[j]);
			}
			else if(i!=j)
			{
				printf("��%d��%d�����·������Ϊ:%d\t ·��Ϊ:",G.vers[i],G.vers[j],A[i][j].adj);
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
	printf("\n������·��:\n");
	DisPath_Floyd(adj,path,G);
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