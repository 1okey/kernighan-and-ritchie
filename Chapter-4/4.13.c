#include <string.h>

void reverse(char s[]){
  if(strlen(s) < 2)
    return;

  int l = 0;
  char t = s[0];
  s[0] = s[l = strlen(s) - 1];
  s[l] = 0;
  reverse(s + 1);
  s[l] = t;
}
