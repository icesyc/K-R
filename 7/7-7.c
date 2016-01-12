/**
 * 修改第5章的模式查找程序，使它从一个命名文件的集合中读取输入（有文件名参数时），如果没有文件名参数，则从标准输入中
 * 读取输入。当发现一个匹配行时，是否应该将相应的文件名打印出来？
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000
void fpat(FILE *fp, char *fname, char *pattern, int except, int number);
int main(int argc, char *argv[]){
	char *arg;
	char pattern[MAXLINE];
	int number, except;
	FILE *fp;
	while(--argc > 0 && (*++argv)[0] == '-'){
		arg = *argv;
		while(*++arg != '\0'){
			switch (*arg) {
				case 'n':
				number = 1;
				break;
				case 'x':
				except = 1;
				break;
			}
		}
	}
	if(argc > 0){
		strcpy(pattern, *argv);
	}else{
		printf("Usage: find [-xn] pattern [file...]\n");
		exit(1);
	}
	if(argc == 1){
		fpat(stdin, "", pattern, except, number);
	}else{
		while(--argc > 0){
			fp = fopen(*++argv, "r");
			if(fp == NULL){
				fprintf(stderr, "can not open file %s\n", *argv);
				exit(1);
			}else{
				fpat(fp, *argv, pattern, except, number);
				fclose(fp);
			}
		}
	}
	return 0;
}
void fpat(FILE *fp, char *fname, char *pattern, int except, int number){
	char line[MAXLINE];
	int found = 0;
	int lines = 0;
	while(fgets(line, MAXLINE, fp) != NULL){
		lines++;
		found = strstr(line, pattern) != NULL;
		if(found != except){
			if(*fname){
				printf("%s - ", fname);
			}
			if(number){
				printf("%d: ", lines);
			}
			printf("%s", line);
		}
	}
}
