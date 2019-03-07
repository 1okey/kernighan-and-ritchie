#include <math.h>

double atof(char s[])
{
	double val = 0.0;
	double power = 1.0;
	int i = 0;
	int sign = 0;
	int exp_sign = 0;
	int exp = 0;
	// trim leading spaces
	for(; isspace(s[i]); ++i);

	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		++i;
	for (; isdigit(s[i]); ++i)
		val = 10 * val + (s[i] - '0');
	if (s[i] == '.')
		++i;
	for (; isdigit(s[i]); ++i){
		val = 10 * val + (s[i] - '0');
		power *= 10;
	}
	
	exp_sign = (s[i++] == '-') ? -1 : 1;
	if (s[i] == 'E' || s[i] == 'e')
		++i;
	for(; isdigit(s[i]); ++i)
		exp = 10 * exp + (s[i] - '0');

	power *= pow(10, exp_sign == 1 ? 1/exp : exp);
	return sign * val / power;
}
