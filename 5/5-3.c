/**
 * 用指针方式实现第2章中的函数strcat。函数strcat(s,t)将t指向的字符串复制到s指向的字符串的尾部。
 */
#include <stdio.h>
void strcat2(char *s, char *t);
int main(){
	char s[30] = "hello, ";
	char *t = "world";
	strcat2(s, t);
	printf("%s\n", s);
	return 0;
}
void strcat2(char *s, char *t){
	while(*s) s++;
	while((*s++ = *t++));
}

