#include <stdarg.h>

void minprintf(char *fmt, ...){
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    char cval;
    void* ptrval;

    va_start(ap,fmt);
    for ( p = fmt; *p; ++p) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, float);
                printf("%f", ival);
                break;
            case 'p':
                ptrval = va_arg(ap, void*);
                printf("%p", ptrval);
                break;
            case 'x':
                cval = va_arg(ap, char);
                printf("%x", cval);
                break;
            case 's':
                for (sval = va_arg(ap, char*); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*sval);
                break;
        }
    }
    va_end(ap);
}