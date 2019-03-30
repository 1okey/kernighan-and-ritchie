#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_LINES	10
#define MAXLINES	5000

char	*lineptr[MAXLINES];

int	readlines (char *lineptr[], int maxlines);
void writelines (char *lineptr[], int nlines);

int main (int argc, char *argv[]){
    int	n, nlines;

    n = NUMBER_LINES;
    if (argc == 2 && *argv[1]++ == '-' && isdigit(*argv[1]))
        n = atoi(argv[1]);
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (n > nlines)
            n = nlines;
        writelines(lineptr + (nlines - n), n);
        return 0;
    } else {
        printf("Error: Input too big!\n");
        return 1;
    }
}

#define MAXLEN	1000

int cgetline (char line[], int limit);
char *alloc (int n);

int readlines (char *lineptr[], int maxlines){
    int	len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = cgetline(line, MAXLEN)) > 0)

        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }

    return nlines;
}

void writelines (char *lineptr[], int nlines){
    int	i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int cgetline (char line[], int limit){
    int i, c;
    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

#define ALLOCSIZE	100000
char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

char *alloc (int n){
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else return NULL;
}
