#include <stdio.h>
#define MAXLINE 1000
int getln(char s[], int limit);
int slen(char s[]);
void reverse(char s[], char r[]);

int main(){
	char line[MAXLINE], reline[MAXLINE];
	int rl = 0;
	while((rl = getln(line, MAXLINE)) != EOF){
		reverse(line, reline);	
		printf("line length is %d, line=%s\n", rl, reline);
	}
}

int getln(char s[], int limit){
	int len = 0, idx = -1;
	char c;
	while(len < limit && (c = getchar()) != '\n' && c != EOF){
		s[len] = c;	
		len++;
	}
	if(len == 0 && c == EOF){
		return EOF;
	}
	if(c == '\n'){
		s[len] = c;
		len++;
	}
	s[len] = '\0';
	return len;
}
int slen(char s[]){
	int i = 0;
	while(s[i] != '\0') i++;
	return i;
}
void reverse(char s[], char r[]){
	int i = 0, j = slen(s) - 1;
	while(s[i] != '\0'){
		r[j] = s[i];
		i++;
		j--;
	}
	r[i] = '\0';
}
