/**
 * 以上介绍的getch与ungetch函数不能正确地处理压回的EOF.考虑压回EOF时应该如何处理?请实现你的设计方案
 * 
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TYPE_MATH 1
#define TYPE_NUM 2

int getop(char s[]);
int getch();
void ungetch(int c);
void print_buff();

//带buffer的getch和ungetch
int buff[100];
int p = 0;

int main(){
	ungetch(EOF);
	printf("char=%d\n", getch(EOF));
	return 0;
}

int getch(){
	return p > 0 ? buff[--p]: getchar();
}
void ungetch(int c){
	if(p < 100){
		buff[p++] = c;
	}
}
