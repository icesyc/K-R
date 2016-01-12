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
	while((rl = getln(line, MAXLINE)) > 0){
		if(rl > max){
			printf("line length is %d, line=%s\n", rl, line);
		}
	}
}

int getln(char s[], int limit){
	int len = 0;
	char c;
	while(len < limit && (c = getchar()) != '\n' && c != EOF){
		s[len] = c;	
		len++;
	}
	if(c == '\n'){
		s[len] = c;
		len++;
	}
	s[len] = '\0';
    return len;
}
int copy(char from[], char to[]){
	int i = 0;
	while((to[i] = from[i]) != '\0'){
		i++;
	}
	return i;
}
