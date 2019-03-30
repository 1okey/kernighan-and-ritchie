#include <stdio.h>

int bitcount(unsigned x);

int main(){
    printf("%d", bitcount(12));
    return 0;
}

int bitcount(unsigned x)
{
  int b;
  // x - 1 will flip rightmost bit and 
  // x &= x - 1 checks if that bit is 1
  for (b = 0; x != 0; x &= x-1) ++b;
  return b;
}