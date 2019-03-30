#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS, QUALIFIER, TYPE };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int getch(void);
void ungetch(int c);

int bufp = 0;
int tokentype;
char out[1000];
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char buf[BUFSIZE];

int main() {
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}


void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*'; )
        ns++;

    dirdcl();
    while (ns-- > 0) strcat(out, " pointer to");
}

void dirdcl(void) {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME) {
        strcpy(name, token);
    } else if (tokentype == QUALIFIER) {
        printf("const");
    } else if (tokentype == TYPE) { 
        printf("type");
    } else {
        printf("error: expected name or (dcl)\n");
    }

    while ((type == gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }   
    }
}

int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t');

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';);
        *p = 0;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = 0;
        ungetch(c);
        if(!strcmp(p, "const") || !strcmp(p, "register")){
            return tokentype = QUALIFIER;
        } else if (!strcmp(token, "char") || !strcmp(token, "int") || !strcmp(token, "double")) {
			return tokentype = TYPE;
        } else {
            return tokentype = NAME;
        }
    } else return tokentype = c;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}