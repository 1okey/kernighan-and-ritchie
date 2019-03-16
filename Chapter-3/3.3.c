#include <ctype.h>
#include <stdio.h>
#define BUFFER_SIZE		100
#define NUMBER_TEST_STRINGS	4

void expand(char s1[], char s2[]){
    unsigned i,j;
    for(i = j = 0; s1[i]; ++i){
        if(isalpha(s1[i]) && s1[i + 1] == '-' && isalpha(s1[i + 2])){
            for(char c = s1[i]; c <= s1[i + 2]; c++) s2[j++] = c;
            i+=2;
        }
        else if(isdigit(s1[i]) && s1[i + 1] == '-' && isdigit(s1[i + 2])){
            for(char c = s1[i]; c <= s1[i + 2]; c++) s2[j++] = c;
            i+= 2;
        }
        else s2[j++] = s1[i];
    }
    s2[j] = 0;
}

char *TEST_STRINGS[NUMBER_TEST_STRINGS] = {
    "a-b-c",
    "a-z0-9",
    "-a-z",
    "A-Z-",
};

int main (){
    int	i;
    char	s[BUFFER_SIZE];
    for (i = 0; i < NUMBER_TEST_STRINGS; i++) {
        expand(TEST_STRINGS[i], s);
        printf("\"%s\" => \"%s\"\n", TEST_STRINGS[i], s);
    }
    return 0;
}

