#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAX_OCCURENCES 10

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char * strdup(char *);

struct tnode {
    char *word;
    int count;
    int * occurences;
    struct tnode * left;
    struct tnode * right;
};

int main(int argc, char ** argv) {
    struct tnode * root;
    int limit = MAXWORD;

    if(argc == 2)
        limit = atoi(argv[1]);

    char word[limit];
    root = NULL;

    while (getword(word, limit) != EOF)
        if (isalpha(word[0]))
            root = addtree(root,word);

    treeprint(root);
    return 0;
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        p->occurences = (int*) malloc(sizeof(int) * MAX_OCCURENCES);
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
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
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

struct tnode * talloc(void) {
    return (struct tnode*) malloc(sizeof(struct tnode));
}

char * strdup(char *s) {
    char * p;
    p = (char*) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p,s);
    return p;
}

int getword(char * word, int lim){
    int c;
    char *w = word;

    while(isspace(c = getch()));

    if(c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        if (c = '\n') line_number++;
        else if (c == '"')
            while((c = getch() != '"'));
        else if(c == '#') {
            while((c = getch() != '\n'));
            if (c = '\n') line_number++;
        }
        else if(c == '_')
            while((c = getch() != ' '));
        else if(c == '/') {
            char next = getch();
            if(next == '/'){
                while((c = getchar()) != '\n');
                if (c = '\n') line_number++;
            } else if(next == '*'){
                while((next = c) && (c = getchar())){
                    if (c = '\n') line_number++;
                    if(next == '*' && c == '/') break;
                }
            } else {
                ungetch(next);
                ungetch(c);
            }
        }

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