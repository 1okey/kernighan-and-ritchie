#include <string.h>

void strncpy(char * s, const char * t, int n)
{
	while(n-- && (*s++ = *t++));
}

void strncat(char * s, const char * t, int n)
{
	while(*s++);
	strncpy(s,t,n);
}

int strncmp(const char * s, const char * t, int n)
{
	for(; *s == *t && n; s++, t++, n--){
		if(*s == 0)
			return 0;
	}
	return *s - *t;
}
