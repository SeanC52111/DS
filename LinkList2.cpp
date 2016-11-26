#include<stdio.h>
#include<malloc.h>
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode* next;
}LinkList;

void Insert(LinkList *L,int i,ElemType e)
{
	int j;
	LinkList *s,*p;
	if(L->data==-1 && L->next==NULL)
	{
		L->data=e;
		L->next=NULL;
	}
	else
	{
		if(i==1)
		{
			s=(LinkList *)malloc(sizeof(LinkList));
			s->data=e;
			s->next=L;
			L=s;
		}
		else
		{
			p=L;
			j=1;
			while(p && j<i-1)
			{
				j++;
				p=p->next;
			}
			if(!p || j>i-1)
			{
				printf("error\n");
				return;
			}
			else
			{
				s=(LinkList *)malloc(sizeof(LinkList));
				s->data=e;
				s->next=p->next;
				p->next=s;
			}
		}
	}
}

LinkList* Delete(LinkList* L,int i)
{
	int j;
	LinkList *p,*q;
	if(!L)
	{
		printf("EMPTY\n");
	}
	if(i==1)
	{
		p=L;
		L=L->next;
		free(p);
	}
	else
	{
		j=1;
		p=L;
		while(p->next && j<i-1)
		{
			j++;
			p=p->next;
		}
		if(!p->next || j>i-1)
		{
			printf("error\n");
			return NULL;
		}
		q=p->next;
		p->next=q->next;
		free(q);
	}
	return L;
}

void print(LinkList *L)
{
	LinkList *p;
	p=L;
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}

int main()
{
	LinkList *L;
	L=(LinkList *)malloc(sizeof(struct LNode));
	L->data=-1;
	L->next=NULL;
	Insert(L,1,10);
	Insert(L,2,19);
	Insert(L,3,31);
	Insert(L,4,21);
	print(L);
	L=Delete(L,2);
	print(L);
	free(L);
	return 0;
}
