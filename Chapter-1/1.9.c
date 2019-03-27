#include <stdio.h>

int main(){
    char c;
    while((c = getchar()) != EOF){
		if(c == ' '){ 
			putchar(c);
			// skip all further spaces
	   		while((c = getchar()) == ' ');
		}
		putchar(c);
	}
    return 0;
}
