#include <stdio.h>

#define SYMBOL_AMMOUNT 93
#define CHAR_FROM 33
#define SHIFT 33
#define CHAR_TO 126

static char table[SYMBOL_AMMOUNT] = {};

// SHIFT is simply a shift from start of ASCI table to start of actual characters
char index_to_char(int index) { 
    return index + SHIFT; 
}

int char_to_index(char character) { 
    return character - SHIFT;
}

int main(){
    char c;
    for(unsigned i = 0; i < SYMBOL_AMMOUNT; table[i] = 0, ++i);
    while ((c = getchar()) != EOF) {
        if(c == ' ' || c == '\n' || c == '\t') 
            continue;
            // if its a character, than increment count of it
        if(CHAR_FROM < c && c < CHAR_TO)
            table[char_to_index(c)]++;
    }

    for (unsigned i = 0; i < SYMBOL_AMMOUNT; i++) {
        if(table[i] > 0){
            printf("\n%c ", index_to_char(i));
            for(int j = 0; j < table[i]; j++)
                printf("-");
        }
    }
    return 0;
}