/**
 * 模仿函数getint的实现方法，编写一个读取浮点数的函数getfloat
 * getfloat函数的返回值应该是什么类型？
 */
#include <stdio.h>
#include <ctype.h>
int getfloat(double *pn);
char getch();
void ungetch(char c);

int main(){
	double i = 0.0;
	getfloat(&i);
	printf("getfloat=%f\n", i);
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
int getfloat(double *pn){
	int c, sign = 1;
	double n;
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
	//处理小数点
	if(c == '.'){
		c = getch();
	}
	for(n = 1; isdigit(c); c = getch()){
		*pn = 10 * *pn + (c - '0');
		n *= 10;
	}
	*pn *= sign / n;
	if(c != EOF){
		ungetch(c);
	}
	return c;
}
