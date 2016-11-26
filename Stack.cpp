#include<stdio.h>
#include<malloc.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int ElemType;
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stacksize;
}sqstack;

void ClearStack(sqstack *s)
{
	free(s->base);
}

void InitStack(sqstack *s)
{
	s->base = (ElemType*)malloc(sizeof(ElemType)*STACK_INIT_SIZE);
	if(!s->base)
	{
		printf("error\n");
		return ;
	}
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
}

void Push(sqstack *s,ElemType e)
{
	if(s->top - s->base >= s->stacksize)
	{
		s->base = (ElemType*)realloc(s->base,
			(s->stacksize + STACKINCREMENT)*sizeof(ElemType));
		if(!s->base)
		{
			printf("error\n");
			return;
		}
		s->top = s->base + s->stacksize;
		s->stacksize += STACKINCREMENT;
	}
	*s->top++ = e;
}

ElemType Pop(sqstack *s)
{
	if(s->base == s->top)
	{
		printf("empty!\n");
		return -1;
	}
	else
	{
		return *(--s->top);
	}
}

int StackLength(sqstack *s)
{
	int i = 0;
	ElemType *p;
	p = s->top - 1;
	do{
		i++;
		p--;
	}while(p!=s->base-1);
	return i;
}

int StackEmpty(sqstack *s)
{
	return (s->top == s->base);
}

ElemType GetTop(sqstack *s)
{
	if(s->top == s->base)
	{
		printf("empty!\n");
		return -1;
	}
	return *(s->top-1);
}

void output(sqstack *s)
{
	ElemType *p;
	p = s->top - 1;
	do{
		printf("%d ",*p);
		p--;
	}while(p != s->base - 1);
	printf("\n");
}

int main()
{
	sqstack *s;
	s = (sqstack*)malloc(sizeof(sqstack));
	InitStack(s);
	printf("stack is %s\n",(StackEmpty(s)? "empty" : "not empty"));
	int i;
	for(i = 0; i < 10; i++)
		Push(s,i+1);
	printf("length: %d",StackLength(s));
	printf("top:%d\n",GetTop(s));
	output(s);
	Pop(s);
	output(s);
	return 0;
}