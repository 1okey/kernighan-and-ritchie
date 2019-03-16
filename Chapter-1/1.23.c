#include <stdio.h>

int main()
{
    char c, l;
    while((c = getchar()) != EOF){
        if(c == '/'){
            l = getchar();
            if(l == '/'){
                while((c = getchar()) != '\n');
                continue;
            } else if(l == '*'){
                while((l = c) && (c = getchar()))
                    if(l == '*' && c == '/') break;
                continue;
            };
            putchar(c);
            putchar(l);
            continue;
        }
        putchar(c);
    }
}
