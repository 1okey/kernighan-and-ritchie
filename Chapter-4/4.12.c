#include <string.h>

void itoa(int n, char s[])
{
	if(n / 10){
		itoa(n / 10, s);
	} 
	else {
		s[0] = 0;
	}
	int len = strlen(s); 
	s[len] = '0' + n % 10;
	s[len + 1] = 0;
}
