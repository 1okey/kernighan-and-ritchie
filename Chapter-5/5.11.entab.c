#include <stdio.h>
#include <stdlib.h>
#define TAB 0x09

int main(int argc, char ** argv){
    if(argc >= 3){
        printf("too many arguments");
        return 1;
    }
    if(argc == 1){
        printf("not enough arguments");
        return 1;
    }

    int identation = atoi(*(argv + 1));
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
