#include <stdio.h>
#include <string.h>

#define MAXLINE 120
int main(int argc, char ** argv) {
    if (argc < 3)
        fprintf(stderr, "You must provide 2 arguments");
   
    FILE * first = fopen(argv[1], "r");
    FILE * second = fopen(argv[2], "r");
    char f_line[MAXLINE], s_line[MAXLINE];
    unsigned i = 1;
    while(fgets(f_line, 120, first) != NULL && fgets(s_line, MAXLINE, second) != NULL) {
        if(strcmp(f_line, s_line) != 0) {
            printf("difference in line #%d\n%s%s", i, f_line, s_line);
            break;
        }
        ++i;
    }

    fclose(first);
    fclose(second);
    return 0;
}