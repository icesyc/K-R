/**
 * 在上面的例子中，如果符号+或-的后面紧跟的不是数字，getint函数将把符号视为数字0的有效表达式。
 * 修改该函数，将这种形式的+或-符号重新写回到输入流中。
 */
#include <stdio.h>
#include <ctype.h>
int getint(int *pn);
char getch();
void ungetch(char c);

int main(){
	int i = 0;
	getint(&i);
	printf("getint=%d\n", i);
	return 0;
}
//带buffer的getch和ungetch
char buff[100];
int bp = 0;
char getch(){
	return bp > 0 ? buff[--bp] : getchar();
}
void ungetch(char c){
	if(bp < 100){
		buff[bp++] = c;
	}
}
int getint(int *pn){
	int c, sign = 1;
	while(isspace(c = getch()));
	if(!isdigit(c) && c != '+' && c != '-' && c != EOF){
		ungetch(c);
		return 0;
	}
	if(c == '-' || c == '+'){
		if(c == '-'){
			sign = -1;
		}
		char d = c;
		c = getch();
		if(!isdigit(c)){
			if(c != EOF){
				ungetch(c);
			}
			ungetch(d);
			return 0;
		}
	}
	for(*pn = 0; isdigit(c); c = getch()){
		*pn = 10 * *pn + (c - '0');
	}
	*pn *= sign;
	if(c != EOF){
		ungetch(c);
	}
	return c;
}
