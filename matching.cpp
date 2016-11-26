#include<stdio.h>
#include<malloc.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char ElemType;
typedef struct{
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
		return 'F';
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
		return 'F';
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
	ElemType ch,e;
	int i=0;
	sqstack *s;
	s = (sqstack*)malloc(sizeof(sqstack));
	InitStack(s);
	printf("read the first ch:");
	ch = getchar();
	while(ch != '0')
	{
		if(ch == '(' || ch == ')' || ch == '[' || ch == ']')
		{
			switch(ch)
			{
			case '(': {Push(s,ch);break;}
			case '[': {Push(s,ch);break;}
			case ')':
				{
					e=GetTop(s);
					if(e != '(')
						i = 1;
					else if(StackEmpty(s))
						i = 1;
					Pop(s);
					break;
				}
			case ']':
				{
					e=GetTop(s);
					if(e != '[')
						i = 1;
					else if(StackEmpty(s))
						i = 1;
					Pop(s);
					break;
				}
			}
			printf("continue reading next ch:");
			getchar();
			ch = getchar();
		}
	}
	if(StackEmpty(s) && i == 0)
		printf("success!\n");
	else
		printf("fail!\n");
	ClearStack(s);
	return 0;
}
