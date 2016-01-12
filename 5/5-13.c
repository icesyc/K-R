/**
 * 编写程序tail,将其输入中的最后n行打印出来.默认情况下,n的值为10,但可通过一个可选参数改变n的值,因此,命令tail -n
 * 将打印其输入的最后n行.无论输入或n的值是否合理,该程序都应该能正常运行.编写的程序要充分地利用存储空间;输入行的存储
 * 方式应该同5.6节中排序程序的存储方式一样,而不采用固定长度的二维数组.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1000
#define MAXLINE 100
void tail(int n);
int getln(char *s, int max);

int main(int argc, char *argv[]){
	char *arg;
	int n = 10;
	if(argc == 2){
		arg = *++argv;
		if(*arg == '-'){
			int l = atoi(++arg);	
			if(l > 0){
				n = l;
			}
		}	
	}
	tail(n);
}
void tail(int n){
	char line[MAXLEN];
	char *p[MAXLINE];
	int len;
	int i = 0;
	while((len = getln(line, MAXLEN-1)) > 0){
		p[i] = malloc(len + 1);
		strcpy(p[i], line);
		i++;
	}
	int j = i > n ? i - n : 0;
	while(j < i){
		printf("%s", p[j++]);
	}
}
int getln(char *s, int max){
	char c;
	int i = 0;
	while((c = getchar()) != '\n' && c != EOF && i < max){
		*s++ = c;	
		i++;
	}
	if(c == '\n'){
		i++;
		*s++ = c;
	}
	*s = '\0';
	return i;	
}
