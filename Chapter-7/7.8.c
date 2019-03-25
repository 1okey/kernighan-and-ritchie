#include <stdio.h>
#include <string.h>

static char separator[80] = "==============================================================================\n";

int main(int argc, char ** argv) {
    if(argc == 1)
        fprintf(stderr, "No files provided\n");

    int MAXLINE = 80;
    FILE* current_file = NULL;
    char file_name[MAXLINE], line[MAXLINE];
    unsigned i = 1;
    argv++;
    while(*argv){
        char * file_name = *argv++;
        int padding = (MAXLINE - strlen(file_name)) / 2;
        current_file = fopen(file_name, "r");
        fprintf(stdout, "%*c%s\n%s", padding, ' ', file_name, separator);
        while(fgets(line, MAXLINE, current_file) != NULL)
            fprintf(stdout, line);
        fprintf(stdout, "\n%s%*c%d\n\n", separator, 75, ' ', i++);
        fclose(current_file);
    }
}