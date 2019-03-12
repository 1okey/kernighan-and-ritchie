#include <string.h>

void _strncpy(char * s, const char * t, int n)
{
	while(n-- && (*s++ = *t++));
}

void _strncat(char * s, const char * t, int n)
{
	while(*s++);
	_strncpy(s,t,n);
}

int _strncmp(const char * s, const char * t, int n)
{
	for(; *s == *t && n; s++, t++, n--){
		if(*s == 0)
			return 0;
	}
	return *s - *t;
}
