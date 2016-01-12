/**
 * 修改fsize程序，打印结点项中包含的其它信息。
 * 注：由于非unix系统上已经无法使用read系统调用打开目录，原书的例子已经失效
 * 改成使用系统原生的opendir, readdir, closedir
 * 需要包含sys/dir.h
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/dir.h>

#define NAME_MAX 256
#define MAX_PATH 256

void dirwalk(char *name, void (*fn)(char *name));
void fsize(char *name);

int main(int argc, char **argv){
	if(argc == 1){
		fsize((char *)".");	
	}else{
		while(--argc > 0){
			fsize(*++argv);
		}
	}
}
void fsize(char *name){
	struct stat stbuf;

	if(stat(name, &stbuf) == -1){
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if((stbuf.st_mode & S_IFMT) == S_IFDIR){
		dirwalk(name, fsize);
	}
	printf("%5llu %6o %3u %20lld %s\n", stbuf.st_ino, stbuf.st_mode, stbuf.st_nlink, stbuf.st_size, name);
}	
void dirwalk(char *dir, void (*fn)(char *)){
	direct *dp;
	DIR *dfd;
	char name[MAX_PATH];
	if((dfd = opendir(dir)) == NULL){
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
	}
	while((dp = readdir(dfd)) != NULL){
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0){
			continue;
		}
		if(strlen(dir)+strlen(dp->d_name) + 2 > sizeof(name)){
			fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
		}else{
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fn)(name);
		}
	}
	closedir(dfd);
}
