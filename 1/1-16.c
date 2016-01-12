#include <stdio.h>
#define MAXLINE 300
int getln(char s[], int limit);
int copy(char from[], char to[], int offset);

int main(){
	char line[MAXLINE];
	char longest[5000];
	int ll, rl, max, offset;
	ll = rl = max = offset = 0;
	while((rl = getln(line, MAXLINE)) > 0){
		ll += rl;
		offset = copy(line, longest, offset);
		if(line[rl-1] == '\n'){
			if(ll > max){
				max = ll;
			}
			ll = 0;
			longest[offset] = '\0';
			offset = 0;
		}
	}
	printf("max line is %d, line=%s\n", max, longest);
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
int copy(char from[], char to[], int offset){
	int i = 0;
	while(from[i] != '\0'){
		to[offset] = from[i];	
		i++;
		offset++;
	}
	return offset;
}
