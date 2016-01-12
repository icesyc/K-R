/**
 * 编写一个函数ungets(s),将整个字符串s压回到输入中.
 * ungets函数需要使用buf和bufp吗?它能否仅使用ungetch函数?
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TYPE_MATH 1
#define TYPE_NUM 2

int getop(char s[]);
char getch();
void ungetch(char c);
void ungets(char s[]);
void print_buff();

//带buffer的getch和ungetch
char buff[100];
int bp = 0;

int main(){
	ungets("123456");
	print_buff();
	return 0;
}

char getch(){
	return bp > 0 ? buff[--bp] : getchar();
}
void ungetch(char c){
	if(bp < 100){
		buff[bp++] = c;
	}
}
void ungets(char s[]){
	int len = strlen(s);
	while(len > 0){
		ungetch(s[--len]);
	}
}
void print_buff(){
	int p = bp;
	while(p > 0){
		printf("%c", buff[--p]);	
	}
	printf("\n");
}
