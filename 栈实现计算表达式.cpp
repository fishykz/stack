#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#pragma warning (disable:4996)
#define maxsize 100
#define datatype int
//定义两个结构体
//一个存放数字
//一个存放运算符
//运算符顺序比较
typedef struct stack
{
	datatype data[maxsize];
	datatype down;
	datatype top;
}SqlStack;
SqlStack* s;

void InitStack(SqlStack* s)//初始化
{
	//s = (SqlStack*)malloc(sizeof(stack)*maxsize);
	s->down = 0;
	s->top = 0;
}
void Push(SqlStack* s, datatype x)//入栈,将x置于栈顶
{
	int b=s->top++;
	s->data[b] = x;



}
char pop(SqlStack* s, datatype c)//出栈
{
	if (s->top == s->down)
	{
		printf("underflow!");
		return 0;
	}
	s->top--;
	c = s->data[int(s->top)];
	return c;
}

datatype GetTop(SqlStack* s)//取栈顶元素
{
	if (s->top == s->down)
	{
		printf("it is empty!");
		return 0;
	}
	return (s->data[int(s->top - 1)]);
}

int operate(int a,char c,int b,SqlStack* d)
{
	int index = 0;
	switch (c)
	{
	case '+':
		index = a + b;
		break;
	case '-':
		index = a - b;
		break;
	case '*':
		index = a * b;
		break;
	case '/':
		index = a / b;
		break;
	case')':
		Push(d, a);
		Push(d, b);
	default:break;
		return index;

	}

}

int getIndex(char theta)   
//获取theta所对应的索引
{
	int index = 0;
	switch (theta)
	{
	case '+':
		index = 0;
		break;
	case '-':
		index = 1;
		break;
	case '*':
		index = 2;
		break;
	case '/':
		index = 3;
		break;
	case '(':
		index = 4;
		break;
	case ')':
		index = 5;
		break;
	case '#':
		index = 6;
	default:break;
	}
	return index;
}

char getPriority(char theta1, char theta2)   //获取theta1与theta2之间的优先级
{
	const char priority[][7] =     //算符间的优先级关系
	{
		{ '>','>','<','<','<','>','>' },
		{ '>','>','<','<','<','>','>' },
		{ '>','>','>','>','<','>','>' },
		{ '>','>','>','>','<','>','>' },
		{ '<','<','<','<','<','=','0' },
		{ '>','>','>','>','0','>','>' },
		{ '<','<','<','<','<','0','=' },
	};

	int index1 = getIndex(theta1);
	int index2 = getIndex(theta2);
	return priority[index1][index2];
}

int FuckC(char* a, char b)//查看元素是否在数组内
{
	int i;
	for (i = 0; i <= int(strlen(a)); i++)
	{
		if (b == a[i])
		{
			return true;
		}
	}
	return 0;
}



int main()
{
	int i = 0;
	int k = 0;
	
	char c;
	SqlStack Num, Sym;
	InitStack(&Num);
	InitStack(&Sym);
	printf("*****welcome 2 YK2's calculator!*****\n");
	printf("*****此辣鸡求值器括号必须严格对称!*****\n");
	char str[100] = { 0 };
	scanf("%s", &str);
	char d[8] = "+-*/()#";
	Push(&Num, 0);
	Push(&Sym, '#');
	Push(&Sym, '+');
	for (i = 0; i < int(strlen(str)); i++)
	{
		c = str[i];
		if (c >= '0' && c <= '9')
		{
			Push(&Num, c - '0');
		}
		else if (FuckC(d, c))
		{
			char j = 0;
			j = GetTop(&Sym);//栈顶元素
			if (getPriority(j, c) == '>')
			{
				int m = 0;
				int k = 0;
				m = pop(&Num, m);
				k = pop(&Num, k);
				pop(&Sym, j);
				int G00dN1ght = 0;
				G00dN1ght = operate(k, j, m, &Num);
				Push(&Num, G00dN1ght);
				Push(&Sym,c);

			}
			else if (getPriority(j, c) == '<')
			{
				Push(&Sym, c);

			}
			else
			{
				;
			}
		int An00y = 0;
		An00y = pop(&Sym, An00y);
		j = GetTop(&Sym);//栈顶元素
		Push(&Sym, An00y);
		if (getPriority(j, c) == '=')
			{
				pop(&Sym, j);
				pop(&Sym, An00y);
			}
		}
		else
		{
			printf("wrong input!");
			return 0;
		}
	}
	while (Sym.top!=Sym.down)
	{
			char Last2index = 0;//栈顶
			char Lastindex = 0;//栈顶下
			Last2index = GetTop(&Sym);
			pop(&Sym, Last2index);
			Lastindex = GetTop(&Sym);
			if (getPriority(Lastindex, Last2index) == '>')
			{
				int m = 0;
				int k = 0;
				m = pop(&Num, m);
				k = pop(&Num, k);
				int G00dN1ght = 0;
				G00dN1ght = operate(k, Lastindex, m, &Num);
				Push(&Num, G00dN1ght);
				if (Lastindex != '#')
				{
					break;
				}
				Push(&Sym, Last2index);
			}
			else if (getPriority(Lastindex, Last2index) == '<')
			{
				Push(&Sym, Last2index);

			}
		else
		{

		}
	}

	printf("Result = %d", GetTop(&Num));
	return 0;
}