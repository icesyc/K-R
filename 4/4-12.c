/**
 * 运用printd函数的设计思想编写一个递归版本的itoa函数.
 * 即通过递归调用把整数转换为字符串.
 */
#include <stdio.h>

void itoa(int n, char s[]);
int main(){
	int i = 1234;
	char s[100];
	itoa(i, s);
	printf("n=%s\n", s);
}
void itoa(int n, char s[]){
	static int i = 0;
	if(n < 0){
		s[i++] = '-';
		n = -n;
	}
	if(n / 10){
		itoa(n / 10, s);	
	}
	s[i++] = n % 10  + '0';
	s[i] = '\0';
}
