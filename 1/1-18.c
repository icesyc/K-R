#include <stdio.h>
#define MAXLINE 1000
int getln(char s[], int limit);
int copy(char from[], char to[]);

int main(){
	char line[MAXLINE];
	char longest[MAXLINE];
	int rl, max;
	rl = 0;
	max = 80;	
	while((rl = getln(line, MAXLINE)) != EOF){
		if(rl == 0) continue;
		printf("line length is %d, line=%s\n", rl, line);
	}
}

int getln(char s[], int limit){
	int len = 0, idx = -1;
	char c;
	while(len < limit && (c = getchar()) != '\n' && c != EOF){
		if(c == '\t' || c == ' '){
			if(idx == -1) idx = len;
		}else{
			idx = -1;
		}
		s[len] = c;	
		len++;
	}
	if(len == 0 && c == EOF){
		return EOF;
	}
	len = idx != -1 ? idx : len;
	s[len] = '\0';
	return len;
}
