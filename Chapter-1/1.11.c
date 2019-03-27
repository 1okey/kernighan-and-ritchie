#include <stdio.h>
#define OUT  0
#define IN  1

int main() {

    int c, nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    while((c = getchar()) != EOF)
    {
        // Backslash will cover next char next to it, which leads to incorrect word count
        ++nc;
        if(c == '\n')
            ++nl;
        if(c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        // All kinds of separators will count as words, such as ' / - etc.
        // Therefore we should check if input char is stands in range between a-zA-Z 
        else if(state == OUT)
        {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
    return 0;
}