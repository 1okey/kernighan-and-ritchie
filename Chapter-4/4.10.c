#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100

static int stack_ptr = 0;
static double values[MAXVAL];
static double VARIABLES[26];
static char VARIABLE = ' ';
const static char * help_str = 
    "Available commands: \n"
    "[+] - addition\n"
    "[-] - subtraction\n"
    "[/] - division\n"
    "[*] - multiplication\n"
    "[%] - modulus\n"
    "[^] - power\n"
    "[~] - sine\n"
    "[E] - exponent\n"
    "[D] - duplicate (duplicate last entered element)\n"
    "[C] - clear\n"
    "[=] - swap places of last two entered elements\n"
    "[>] - read number into. Example: '3 a >'. \n"
    "[<] - read value of variable. Example: 'a <' \n\n"
    "Calculator parses reverse polish notation, so to execute you input shood look as followed:\n"
    "'3 4 +'   -- should save 7\n"
    "'3 a >'   -- should save 3 into variable 'a'\n"
    "'6 a < +' -- should read value of a and sum it with 6 and save result\n"
    "'5 6 *'   -- should multiply 5 by 6";

int getop(char*c, char*, int*);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void ungets(char s[]);
void init_variables();
int cgetline(char*);

// Commands
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
    SWP = '=',
    NUM = '0',
    IN  = '>',
    OUT = '<',
    VAR = '@',
    HLP = 'H'
};

int main() {
    int type = 0;
    int mode = 0;
    double op1 = 0.0;
    double op2 = 0.0;
    char s[MAXOP];
    char line[MAXOP];
    init_variables();

    while (cgetline(line)) {
        int index = 0;
        while ((type = getop(line, s, &index))) {
            switch(type) {
            case NUM: push(atof(s));                break;
            case ADD: push(pop() + pop());          break;
            case MUL: push(pop() * pop());          break;
            case SIN: push(sin(pop()));             break;
            case EXP: push(exp(pop()));             break;
            case CLR: while(stack_ptr > 1) pop();   break;
            case HLP: printf("%s", help_str);       break;
            case VAR:                               break;
            case POW:
                op2 = pop();
                push(pow(pop(),op2));
                break;
            case PNT:
                if(stack_ptr > 0) {
                    op1 = pop();
                    printf("= %.8g\n", pop());
                    push(op1);
                }
                break;
            case DUP:
                op1 = pop();
                push(op1);
                push(op1);
                break;
            case SWP:
                op1 = pop();
                op2 = pop();
                push(op1);
                push(op2);
                break;
            case IN:
                op1 = pop();
                VARIABLES[VARIABLE - 'a'] = op1;
                push(op1);
                break;
            case OUT:
                push(VARIABLES[VARIABLE - 'a']);
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
            case MOD:
                op2 = pop();
                if(op2 != 0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero division\n");
                break;
            case '\n':
                if (stack_ptr > 0) {
                    printf("= %.8g\n", pop());
                }
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }
        }
    }
    return 0;
}

void init_variables(){
    for(char start = 'a'; start < 'z'; ++start) {
        VARIABLES[start - 'a'] = 0.0;
    }
}

void push(double f) {
    if(stack_ptr < MAXVAL)
        values[stack_ptr++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (stack_ptr > 0)
        return values[--stack_ptr];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char* line, char *s, int* index) {
    int i = 0, c = 0;
    int sign = 0;
    while ((s[0] = c = line[(*index)++]) == ' ' || c == '\t');
    // s[1] = '\0';

    char next;
    if(c == '-'){
        next = line[(*index)++];
        if(isdigit(next)) {
            --(*index);
            c = next;
        }
        else {
            --(*index);
            return c;
        }
    } else if(!isdigit(c) && c != '.') {
        if(isalpha(c) && islower(c)){
            VARIABLE = c;
            return VAR;
        }
        return c;
    }

    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = line[(*index)++]));
    if (c == '.')
        while (isdigit(s[++i] = c = line[(*index)++]));
    s[i] = '\0';
    if (c != EOF)
        --(*index);
    return NUM;
}

int cgetline(char *s) {
    int c, i;
    for(i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
