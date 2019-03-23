#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS };

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
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        type = gettoken();
        do {
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                int	count = 0;

                do {
                    count++;
                    gettoken();
                } while (tokentype == '*');

                temp[0] = '\0';
                if (tokentype != NAME)
                    strcat(temp, "(");

                while (count--) strcat(temp, "*");

                strcat(temp, out);
                if (tokentype != NAME)
                    strcat(temp, ")");
                strcpy(out, temp);

                continue;
            }
            else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out ,temp);
            } else printf("invalid input at %s\n", token);
        } while((type = gettoken()) != '\n');
        printf("%s\n", out);
    }
    return 0;
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
        return tokentype = NAME;
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
