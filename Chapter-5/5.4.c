#include <string.h>

int strend(char * s, char * t)
{
	unsigned s_l = strlen(s);
	unsigned t_l = strlen(t);
	for(unsigned i = s_l - t_l, j = 0; i < s_l; i++ ,j++){
		if(s[i] != t[j])
			return 0;
	} 
	return 1;
}
