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
