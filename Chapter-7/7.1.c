#include <ctype.h>
#include <stdio.h>

int main(){
    char c;
    while((c = getchar()) != EOF) {
        putchar(islower(c) ? toupper(c) : tolower(c));
    }
    return 0;
}