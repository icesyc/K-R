/**
 * 假定最多只压回一个字符.请相应地修改getch与ungetch这两个函数.
 * 
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TYPE_MATH 1
#define TYPE_NUM 2

int getop(char s[]);
char getch();
void ungetch(char c);
void print_buff();

//带buffer的getch和ungetch
char buff = 0;

int main(){
	ungetch('c');
	ungetch('b');
	return 0;
}

char getch(){
	return buff > 0 ? buff : getchar();
}
void ungetch(char c){
	if(buff == 0){
		buff = c;
	}else{
		printf("too many chars in buff\n");
	}
}
