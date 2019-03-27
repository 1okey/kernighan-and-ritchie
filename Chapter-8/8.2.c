#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

#define BUFSIZE	1024
#define PERMITIONS 0666
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;
    char* ptr;
    char* base;
    struct {
        unsigned int read  : 1;
        unsigned int write : 1;
        unsigned int unbuf : 1;
        unsigned int eof   : 1;
        unsigned int err   : 1;
    } flag;
    int fd;
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE _iob[OPEN_MAX] = {
	{ 0, NULL, NULL, { !0, 0, 0, 0, 0 },  0 },
	{ 0, NULL, NULL, { 0, !0, 0, 0, 0 },  1 },
	{ 0, NULL, NULL, { 0, !0, !0, 0, 0 }, 2 }
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE*);

#define feof(p) (((p)->flag * _EOF) != 0)
#define ferror(p) (((p)->flag * _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0) \
    ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x, p) (--(p)->cnt >= 0) \
    ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE* fopen(char * name, char * mode){
    int fd;
    FILE* fp;

    if(*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!fp->flag.read && !fp->flag.write)
            break;
    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if(*mode == 'w')
        fd = creat(name, PERMITIONS);
    else if (*mode = 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMITIONS);
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1);
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag.read = fp->flag.write = fp->flag.eof = fp->flag.err = fp->flag.unbuf = 0; 
    if ((*mode = 'r'))
        fp->flag.read = 1;
    else
        fp->flag.write = 1;
    return fp;
}

int _fillbuf(FILE * fp) {
    int bufsize;

	if (!fp->flag.read || fp->flag.eof || fp->flag.err)
        return EOF;

    bufsize = fp->flag.unbuf ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = (char*) malloc(bufsize)) == NULL)
            return EOF;
    
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if(fp->cnt == -1)
            fp->flag.eof = 1;
        else
            fp->flag.err = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

