#include <stdio.h>
int blank_num(char s[]);
int main(){
	int n = 0;
	char c;
	while((c = getchar()) != EOF){
		if(c == '\n' || c == '\t' || c == ' ') n++;
	}
	printf("white space n is %d\n", n);
}
