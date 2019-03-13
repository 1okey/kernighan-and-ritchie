#include <stdio.h>

int main()
{
	char c, l;
	while((c = getchar()) != EOF){
		if(c == '/'){
			if((l = getchar()) == '/'){
				while((c = getchar()) != '\n');
				continue;
			}
			if((l = getchar()) == '*'){
				c = getchar();
				while((l = c) != '*' && (c = getchar()) != '/');
				continue;
			}
			putchar(c);
			continue;
		}
		putchar(c);
	}
}
