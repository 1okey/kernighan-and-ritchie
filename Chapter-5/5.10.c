#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100

int stack_ptr = 0;
double values[MAXVAL];

int getop(char s[], int* argc, char ** argv);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

enum {
    ADD = '+',
    SUB = '-',
    DIV = '/',
    MUL = '*',
    MOD = '%',
    NUM = '0',
};

int main(int argc ,char ** argv)
{
    int type = 0;
    double op2 = 0.0;

    if (argc == 1)
        return 0;

    char	s[MAXOP];
    int * n_args = &argc;
    char ** args = argv;

    while ((type = getop(s, n_args, args++)) != EOF)
    {
        switch(type)
        {
        case NUM:
            push(atof(s));
            break;
        case ADD:
            push(pop() + pop());
            break;
        case MUL:
            push(pop() * pop());
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
            printf("= %.8g\n", pop());
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

int getop (char s[], int * argc, char ** argv)
{
    int	i, c, d;
    if (!(*argc))
        return EOF;
    else if (--(*argc) == 0)
        return '\n';
    else
        argv++;

    while ((s[0] = c = *(*argv)++) == ' ' || c == '\t');

    if (!isdigit(c) && c != '.') {
        if (c == '-') {
            if (isdigit(d = *(*argv)++) || d == '.')
                s[i = 1] = c = d;
            else {
                s[1] = '\0';
                return c;
            }
        } else {
            s[1] = '\0';
            return c;
        }
    } else
        i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = *(*argv)++));
    if (c == '.')
        while (isdigit(s[++i] = c = *(*argv)++));
    s[i] = '\0';
    return NUM;
}


