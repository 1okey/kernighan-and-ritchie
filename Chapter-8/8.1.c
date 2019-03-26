#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE	1024

void filecopy(const int ifd, const int ofd);

int main(int argc, char ** argv) {
    int fd;
    char * prog = argv[0];

    if (argc == 1)
        filecopy(0, 1);
    else {
        while(--argc > 0) {
            if ((fd == open(*++argv, O_RDONLY, 0)) == -1) {
                dprintf(2, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fd, 1);
                close(fd);
            }
        }
    }

    exit(0);
}

void filecopy(int ifd, int ofd) {
    char buffer[BUFSIZ];
    int n;
    while((n = read(ifd, buffer, BUFSIZ)) > 0)
        write(ofd, buffer, n);
}