#include <stdio.h>

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
    char c;
    while((c = getchar()) != EOF){
        if(c == '\t'){
            c = ' ';
            printf("%*c", identation, c);
        } else 
            printf("%c",c);
    }
}