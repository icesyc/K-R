/**
 * 重写函数readlines, 将输入的文本行存储到由main函数提供的一个数组中,而不是存储到用alloc分配的存储空间中.该函数的运行速度比改写前快多少?
 */
#include <stdio.h>
#define MAXLINE 500
#define MAXLEN 500

char data[(MAXLEN + 1) * MAXLINE];
int getln(char *line, int max);
int readlines(char *lines[], int maxline);
int main(){
	char line[MAXLINE];
	char *lines[MAXLINE];
	int n = readlines(lines, MAXLINE);
	for(int i = 0; i < n; i++){
		printf("%s", lines[i]);
	}
	return 0;
}

int readlines(char *lines[], int maxline){
	int i = 0, n;
	char *p = data;
	while(i < maxline && (n = getln(p, MAXLEN)) > 0){
		lines[i++] = p;
		p += n;
	}
	return i;
}
int getln(char *line, int max){
	int i = 0;
	char c;
	while(i++ < max && (c = getchar()) != EOF && c != '\n'){
		*line++ = c;
	}
	if(c == '\n'){
		*line++ = c;
		i++;
	}
	*line = '\0';
	return i;
}
