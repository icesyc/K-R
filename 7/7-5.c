/**
 * 改写第4章中的后缀计算器程序，用scanf函数和(或)sscanf函数实现输入以及数的转换。
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NUMBER '0'

int getop(char *s);
int main(int argc, char *argv[]){
	char s[100];
	while(getop(s) != EOF){
		printf("op=%s\n", s);
	}
	return 0;
}

int getop(char s[]){
	char c;
	float f;
	while((c = getchar()) == ' ' || c == '\t' || c == '\n');
	s[0] = c;
	if(c == EOF){
		return c;
	}
	if(!isnumber(c) && c != '.'){
		s[1] = '\0';
		return c;
	}
	ungetc(c, stdin);
	scanf("%f", &f);
	sprintf(s, "%f", f);
	return NUMBER;
}