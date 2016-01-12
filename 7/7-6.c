/**
 * 编写一个程序，比较两个文件并打印它们第一个不相同的行。
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000
void compare(char *f1, char *f2);
int main(int argc, char *argv[]){
	if(argc < 3){
		printf("usage: %s file1 file2\n", *argv);
		exit(1);
	}
	char *f1 = argv[1];
	char *f2 = argv[2];
	compare(f1, f2);
	return 0;
}

void compare(char *f1, char *f2){
	FILE *fp1 = fopen(f1, "r");
	FILE *fp2 = fopen(f2, "r");
	if(fp1 == NULL || fp2 == NULL){
		printf("can not open file %s\n", fp1 == NULL ? f1 : f2);
	}
	char line1[MAXLINE], line2[MAXLINE];
	while(fgets(line1, MAXLINE, fp1) != NULL && fgets(line2, MAXLINE, fp2) != NULL){
		if(strcmp(line1, line2) != 0){
			printf("line1=%s", line1);
			printf("line2=%s", line2);
			break;
		}	
	}
}
