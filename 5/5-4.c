/**
 * 编写函数strend(s,t)。如果字符串t出现在字符串s的尾部，该函数返回1；否则返回0.
 */
#include <stdio.h>
int strend(char *s, char *t);
int main(){
	char *s = "hello, worldllo";
	char *t = "llo";
	printf("%d\n", strend(s, t));
	return 0;
}
int strend(char *s, char *t){
	char *i = t;
	while(*s != '\0'){
		if(*s != *t){
			t = i;
		}else{
			t++;
		}
		s++;
	}
	return *s == '\0' && *t == '\0';
}

