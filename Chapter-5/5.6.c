#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int strindex(char * s, char * t){
    int i,j,k;
    for(i = 0; s[i] != '\0'; i++)
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            if(k > 0 && t[k] == '\0' && s[i] == '\0')
                return i;
    return -1;
}

double atof(char * s)
{
    double val = 0.0;
    double power = 1.0;
    int sign = 0;
    int exp_sign = 0;
    int exp = 0;
    while(isspace(*s)) ++s;

    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-') ++s;

    while(isdigit(*s)) val = 10 * val + (*s++ - '0');

    if (*s == '.') ++s;

    while(isdigit(*s)){
        val = 10 * val + (*s++ - '0');
        power *= 10;
    }

    if (*s == 'E' || *s == 'e') ++s;

    exp_sign = (*s++ == '-') ? -1 : 1;

    while(isdigit(*s)) exp = 10 * exp + (*s++ - '0');

    power *= pow(10, exp_sign == 1 ? 1/exp : exp);
    return sign * val / power;
}

void itoa(int n, char * s){
    if(n / 10)
        itoa(n / 10, s);
    else
        s[0] = 0;

    unsigned long len = strlen(s);
    s[len] = '0' + n % 10;
    s[len + 1] = 0;
}

void reverse(char * s){
    if(strlen(s) < 2)
        return;

    unsigned long l = 0;
    char t = *s;
    *s = s[l = strlen(s) - 1];
    s[l] = 0;
    reverse(s + 1);
    s[l] = t;
}

int c_getline(char * s, int lim){
    int c, i = 0;

    for(; i < lim - 1 && (c = getchar()) != EOF; ++i){
        if(c == '\n') break;
        *s++ = (char)c;
    }

    if (c == '\n') *s++ = (char)c;
    *s = 0;
    return i;
}

int main(){
    char str[] = "abcde";
    int num = 123567;
    char num_str[8];
    char float_str[] = "123.345-e3";
    char line[8];
    reverse(str);
    itoa(num, num_str);
    double float_num = atof(float_str);
    c_getline(line,8);
    printf("reverse: %s\n"
           "itoa: %s\n"
           "atof: %f\n"
           "getline: %s\n", str, num_str, float_num, line);
    return 0;
}

