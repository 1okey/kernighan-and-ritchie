#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// this func converts char to hex number
int ctoh(char c){
    char lc = tolower(c);
    if('a' <= lc && lc <= 'f') 
        return c - 'a' + 10;
    else 
        return c - '0';
}

int htoi(char hex[]){
    int len = strlen(hex);
    int acc = 0, i = 0;
    while(tolower(hex[--len]) != 'x')
        // converting hex to dec and multiplying by base
        acc += ctoh(hex[len]) * pow(16,i++);
    return acc;
}

int main() {
    printf("%s - %d\n", "0x21", htoi("0x21"));
    printf("%s - %d\n", "0xf", htoi("0xf"));
    printf("%s - %d\n", "0xaaf", htoi("0xaaf"));
}