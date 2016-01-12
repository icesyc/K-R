/**
 * 标准库函数 int fseek(FILE *fp, long offset, int origin)类似于函数lseek，所不同的是该函数中的fp是一个文件指针而不是
 * 一个文件描述符，且返回值是一个int类型的状态而非位置值。编写函数fseek，并确保该函数与库中其它函数使用的缓冲能够协同工作。
 * 
 */

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

struct _flags {
	unsigned int _READ : 1;
	unsigned int _WRITE : 1;
	unsigned int _UNBUF : 1;
	unsigned int _EOF : 1;
	unsigned int _ERR : 1;
};

typedef struct _iobuf {
	int cnt;					/* character left */
	char *ptr;					/* next character position */
	char *base;					/* location of buffer */
	struct _flags flags;		/* mode of file access */
	int fd;						/* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, { 1, 0, 0, 0, 0 }, 0 },
	{ 0, (char *) 0, (char *) 0, { 0, 1, 0, 0, 0 }, 1 },
	{ 0, (char *) 0, (char *) 0, { 0, 1, 1, 0, 0 }, 2 }
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flags._EOF) != 0)
#define ferror(p) (((p)->flags._ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
					? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
					? *(p)->ptr++ = (x) : _flushbuf((x), p))
					
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout) 

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define PERMS 0666

FILE *fopen(char *fname, char *mode);
int fclose(FILE *fp);
int fflush(FILE *fp);
int fseek(FILE *fp, long offset, int origin);

int main(int argc, char *argv[]){
	FILE *fp = fopen("8-2.c", "r");
	fseek(fp, -10, 2);
	char buff[BUFSIZ];
	unsigned char c;
	int i = 0;
	while(i < 10){
		buff[i++] = getc(fp);
	}
	write(1, buff, 10);
	return 0;
}
FILE *fopen(char *fname, char *mode){
	FILE *fp;
	if(*mode != 'r' && *mode  != 'w' && *mode != 'a'){
		return NULL;
	}
	for(fp = _iob; fp < _iob + OPEN_MAX; fp++){
		if(fp->flags._READ == 0 || fp->flags._WRITE == 0){
			break;
		}
	}
	//no available fp
	if(fp >= _iob + OPEN_MAX){
		return NULL;
	}

	fp->flags._READ = 0;
	fp->flags._WRITE = 0;
	fp->flags._UNBUF = 0;
	fp->flags._EOF = 0;
	fp->flags._ERR = 0;
	if(*mode == 'r'){
		fp->fd = open(fname, O_RDONLY, 0);
		fp->flags._READ = 1;
	}else if(*mode == 'w'){
		fp->fd = creat(fname, PERMS);
		fp->flags._WRITE = 1;
	}else{
		fp->fd = open(fname, O_WRONLY, 0);
		if(fp->fd == -1){
			fp->fd = creat(fname, PERMS);
		}
		lseek(fp->fd, 0, 2);
		fp->flags._WRITE = 1;
	}
	if(fp->fd == -1){
		return  NULL;
	}
	fp->cnt = 0;
	fp->ptr = NULL;
	fp->base = NULL;
	return fp;
}
int _fillbuf(FILE *fp){
	int buffsize = fp->flags._UNBUF ? 1 : BUFSIZ;
	if(fp->base == NULL){
		fp->base = (char *)malloc(buffsize);
		if(fp->base == NULL){
			return EOF;
		}
	}
	fp->cnt = read(fp->fd, fp->base, buffsize);
	if(fp->cnt == -1){
		fp->cnt = 0;
		return EOF;
	}
	fp->ptr = fp->base;
	if(--fp->cnt < 0){
		if(fp->cnt == -1){
			fp->flags._EOF = 1;
		}else{
			fp->flags._ERR = 1;
		}
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}
int _flushbuf(int c, FILE *fp){
	if(!fp->flags._WRITE){
		return EOF;
	}
	int buffsize = fp->flags._UNBUF ? 1 : BUFSIZ;
	if(fp->base == NULL){
		fp->base = (char *)malloc(buffsize);
		if(fp->base == NULL){
			fp->flags._ERR = 1;
			return EOF;
		}
	}else{
		int buffed = fp->ptr - fp->base;
		if(write(fp->fd, fp->base, buffed) != buffed){
			fp->flags._ERR = 1;
			return EOF;
		}
	}
	fp->cnt = buffsize - 1;
	fp->ptr = fp->base;
	*fp->ptr++ = c;
	return c;
}
int fclose(FILE *fp){
	if(fflush(fp) == -1){
		return EOF;
	}
	free(fp->base);
	fp->ptr = NULL;
	fp->base = NULL;
	fp->cnt = 0;
	fp->flags._READ = 0;
	fp->flags._WRITE = 0;
	fp->flags._UNBUF = 0;
	fp->flags._EOF = 0;
	fp->flags._ERR = 0;
	return close(fp->fd);
}
int fflush(FILE *fp){
	int buffed = fp->ptr - fp->base;
	_flushbuf(0, fp);
	fp->ptr = fp->base;
	fp->cnt = fp->flags._UNBUF ? 1 : BUFSIZ;
	return 0;
}
int fseek(FILE *fp, long offset, int origin){
	int pos, nc;
	if(fp->flags._READ){
		if(origin == 1){
			offset -= fp->cnt;
		}
		fp->cnt = 0;
	}else{
		if(origin == 1){
			int nc = fp->ptr - fp->base;
			if(write(fp->fd, fp->ptr, nc) != nc){
				return EOF;
			}
		}
		fp->cnt = BUFSIZ;
	}
	pos = lseek(fp->fd, offset, origin);
	if(pos < 0){
		return EOF;
	}
	return 0;
}


