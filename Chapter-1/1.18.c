#include <stdio.h>

#define MAXLEN 100

int is_delimiter(char ch) {
    return ch == ' ' || ch == '\t';
}

int main() {
    char ch;
    char line[MAXLEN];
    char dest[MAXLEN]; 

    int index = 0;
    while((ch = getchar()) != EOF) {
        if(ch == '\n') 
            continue;
        line[index++] = ch;
    }
    line[index--] = 0;

    while(is_delimiter(line[index]) && --index);
    line[++index] = 0;
    printf("%s", line);
    return 0;
}