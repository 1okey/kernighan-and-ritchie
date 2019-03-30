#include <stdio.h>
#include <stdlib.h>
#define TAB 0x09
#define IDENTATION 4

int main(int argc, char ** argv){
    int identation = IDENTATION;
    if(argc == 2){
        identation = atoi(*(argv + 1));
    }
    char c; int idnt_counter = 0;
    while((c = getchar()) != EOF){
        if(c == ' '){
            ++idnt_counter;
            if(idnt_counter == identation)
                printf("%c", TAB);
        } else {
            idnt_counter = 0;
            printf("%c",c);
        }
    }
}
