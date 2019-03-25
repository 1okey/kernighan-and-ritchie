#include <stdio.h>
#include <ctype.h>

#define MAXLEN 160

int main() {
    char c;
    char word[MAXLEN];
    while((c = getchar()) != EOF){
        if(!isalnum(c)) {
            printf(" %x ", c);
        } else {
            unsigned i = 0;
            while(isalnum(c)){
                word[i++] = c;
                c = getchar();
            }
            printf("%.*s\n", MAXLEN, word);
        }
    }
}