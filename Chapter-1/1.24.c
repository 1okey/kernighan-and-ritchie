#include <stdio.h>

int is_pair_symbol(char c){
    return c == '"' || c == '[' || c == '{' || c == '(';
}

char get_pair_symbol(char c){
    switch(c){
        case '"': return '"';
        case '[': return ']';
        case '{': return '}';
        case '(': return ')';
    }
}

int main()
{
    char c, l;
    int line = 1;
    while((c = getchar()) != EOF){
        if(is_pair_symbol(c)){
            char pair_symbol = get_pair_symbol(c);
            while((c = getchar()) != pair_symbol){
                if(c == '\n') {
                    printf("Couldn't find closing %c, in line %d\n", pair_symbol, line++);
                    break;
                }
            }
        } else if(c == '/'){
            l = getchar();
            if(l == '/'){
                while((c = getchar()) != '\n');
                line++;
                continue;
            } else if(l == '*'){
                while((l = c) && (c = getchar()))
                    if(l == '\n') line++;
                    if(l == '*' && c == '/') break;
                continue;
            };
            continue;
        }
        if(c == '\n') line++;
    }
}


