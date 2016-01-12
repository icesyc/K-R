#include <stdio.h>
#define MAXLINE 40
#define TAB 8
int main(){
	int i = 0, s = 0, t = 0, sl = 0;
	char space[MAXLINE];
	char c;
	while((c = getchar()) != EOF){
		if(c == '\t'){
			i += TAB - i % TAB;
			space[sl++] = c;
		}else if(c == '\n'){
			i = 0;
		}
		else if(c == ' '){
			i++;
			space[sl++] = c;
		}else{
			i++;
		}
		if(i > MAXLINE){
			printf("\n");
			i = i - MAXLINE;
		}
		if(c != '\t' && c != ' '){
			if(sl > 0){
				space[sl] = '\0';
				sl = 0;
				printf("%s", space);
			}
			printf("%c", c);
		}
	}
	return 0;
}

