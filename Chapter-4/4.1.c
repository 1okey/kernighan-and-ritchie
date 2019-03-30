#include <stdio.h>

int strindex(char s[], char t[]){
    int i = 0, j = -1, start = -1, k = 0;
    for(; s[i] != '\0'; i++) {
        // this loop will start inly if starting chars are the same
        if(s[i] == t[0]) {
            for ( j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k);
            // only if we have match, than change start of last match index
            if(t[k] == 0)
                start = i;
        }
    }
    return start;
}

int main(){
    printf("%d == 4\n", strindex("asdaasdas","asd"));
    printf("%d == 0\n", strindex("asdas","asd"));
    printf("%d == 3\n", strindex("asdasd","asd"));
    printf("%d == -1\n", strindex("adads","asd"));
    return 0;
}