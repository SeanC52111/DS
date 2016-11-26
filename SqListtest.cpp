#include<stdio.h>
#include<malloc.h>
#define LISTSIZE 100
#define LISTINCREMENT 10

typedef int ElemType;
typedef struct {
	ElemType* elem;
	int length;
	int listsize;
}SqList;

SqList L;

SqList* InitList()
{
	L.elem=(ElemType*)malloc(sizeof(ElemType)*LISTSIZE);
	if(!L.elem)
	{
		printf("overflow,error!\n");
	}
	L.length=0;
	L.listsize=LISTSIZE;
	return &L;
}

void DestroyList(SqList* L)
{
	free(L);
}

int ListInsert(SqList* L,int i,ElemType e)
{
	ElemType* newbase;
	if(i<1 || i>L->length+1)
	{
		printf("incorrect position!\n");
		return 0;
	}
	if(L->length==L->listsize)
	{
		newbase=(ElemType*)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
		{
			printf("overflow,fail!\n");
			return 0;
		}
		L->elem=newbase;
		L->listsize+=LISTINCREMENT;
	}
	i--;
	for(int j=L->length-1;j>=i;j--)
		L->elem[j+1]=L->elem[j];
	j++;
	L->elem[j]=e;
	L->length++;
	return 1;
}

int ListDelete(SqList* L,int i)
{
	if(L->length==0)
	{
		printf("list is empty!\n");
		return 0;
	}
	else if(i<1 || i>L->length)
	{
		printf("incorrect position!\n");
		return 0;
	}
	int j;
	i--;
	for(j=i;j<L->length-1;j++)
	{
		L->elem[j]=L->elem[j+1];
	}
	L->length--;
	return 1;
}

void ListTraverse(SqList *L)
{
	if(L->length==0)
		printf("empty list!\n");
	else
	{
		int i;
		for(i=0;i<L->length;i++)
			printf("%d ",L->elem[i]);
		printf("\n");
	}
}

int main()
{
	InitList();
	printf("insert 20,22,23,24,24,26\n");
	ListInsert(&L,1,20);
	ListInsert(&L,2,22);
	ListInsert(&L,3,23);
	ListInsert(&L,4,24);
	ListInsert(&L,5,24);
	ListInsert(&L,6,26);
	printf("traverse\n");
	ListTraverse(&L);
	printf("insert 21 to the second position:\n");
	ListInsert(&L,2,21);
	printf("traverse\n");
	ListTraverse(&L);
	printf("delete the 6th number\n");
	ListDelete(&L,6);
	printf("traverse\n");
	ListTraverse(&L);
	printf("insert 25 to the 6th position\n");
	ListInsert(&L,6,25);
	printf("traverse\n");
	ListTraverse(&L);
	return 0;
}