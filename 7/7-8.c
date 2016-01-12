/**
 * 编写一个程序，以打印一个文件集合，每个文件从新的一页开始打印，并且打印每个文件相应的标题和页数。
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#define MAXLINE 1000
#define MAXPAGE 30
#define PAD_BOTTOM 2
void printfile(FILE *fp, char *fname);

int main(int argc, char *argv[]){
	char *arg;
	FILE *fp;
	while(--argc > 0){
		arg = *++argv;
		fp = fopen(arg, "r");
		if(fp ==  NULL){
			fprintf(stderr, "can not open file: %s\n", arg);
			continue;
		}
		printfile(fp, arg);
		fclose(fp);

	}
	return 0;
}
int printhead(char *fname, int pageno){
	printf("=====================================\n");
	printf("%s\tpage %d\n", fname, pageno);
	printf("=====================================\n");
	return 3;
}
void printfoot(int pageno){
	printf("\n");
	printf("############## p%d ###################\n", pageno);
}
void printfile(FILE *fp, char *fname){
	char line[MAXLINE];
	int pageno = 1;
	int lineno = printhead(fname, pageno);
	while(fgets(line, MAXLINE, fp) != NULL){
		if(lineno >= MAXPAGE - PAD_BOTTOM){
			printfoot(pageno);
			lineno = printhead(fname, ++pageno);
		}
		printf("%s", line);
		if(line[strlen(line)-1] != '\n'){
			printf("\n");
		}
		lineno++;
	}
	while(lineno++ < MAXPAGE - PAD_BOTTOM){
		printf("\n");
	}
	printfoot(pageno);

}