#include <stdio.h>
#define IDENTATION 4
int main(int argc, char ** argv){
    int identation = IDENTATION;
    if(argc == 2){
        identation = atoi(*(argv + 1));
    }
    char c;
    while((c = getchar()) != EOF){
        if(c == '\t'){
            printf("%*c", identation, ' ');
        } else 
            printf("%c",c);
    }
}