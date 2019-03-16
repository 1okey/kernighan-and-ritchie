#include <ctype.h>
#include <stdio.h>

void reverse (char s[]){
    int	c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itob(int n , char s[], int base){
    unsigned i = 0;
    while(n > 0){
        s[i++] = '0' + (n % base) ;
        n /= base;
    }
    s[i] = 0;
    reverse(s);
}

int main(){
    char number[16];
    itob(32, number, 16);
    printf("%s == 20", number);
}



