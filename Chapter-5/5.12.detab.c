#include <stdio.h>
#include <stdlib.h>

#define TAB 0x09
#define DEF_INDENTATION 4
#define DEF_FREQUENCY 10
#define DEF_FROM_POS  10

void enchar(char c);
void detab(int from_pos, int frequency);
static int indentation = DEF_INDENTATION;

int main(int argc, char ** argv) {
    int from_pos  = DEF_FROM_POS;
    int frequency = DEF_FREQUENCY;

    if (argc > 1) {
        from_pos = (*(++argv))[1] - '0';
        if(argc == 3)
            frequency = (*(++argv))[1] - '0';
    } 
    printf("%d, %d\n", from_pos, frequency);
    detab(from_pos, frequency);
}

void enchar(char c) {
    if(c == '\t'){
        printf("%*c", indentation, ' ');
    } else {
        putchar(c);
    }
}

void detab(int from_pos, int frequency){
    char c;
    int column = 1, period = 1;
    while((c = getchar()) != EOF){
        while(column >= from_pos && c != EOF && c != '\n'){
            if (period % frequency == 0) {
                period = 0;
                printf("%*c", DEF_INDENTATION, ' ');
            }
            enchar(c);
            c = getchar();
            ++period;
            ++column;
        }

        enchar(c);
        column = (c == '\n') ? 1 : ++column;
    }
}