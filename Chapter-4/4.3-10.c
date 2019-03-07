#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int stack_ptr = 0;
int buffer_ptr = 0;
double values[MAXVAL];
char buffer[BUFSIZE];


int getop(char s[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void ungets(char s[]);

// operators for problem #4.5
enum {
	ADD = '+',
	SUB = '-',
	DIV = '/',
	MUL = '*',
	MOD = '%',
	POW = '^',
	SIN = '~',
	EXP = 'E',
	CLR = 'C',
	SWP = 'S'
}

int main()
{
	int type = 0;
	double op2 = 0.0;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) 
	{
		switch(type)
		{
		case NUMBER:
			push(atof(s));
			break;
		case SUM:
			push(pop() + pop());
			break;
		case MUL:
			push(pop() * pop());
			break;
		case POW:
			op2 = pop();
			push(pow(pop(),op2));
			break;
		case SIN:
			//TODO
			break;
		case EXP:
			//TODO
			break;
		case SWP:
			//TODO
			break;
		case CLR:
			//TODO
			break;
		case SUB:
			op2 = pop();
			push(pop() - op2);
			break;
		case DIV:
			op2 = pop();
			if(op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero division\n");
			break;
		// solution for problem #4.3
		case MOD:
			op2 = pop();
			if(op2 != 0)
				push(fmod(pop(), op2));
			else
				printf("error: zero division\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

void push(double f)
{
	if(stack_ptr < MAXVAL)
		values[stack_ptr++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (stack_ptr > 0)
		return values[--stack_ptr];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getop(char s[])
{
	int i = 0, c = 0;
	int sign = 0;
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	
	if(!isdigit(c) && c != '.' && c != '-')
		return c;
	
	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));
	if (c == '.' || c == '-')
		while (isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return i == 1 ? '-' : NUMBER;
}

int getch(void)
{
	return (buffer_ptr > 0) ? buffer[--buffer_ptr] : getchar();
}

void ungetch(int c)
{
	if(buffer_ptr >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buffer[buffer_ptr++] = c;
}

// Solution of problem #4.7
void ungets(char s[])
{
	while(s != '\0') ungetch(*s++);
}
