#include<stdio.h>
#include<algorithm>
using namespace std;
#define N 101
int Tree[N];
int findRoot(int x)
{
	if(Tree[x]==-1)
		return x;
	else
	{
		int tmp=findRoot(Tree[x]);
		Tree[x]=tmp;
		return tmp;
	}
}

struct Edge{
	int a,b;
	int cost;
	bool operator<(const Edge &A)const{
		return cost<A.cost;
	}
}edge[6000];

int main()
{
	int n,m,i;
	printf("input vertex number:\n");
	scanf("%d",&n);
	printf("input edge number:\n");
	scanf("%d",&m);
	printf("input edge a,b,cost:\n");
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&edge[i].a,&edge[i].b,&edge[i].cost);
	}
	printf("\n");
	sort(edge+1,edge+1+m);//按权值递增排序
	for(i=1;i<=n;i++)
		Tree[i]=-1;
	int ans=0;
	for(i=1;i<=m;i++)
	{
		int a=findRoot(edge[i].a);
		int b=findRoot(edge[i].b);
		if(a!=b)
		{
			Tree[a]=b;
			ans+=edge[i].cost;
			printf("%d--%d weight:%d\n",edge[i].a,edge[i].b,edge[i].cost);
		}
	}
	printf("%d\n",ans);
	return 0;
}

		