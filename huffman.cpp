#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define N 50
#define M 2*N-1

typedef struct
{
	char data[5];
	double weight;
	int parent;
	int lchild;
	int rchild;
}HTNode;

typedef char** HuffmanCode;

void CreateHT(HTNode ht[],int n)
{
	
	char *str[]=
	{"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S"
	,"T","U","V","W","X","Y","Z"};
	double fnum[]={8.167,1.492,2.782,4.253,12.702,2.228,
	2.015,6.094,6.966,0.153,0.772,4.025,2.406,6.749,7.507,
	1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,
	1.974,0.074};
	/*
	
	char *str[]=
	{"A","B","C","D"};
	double fnum[]={1.0,3.0,5.0,7.0};
	*/
	int i,k,lnode,rnode;
	double min1,min2;
	for(i=0;i<n;i++)
	{
		strcpy(ht[i].data,str[i]);
		ht[i].weight=fnum[i];
	}
	for(i=0;i<2*n-1;i++)
	{
		ht[i].parent=-1;
		ht[i].lchild=-1;
		ht[i].rchild=-1;
	}
	for(i=n;i<2*n-1;i++)
	{
		min1=100.0;min2=100.0;
		lnode=-1;
		rnode=-1;
		for(k=0;k<=i-1;k++)
			if(ht[k].parent==-1)
			{
				if(ht[k].weight<min1)
				{
					min2=min1;
					rnode=lnode;
					min1=ht[k].weight;
					lnode=k;
				}
				else
					if(ht[k].weight<min2)
					{
						min2=ht[k].weight;
						rnode=k;
					}
			}
		ht[rnode].parent=i;
		ht[lnode].parent=i;
		ht[i].weight=ht[rnode].weight+ht[lnode].weight;
		if(lnode>rnode)
		{
			ht[i].lchild=rnode;
			ht[i].rchild=lnode;
		}
		else
			if(lnode<rnode)
			{
				ht[i].lchild=lnode;
				ht[i].rchild=rnode;
			}
	}
}

void CreateHCode(HTNode ht[],HuffmanCode hcd,int n)
{
	int i,f,c,temp;
	char *hc;
	for(i=0;i<n;i++)
	{
		hc=(char*)malloc(n*sizeof(char));
		hc[n]='\0';
		temp=n-1;
		c=i;
		f=ht[i].parent;
		while(f!=-1)
		{
			if(ht[f].lchild==c)
				hc[temp--]='0';
			else
				hc[temp--]='1';
			c=f;
			f=ht[f].parent;
		}
		hcd[i]=(char*)malloc((n-temp)*sizeof(char));
		strcpy(hcd[i],hc+temp+1);
	}
}

void DispHCode(HTNode ht[],HuffmanCode hcd,int n)
{
	int i,j;
	double sum=0,m=0;
	printf("output Huffman code:\n");
	for(i=0;i<n;i++)
	{
		j=0;
		printf("%s:\t",ht[i].data);
		while(hcd[i][j]!='\0')
		{
			printf("%c",hcd[i][j]);
			j++;
		}
		m+=ht[i].weight;
		sum+=ht[i].weight*j;
		printf("\n");
	}
	printf("average length=%g\n",1.0*sum/m);
}

int main()
{
	int n=26;
	HTNode ht[M];
	HuffmanCode hcd;
	hcd=(HuffmanCode)malloc((2*n)*sizeof(char*));
	CreateHT(ht,n);
	CreateHCode(ht,hcd,n);
	DispHCode(ht,hcd,n);
	printf("\n");
	return 0;
}
