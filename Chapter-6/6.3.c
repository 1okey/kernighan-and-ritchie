#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 100

#define MAXWORD 100
#define MAX_OCCURENCES 100


struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char * _strdup(char *);
int getch(void);
void ungetch(int c);
int not_reserved(char * word);
char * reserved[] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default "
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "inline",
    "int",
    "long",
    "register",
    "restrict",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while",
};
char * articles[] = {"a", "an", "the"};
int bufp = 0;
char buf[BUFSIZE];

#define NKEYS ((sizeof reserved) / (sizeof reserved[0]))

struct tnode {
    char *word;
    int count;
    int * occurences;
    struct tnode * left;
    struct tnode * right;
};

int line_number = 1;

int main(int argc, char ** argv) {
    struct tnode * root;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && not_reserved(word) && not_article(word))
            root = addtree(root,word);

    treeprint(root);
    return 0;
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = _strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        p->occurences = (int*) malloc(sizeof(int) * MAX_OCCURENCES);
        p->occurences[p->count - 1] = line_number;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->occurences[p->count++] = line_number;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

void treeprint(struct tnode *p){
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s , on lines ", p->count, p->word);
        for(unsigned i = 0; i < p->count; ++i)
            printf("%d ", p->occurences[i]);
        printf("\n");
        treeprint(p->right);
    }
}

struct tnode * talloc(void) {
    return (struct tnode*) malloc(sizeof(struct tnode));
}

char * _strdup(char *s) {
    char * p;
    p = (char*) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p,s);
    return p;
}

int getword(char * word, int lim){
    int c;
    char *w = word;

    while(isspace(c = getch())) {
        if (c == '\n')
            line_number++;
    }

    if(c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        if (c == '"')
            while((c = getch() != '"'));
        else if(c == '#') {
            while((c = getch() != '\n'));
        }
        else if(c == '_')
            while((c = getch() != ' '));
        else if(c == '/') {
            char next = getch();
            if(next == '/'){
                while((c = getchar()) != '\n');
            } else if(next == '*'){
                while((next = c) && (c = getchar())){
                    if (c == '\n') line_number++;
                    if(next == '*' && c == '/') break;
                }
            } else {
                ungetch(next);
                ungetch(c);
            }
        }

        if (c == '\n')
            line_number++;

        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

int not_reserved(char * word) {
    return binsearch(word, reserved, NKEYS) < 0;
}

int not_article(char * word) {
    return binsearch(word, articles, 3) < 0;
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

int binsearch(char * word, char ** reserved, int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, reserved[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else return mid;
    }
    return -1;
}

