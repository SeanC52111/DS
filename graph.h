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
