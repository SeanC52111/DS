#define INFINITY 32767
#define MAX_VERTEX 20//最大顶点数
#define OK 1
#define ERROR 0
typedef int VRType;//顶点关系类型
typedef int VertexType;//结点类型
typedef int InfoType;//与弧相关信息类型
/*matrix*/
typedef enum{DG=1,DN=2,UDG=3,UDN=4}GraphKind;//1.有向图，2.有向网，3.无向图，4.无向网
typedef enum{FALSE=0,TRUE=1}Boolean;
typedef struct ArcCell
{
	VRType adj;//弧
	InfoType *info;//与弧相关信息的指针
}ArcCell,AdjMatrix[MAX_VERTEX][MAX_VERTEX];

typedef struct
{
	VertexType vers[MAX_VERTEX];//存放顶点一维数组
	AdjMatrix arcs;//邻接矩阵二维数组
	int vexnum;//顶点总数
	int arcnum;//总边数
	GraphKind kind;//图的种类标志
}MGraph; //邻接矩阵结构类型
/*list*/
typedef struct ArcNode //边结点的结构类型
{
	int adjvex;
	struct ArcNode *nextarc;
	InfoType info;//存储与弧相关的信息
}ArcNode;
typedef struct VNode //表头结点结构类型
{
	VertexType data;//顶点信息
	int indegree; //入度信息
	ArcNode *firstarc;//指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX];
typedef struct
{
	AdjList vertices;//表头结点数组
	int vexnum;//顶点总数
	int arcnum;//总边数
	GraphKind kind;//图的种类标志
}ALGraph; //邻接表存储结构类型
int IncInfo=0;//标记弧（边）上是否有信息
int weight=INFINITY;//记录最大权值信息


#include<stdio.h>
#include<malloc.h>
/*LocateMGraphVex: 定位图中顶点位序*/
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
/* CreateDGMGraph:创建有向图G的邻接矩阵*/
int CreateDGMGraph(MGraph *G)
{
	int i,j,k;
	VertexType v1,v2;
	printf("创建有向图G的邻接矩阵\n");
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
			G->arcs[i][j].adj=0;
			G->arcs[i][j].info=NULL;
		}
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("输入第%d条弧依附的两个顶点:",k+1);
		scanf("%d%d",&v1,&v2);
		i=LocateMGraphVex(G,v1);
		j=LocateMGraphVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			G->arcs[i][j].adj=1;
			if(IncInfo)
			{
				printf("弧含有相关信息，输入该弧的相关信息:");
				scanf("%d",&G->arcs[i][j].info);
			}
		}
	}
	printf("有向图G的邻接矩阵创建完成.\n");
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

//CreateUDGMGraph 创建无向图的邻接矩阵
int CreateUDGMGraph(MGraph *G)
{
	int i,j,k;
	VertexType v1,v2;
	printf("创建无向图的邻接矩阵\n");
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
			G->arcs[i][j].adj=0;
			G->arcs[i][j].info=NULL;
		}
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("输入第%d条边依附的顶点:",k+1);
		scanf("%d%d",&v1,&v2);
		i=LocateMGraphVex(G,v1);
		j=LocateMGraphVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			G->arcs[i][j].adj=1;
			if(IncInfo)
			{
				printf("弧含有相关信息，输入该弧的相关信息:");
				scanf("%d",&G->arcs[i][j].info);
			}
			G->arcs[j][i]=G->arcs[i][j];
		}
	}
	printf("无向图G的邻接矩阵创建完成\n");
	return	OK;
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
			G->arcs[i][j].adj=0;
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

int CreateMGraph(MGraph *G)
{
	printf("图的种类: 1表示有向图,2表示有向网,3表示无向图,4表示无向网\n");
	printf("请输入图的种类:");
	scanf("%d",&G->kind);
	switch(G->kind)
	{
	case DG: return CreateDGMGraph(G);
	case DN: return CreateDNMGraph(G);
	case UDG:return CreateUDGMGraph(G);
	case UDN:return CreateUDNMGraph(G);
	default: return ERROR;
	}
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

/*创建图的邻接表*/

//LocateAdjListVex 求图中顶点位序
int LocateAdjListVex(ALGraph *G,VertexType v)
{
	int i;
	for(i=0;i<G->vexnum;i++)
		if(G->vertices[i].data==v)
			return i;
	return -1;
}

//CreateDGAdjList 创建有向图G的邻接表
int CreateDGAdjList(ALGraph *G)
{
	/*输入给定有向图的顶点数和边数，建立其邻接表存储结构
	,在indegree分量中存放顶点的入度信息，各顶点的出边结点按降序排列
    */
	int v1,v2;
	int i,j,k;
	ArcNode *s;
	ArcNode *p;
	ArcNode *q;
	printf("创建有向图G的邻接表\n");
	printf("请输入顶点总数,vexnum=");
	scanf("%d",&G->vexnum);
	printf("请输入弧数,arcnum=");
	scanf("%d",&G->arcnum);
	printf("请输入表头结点信息(顶点名):");
	for(i=0;i<G->vexnum;i++)
	{
		scanf("%d",&G->vertices[i].data);//输入顶点名
		G->vertices[i].firstarc=NULL;//初始化表头结点的firstarc
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("输入第%d条弧依附的顶点:",k+1);
		scanf("%d%d",&v1,&v2);//输入弧尾、弧头结点名
		i=LocateAdjListVex(G,v1);
		j=LocateAdjListVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			p=(ArcNode *)malloc(sizeof(ArcNode));
			p->adjvex=j;
			p->nextarc=NULL;
			q=G->vertices[i].firstarc;
			//按降序链接边结点
			if(q==NULL)
				G->vertices[i].firstarc=p;
			else
			{
				if(q->adjvex<p->adjvex)
				{
					G->vertices[i].firstarc=p;
					p->nextarc=q;
				}
				else
				{
					while(q!=NULL&&q->adjvex>p->adjvex)
					{
						s=q;
						q=q->nextarc;
					}
					if(q!=NULL)
					{
						s->nextarc=q;
						p->nextarc=q;
					}
					else
						s->nextarc=p;
				}
			}
		}
	}
	printf("有向图G的邻接表创建完成\n");
	return OK;
}

//CreateDNAdjList 创建有向网G的邻接表
int CreateDNAdjList(ALGraph *G)
{
	int v1,v2;
	int i,j,k;
	ArcNode *p;
	ArcNode *s;
	ArcNode *q;
	printf("创建有向网G的邻接表\n");
	printf("请输入顶点数,vexnum=");
	scanf("%d",&G->vexnum);
	printf("请输入弧数,arcnum=");
	scanf("%d",&G->arcnum);
	printf("请输入表头结点信息（顶点名）:");
	for(i=0;i<G->vexnum;i++)
	{
		scanf("%d",&G->vertices[i].data);
		G->vertices[i].firstarc=NULL;
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("输入第%d条弧依附的顶点及其权值:",k+1);
		scanf("%d%d%d",&v1,&v2,&weight);
		i=LocateAdjListVex(G,v1);
		j=LocateAdjListVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			p=(ArcNode *)malloc(sizeof(ArcNode));
			p->adjvex=j;
			p->info=weight;
			p->nextarc=NULL;
			q=G->vertices[i].firstarc;
			//按降序链接边结点
			if(q==NULL)
				G->vertices[i].firstarc=p;
			else
			{
				if(q->adjvex<p->adjvex)
				{
					G->vertices[i].firstarc=p;
					p->nextarc=q;
				}
				else
				{
					while(q!=NULL&&q->adjvex>p->adjvex)
					{
						s=q;
						q=q->nextarc;
					}
					if(q!=NULL)
					{
						s->nextarc=q;
						p->nextarc=q;
					}
					else
						s->nextarc=p;
				}
			}
		}
	}
	printf("有向网G的邻接表创建完成\n");
	return OK;
}

//CreateUDGAdjList 创建无向图G的邻接表
int CreateUDGAdjList(ALGraph *G)
{
	int v1,v2;
	int i,j,k;
	ArcNode *p;
	ArcNode *q;
	ArcNode *s;
	printf("创建无向图G的邻接表\n");
	printf("请输入顶点数,vexnum=");
	scanf("%d",&G->vexnum);
	printf("请输入边数,arcnum=");
	scanf("%d",&G->arcnum);
	printf("请输入表头结点信息（顶点名）:");
	for(i=0;i<G->vexnum;i++)
	{
		scanf("%d",&G->vertices[i].data);
		G->vertices[i].firstarc=NULL;
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("输入第%d条边依附的顶点:",k+1);
		scanf("%d%d",&v1,&v2);
		i=LocateAdjListVex(G,v1);
		j=LocateAdjListVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			p=(ArcNode *)malloc(sizeof(ArcNode));
			p->adjvex=j;
			p->nextarc=NULL;
			q=G->vertices[i].firstarc;
			//按降序链接边结点
			if(q==NULL)
				G->vertices[i].firstarc=p;
			else
			{
				if(q->adjvex<p->adjvex)
				{
					G->vertices[i].firstarc=p;
					p->nextarc=q;
				}
				else
				{
					while(q!=NULL&&q->adjvex>p->adjvex)
					{
						s=q;
						q=q->nextarc;
					}
					if(q!=NULL)
					{
						s->nextarc=q;
						p->nextarc=q;
					}
					else
						s->nextarc=p;
				}
			}
		}
		p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=i;
		p->nextarc=NULL;
		q=G->vertices[j].firstarc;
		//按降序链接边结点
		if(q==NULL)
			G->vertices[j].firstarc=p;
		else
		{
			if(q->adjvex<p->adjvex)
			{
				G->vertices[j].firstarc=p;
				p->nextarc=q;
			}
			else
			{
				while(q!=NULL&&q->adjvex>p->adjvex)
				{
					s=q;
					q=q->nextarc;
				}
				if(q!=NULL)
				{
					s->nextarc=q;
					p->nextarc=q;
				}
				else
					s->nextarc=p;
			}
		}
	}
	printf("无向图G的邻接表创建完成\n");
	return OK;
}

//CreateUDNAdjList 创建无向网G的邻接表
int CreateUDNAdjList(ALGraph *G)
{
	int v1,v2;
	int i,j,k;
	ArcNode *p;
	ArcNode *q;
	ArcNode *s;
	printf("创建无向网G的邻接表\n");
	printf("请输入顶点数,vexnum=");
	scanf("%d",&G->vexnum);
	printf("请输入边数,arcnum=");
	scanf("%d",&G->arcnum);
	printf("请输入表头结点信息（顶点名）:");
	for(i=0;i<G->vexnum;i++)
	{
		scanf("%d",&G->vertices[i].data);
		G->vertices[i].firstarc=NULL;
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("输入第%d条边依附的顶点及其权值:",k+1);
		scanf("%d%d%d",&v1,&v2,&weight);
		i=LocateAdjListVex(G,v1);
		j=LocateAdjListVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			p=(ArcNode *)malloc(sizeof(ArcNode));
			p->adjvex=j;
			p->info=weight;
			p->nextarc=NULL;
			q=G->vertices[i].firstarc;
			//按降序链接边结点
			if(q==NULL)
				G->vertices[i].firstarc=p;
			else
			{
				if(q->adjvex<p->adjvex)
				{
					G->vertices[i].firstarc=p;
					p->nextarc=q;
				}
				else
				{
					while(q!=NULL&&q->adjvex>p->adjvex)
					{
						s=q;
						q=q->nextarc;
					}
					if(q!=NULL)
					{
						s->nextarc=q;
						p->nextarc=q;
					}
					else
						s->nextarc=p;
				}
			}
		}
		p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=i;
		p->info=weight;
		p->nextarc=NULL;
		q=G->vertices[j].firstarc;
		//按降序链接边结点
		if(q==NULL)
			G->vertices[j].firstarc=p;
		else
		{
			if(q->adjvex<p->adjvex)
			{
				G->vertices[j].firstarc=p;
				p->nextarc=q;
			}
			else
			{
				while(q!=NULL&&q->adjvex>p->adjvex)
				{
					s=q;
					q=q->nextarc;
				}
				if(q!=NULL)
				{
					s->nextarc=q;
					p->nextarc=q;
				}
				else
					s->nextarc=p;
			}
		}
	}
	printf("无向网G的邻接表创建完成\n");
	return OK;
}

//CreateAdjList 创建图G的邻接表
int CreateAdjList(ALGraph *G)
{
	printf("图的种类 1表示有向图，2表示有向网，3表示无向图，4表示无向网\n");
	printf("请输入图的种类:\n");
	scanf("%d",&G->kind);
	switch(G->kind)
	{
	case DG: return CreateDGAdjList(G);
	case DN: return CreateDNAdjList(G);
	case UDG:return CreateUDGAdjList(G);
	case UDN:return CreateUDNAdjList(G);
	default: return ERROR;
	}
}

void DispAdjList(ALGraph G)
{
	int i;
	ArcNode *p;
	printf("邻接表如下所示:\n");
	printf("位序  顶点名  邻接边");
	for(i=0;i<G.vexnum;i++)
	{
		printf("\n%-7dV%-8d:",i,G.vertices[i].data);
		p=G.vertices[i].firstarc;
		while(p)
		{
			printf("-->%d",p->adjvex);
			p=p->nextarc;
		}
	}
	printf("\n");
}

int main()
{
	MGraph MG;
	ALGraph AG;
	int tag=1;
	printf("创建图的邻接矩阵和邻接表\n");
	while(tag)
	{
		printf("创建图的邻接矩阵\n");
		if(CreateMGraph(&MG))
			DispMat(MG);
		printf("\n");
		printf("创建图的邻接表\n");
		if(CreateAdjList(&AG))
			DispAdjList(AG);
		printf("\n");
		printf("继续测试输入1，否则输入0:");
		scanf("%d",&tag);
		printf("\n");
	}
	return 0;
}

