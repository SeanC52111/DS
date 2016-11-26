#define INFINITY 32767
#define MAX_VERTEX 20//��󶥵���
#define OK 1
#define ERROR 0
typedef int VRType;//�����ϵ����
typedef int VertexType;//�������
typedef int InfoType;//�뻡�����Ϣ����
/*matrix*/
typedef enum{DG=1,DN=2,UDG=3,UDN=4}GraphKind;//1.����ͼ��2.��������3.����ͼ��4.������
typedef enum{FALSE=0,TRUE=1}Boolean;
typedef struct ArcCell
{
	VRType adj;//��
	InfoType *info;//�뻡�����Ϣ��ָ��
}ArcCell,AdjMatrix[MAX_VERTEX][MAX_VERTEX];

typedef struct
{
	VertexType vers[MAX_VERTEX];//��Ŷ���һά����
	AdjMatrix arcs;//�ڽӾ����ά����
	int vexnum;//��������
	int arcnum;//�ܱ���
	GraphKind kind;//ͼ�������־
}MGraph; //�ڽӾ���ṹ����
/*list*/
typedef struct ArcNode //�߽��Ľṹ����
{
	int adjvex;
	struct ArcNode *nextarc;
	InfoType info;//�洢�뻡��ص���Ϣ
}ArcNode;
typedef struct VNode //��ͷ���ṹ����
{
	VertexType data;//������Ϣ
	int indegree; //�����Ϣ
	ArcNode *firstarc;//ָ���һ�������ö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX];
typedef struct
{
	AdjList vertices;//��ͷ�������
	int vexnum;//��������
	int arcnum;//�ܱ���
	GraphKind kind;//ͼ�������־
}ALGraph; //�ڽӱ�洢�ṹ����
int IncInfo=0;//��ǻ����ߣ����Ƿ�����Ϣ
int weight=INFINITY;//��¼���Ȩֵ��Ϣ


#include<stdio.h>
#include<malloc.h>
/*LocateMGraphVex: ��λͼ�ж���λ��*/
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
/* CreateDGMGraph:��������ͼG���ڽӾ���*/
int CreateDGMGraph(MGraph *G)
{
	int i,j,k;
	VertexType v1,v2;
	printf("��������ͼG���ڽӾ���\n");
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
			G->arcs[i][j].adj=0;
			G->arcs[i][j].info=NULL;
		}
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("�����%d������������������:",k+1);
		scanf("%d%d",&v1,&v2);
		i=LocateMGraphVex(G,v1);
		j=LocateMGraphVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			G->arcs[i][j].adj=1;
			if(IncInfo)
			{
				printf("�����������Ϣ������û��������Ϣ:");
				scanf("%d",&G->arcs[i][j].info);
			}
		}
	}
	printf("����ͼG���ڽӾ��󴴽����.\n");
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

//CreateUDGMGraph ��������ͼ���ڽӾ���
int CreateUDGMGraph(MGraph *G)
{
	int i,j,k;
	VertexType v1,v2;
	printf("��������ͼ���ڽӾ���\n");
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
			G->arcs[i][j].adj=0;
			G->arcs[i][j].info=NULL;
		}
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("�����%d���������Ķ���:",k+1);
		scanf("%d%d",&v1,&v2);
		i=LocateMGraphVex(G,v1);
		j=LocateMGraphVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			G->arcs[i][j].adj=1;
			if(IncInfo)
			{
				printf("�����������Ϣ������û��������Ϣ:");
				scanf("%d",&G->arcs[i][j].info);
			}
			G->arcs[j][i]=G->arcs[i][j];
		}
	}
	printf("����ͼG���ڽӾ��󴴽����\n");
	return	OK;
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
			G->arcs[i][j].adj=0;
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

int CreateMGraph(MGraph *G)
{
	printf("ͼ������: 1��ʾ����ͼ,2��ʾ������,3��ʾ����ͼ,4��ʾ������\n");
	printf("������ͼ������:");
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

/*����ͼ���ڽӱ�*/

//LocateAdjListVex ��ͼ�ж���λ��
int LocateAdjListVex(ALGraph *G,VertexType v)
{
	int i;
	for(i=0;i<G->vexnum;i++)
		if(G->vertices[i].data==v)
			return i;
	return -1;
}

//CreateDGAdjList ��������ͼG���ڽӱ�
int CreateDGAdjList(ALGraph *G)
{
	/*�����������ͼ�Ķ������ͱ������������ڽӱ�洢�ṹ
	,��indegree�����д�Ŷ���������Ϣ��������ĳ��߽�㰴��������
    */
	int v1,v2;
	int i,j,k;
	ArcNode *s;
	ArcNode *p;
	ArcNode *q;
	printf("��������ͼG���ڽӱ�\n");
	printf("�����붥������,vexnum=");
	scanf("%d",&G->vexnum);
	printf("�����뻡��,arcnum=");
	scanf("%d",&G->arcnum);
	printf("�������ͷ�����Ϣ(������):");
	for(i=0;i<G->vexnum;i++)
	{
		scanf("%d",&G->vertices[i].data);//���붥����
		G->vertices[i].firstarc=NULL;//��ʼ����ͷ����firstarc
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("�����%d���������Ķ���:",k+1);
		scanf("%d%d",&v1,&v2);//���뻡β����ͷ�����
		i=LocateAdjListVex(G,v1);
		j=LocateAdjListVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			p=(ArcNode *)malloc(sizeof(ArcNode));
			p->adjvex=j;
			p->nextarc=NULL;
			q=G->vertices[i].firstarc;
			//���������ӱ߽��
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
	printf("����ͼG���ڽӱ������\n");
	return OK;
}

//CreateDNAdjList ����������G���ڽӱ�
int CreateDNAdjList(ALGraph *G)
{
	int v1,v2;
	int i,j,k;
	ArcNode *p;
	ArcNode *s;
	ArcNode *q;
	printf("����������G���ڽӱ�\n");
	printf("�����붥����,vexnum=");
	scanf("%d",&G->vexnum);
	printf("�����뻡��,arcnum=");
	scanf("%d",&G->arcnum);
	printf("�������ͷ�����Ϣ����������:");
	for(i=0;i<G->vexnum;i++)
	{
		scanf("%d",&G->vertices[i].data);
		G->vertices[i].firstarc=NULL;
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("�����%d���������Ķ��㼰��Ȩֵ:",k+1);
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
			//���������ӱ߽��
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
	printf("������G���ڽӱ������\n");
	return OK;
}

//CreateUDGAdjList ��������ͼG���ڽӱ�
int CreateUDGAdjList(ALGraph *G)
{
	int v1,v2;
	int i,j,k;
	ArcNode *p;
	ArcNode *q;
	ArcNode *s;
	printf("��������ͼG���ڽӱ�\n");
	printf("�����붥����,vexnum=");
	scanf("%d",&G->vexnum);
	printf("���������,arcnum=");
	scanf("%d",&G->arcnum);
	printf("�������ͷ�����Ϣ����������:");
	for(i=0;i<G->vexnum;i++)
	{
		scanf("%d",&G->vertices[i].data);
		G->vertices[i].firstarc=NULL;
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("�����%d���������Ķ���:",k+1);
		scanf("%d%d",&v1,&v2);
		i=LocateAdjListVex(G,v1);
		j=LocateAdjListVex(G,v2);
		if(i!=-1 && j!=-1)
		{
			p=(ArcNode *)malloc(sizeof(ArcNode));
			p->adjvex=j;
			p->nextarc=NULL;
			q=G->vertices[i].firstarc;
			//���������ӱ߽��
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
		//���������ӱ߽��
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
	printf("����ͼG���ڽӱ������\n");
	return OK;
}

//CreateUDNAdjList ����������G���ڽӱ�
int CreateUDNAdjList(ALGraph *G)
{
	int v1,v2;
	int i,j,k;
	ArcNode *p;
	ArcNode *q;
	ArcNode *s;
	printf("����������G���ڽӱ�\n");
	printf("�����붥����,vexnum=");
	scanf("%d",&G->vexnum);
	printf("���������,arcnum=");
	scanf("%d",&G->arcnum);
	printf("�������ͷ�����Ϣ����������:");
	for(i=0;i<G->vexnum;i++)
	{
		scanf("%d",&G->vertices[i].data);
		G->vertices[i].firstarc=NULL;
	}
	for(k=0;k<G->arcnum;k++)
	{
		printf("�����%d���������Ķ��㼰��Ȩֵ:",k+1);
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
			//���������ӱ߽��
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
		//���������ӱ߽��
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
	printf("������G���ڽӱ������\n");
	return OK;
}

//CreateAdjList ����ͼG���ڽӱ�
int CreateAdjList(ALGraph *G)
{
	printf("ͼ������ 1��ʾ����ͼ��2��ʾ��������3��ʾ����ͼ��4��ʾ������\n");
	printf("������ͼ������:\n");
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
	printf("�ڽӱ�������ʾ:\n");
	printf("λ��  ������  �ڽӱ�");
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
	printf("����ͼ���ڽӾ�����ڽӱ�\n");
	while(tag)
	{
		printf("����ͼ���ڽӾ���\n");
		if(CreateMGraph(&MG))
			DispMat(MG);
		printf("\n");
		printf("����ͼ���ڽӱ�\n");
		if(CreateAdjList(&AG))
			DispAdjList(AG);
		printf("\n");
		printf("������������1����������0:");
		scanf("%d",&tag);
		printf("\n");
	}
	return 0;
}

