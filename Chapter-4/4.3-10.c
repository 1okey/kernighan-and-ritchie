#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100

int stack_ptr = 0;
double values[MAXVAL];


int getop(char s[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void ungets(char s[]);
void init_variables();

enum {
    ADD = '+',
    SUB = '-',
    DIV = '/',
    MUL = '*',
    MOD = '%',
    POW = '^',
    SIN = '~',
    PNT = 'P',
    DUP = 'D',
    EXP = 'E',
    CLR = 'C',
    SWP = 'S',
    NUM = '0',
    IN  = '<',
    OUT = '>',
    VAR = 'a',
};

enum { EXECUTE, PRINT, PASS };

double VARIABLES[26];
char VARIABLE = ' ';

int main()
{
    int type = 0;
    int mode = 0;
    double op1 = 0.0;
    double op2 = 0.0;
    char s[MAXOP];
    init_variables();

    while ((type = getop(s)) != EOF)
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
        case POW:
            op2 = pop();
            push(pow(pop(),op2));
            break;
        case SIN:
            push(sin(pop()));
            break;
        case EXP:
            push(exp(pop()));
            break;
        case PNT:
            mode = PRINT;
            break;
        case DUP:
            op1 = pop();
            push(op1);
            push(op1);
            mode = PASS;
            break;
        case SWP:
            op1 = pop();
            op2 = pop();
            push(op2);
            push(op1);
            mode = PASS;
            break;
        case IN:
            VARIABLES[VARIABLE - 'a'] = pop();
            mode = PASS;
            break;
        case OUT:
            push(VARIABLES[VARIABLE - 'a']);
            mode = PRINT;
            break;
        case CLR:
            if(stack_ptr > 0){
                while(pop() != 0.0);
            }
            break;
        case VAR: break;
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
            if(mode == EXECUTE){
                printf("= %.8g\n", pop());
            } else if (mode == PRINT) {
                op1 = pop();
                printf("= %.8g\n", op1);
                push(op1);
            }
            mode = EXECUTE;
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

void init_variables(){
    for(char start = 'a'; start < 'z'; ++start){
        VARIABLES[start - 'a'] = 0.0;
    }
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

    char next;
    if(c == '-'){
        next = getch();
        if(isdigit(next)) {
            ungetch(next);
            c = next;
        }
        else {
            ungetch(next);
            return c;
        }
    } else if(!isdigit(c) && c != '.') {
        if(islower(c)){
            VARIABLE = c;
        }
        return c;
    }

    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()));
    if (c == '.')
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUM;
}

#define BUFSIZE	100

int	eof_pushedback = 0;
int buffer_ptr = 0;
char buffer[BUFSIZE];

int getch (void){
    if (eof_pushedback) {
        eof_pushedback = 0;
        return EOF;
    } else return buffer_ptr > 0 ? buffer[--buffer_ptr] : getchar();
}

void ungetch (int c){
    if (c == EOF)
        eof_pushedback = !0;
    else if (buffer_ptr >= BUFSIZE)
        printf("Error: Too many characters!\n");
    else
        buffer[buffer_ptr++] = c;
}

void ungets(char s[])
{
    while(s != '\0') ungetch(*s++);
}

