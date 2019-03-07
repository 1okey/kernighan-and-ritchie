#include <ctype.h>

int getch(void);
void ungetch(int);

int getfloat(double* pn)
{
 	int c;
 	while (isspace(c = getch()));
	if (!isdigit(c) && c != EOF && c != '+' && c != '-'){
		ungetch(c);
		return 0;
  	}
	int sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-'){
		if(!isdigit(c = getch())){
			ungetch(c);
			return 0;
		}
	}

	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	
	if(c == '.')
		c = getch();

	double power = 1.0;
	for(; isdigit(c); c = getch()){
		*pn = 10 * *pn + (c - '0');
		power *= 10;
	}
	(*pn *= sign) /= power;
	if(c != EOF)
		ungetch(c);
	return c;
}
