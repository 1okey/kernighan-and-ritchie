#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 3
#define MAXLEN	1000
#define ALLOCSIZE	100000

char *lineptr[MAXLINES];
char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

int _getline (char line[], int limit);
char *alloc (int n);
int _readlintes(char* lineptr[], int nlines);
void _writelines(char* lineptr[], int nlines);
void _qsort(void *lineptr[], int left, int right, int (*comp)(void*,void*));
int _numcmp(char*, char*);
int _strcmp(char *s1, char *s2);
void _swap(void * v[], int i, int j);

int reverse = 0;
int case_sensitive = 1;
int directory = 0;

int main(int argc, char* argv[])
{
    int nlines;
    int numeric = 0;

    if (argc > 1){
        char * flags = argv[1];
        while(*flags){
            switch(*flags++){
                case 'n': numeric = 1;          break;
                case 'd': directory = 1;        break;
                case 'f': case_sensitive = 0;   break;
                case 'r': reverse = 1;          break;
            }
        }
    }

    if ((nlines = _readlines(lineptr, MAXLINES)) >= 0) {
        _qsort((void**) lineptr, 0, nlines - 1, (int (*)(void*, void*))(numeric ? _numcmp : _strcmp));
        _writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Input too big to sort\n");
        return 1;
    }
}

void _qsort(void *v[], int left, int right, int(*comp)(void*, void*)) {
    int i, last;
    if(left >= right)
        return;

    _swap(v, left, (left + right) / 2);
    last = left;
    for ( i = left + 1; i <= right; ++i){
        if(reverse * (*comp)(v[i], v[left]) < 0)
            _swap(v, ++last, i);
    }
    _swap(v, left, last);
    _qsort(v, left, last -1, comp);
    _qsort(v, last + 1, right, comp);
}

int _strcmp(char *s1, char *s2) {
    char a,b;
    do {
        if(directory){
            while (!isalnum(*s1) && !isspace(*s1) && *s1 != '\0') a = *s1++;
            while (!isalnum(*s2) && !isspace(*s2) && *s2 != '\0') b = *s2++;
        }
        else {
            a = *s1++;
            b = *s2++;
        }

        if(case_sensitive){
            a |= 0x40;
            b |= 0x40;
        }

    } while(a == b && a != '\0');


    return a - b;
}

int _numcmp(char *s1, char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else return 0;
}

void _swap(void * v[], int i, int j) {
    void* tmp;
    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

int _readlines (char *lineptr[], int maxlines){
    int	len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)

        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }

    return nlines;
}

void _writelines (char *lineptr[], int nlines){
    int	i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int _getline (char line[], int limit){
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

char *alloc (int n){
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else return NULL;
}
