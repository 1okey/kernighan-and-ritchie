#include <stdarg.h>
#include <stdio.h>

void minscanf(char *fmt, ...){
    va_list ap;
    char *p, *sval;
    int * ival;
    double * dval;
    char * cval;
    void * ptrval;

    va_start(ap,fmt);
    for ( p = fmt; *p; ++p) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'i':
            case 'd':
                ival = va_arg(ap, int*);
                scanf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double*);
                scanf("%f", dval);
                break;
            case 'x':
                cval = va_arg(ap, char*);
                scanf("%x", cval);
                break;
            case 's':
                for (sval = va_arg(ap, char*); *sval; sval++)
                    scanf("%c", sval);
                break;
            default:
                *sval = getchar();
                break;
        }
    }
    va_end(ap);
}

int main() {
    char i;
    minscanf("%d", &i);
    printf("entered number %c", i);
}