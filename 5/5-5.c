#include <stdio.h>
/**
 * 实现函数strncpy, strncat, strncmp,他们最多对参数字符串中的前n个字符进行操作.例如:函数strncpy(s,t,n)将t中最多前n个字符复制到s中.更详细的说明请参见附录B.
 */

int strncpy(char *s, char *t, int n);
int strncat(char *s, char *t, int n);
int strncmp(char *s, char *t, int n);

int main(){
	char s[100] = "hello, ";
	char *t = "world, this is test";
	strncpy(s, t, 5);
	printf("%s\n", s);
	strncat(s, t, 5);
	printf("%s\n", s);
	char *t2 = "wo";
	printf("%d\n", strncmp(s, t2, 5));
	return 0;
}

int strncpy(char *s, char *t, int n){
	int i = 0;
	while((*s = *t) != '\0' && i++ < n){
		s++;
		t++;
	}
	*s = '\0';
	return i;
}
int strncat(char *s, char *t, int n){
	int i = 0;
	while(*s) s++;
	while((*s = *t) != '\0' && i++ < n){
		s++;
		t++;	
	}
	*s = '\0';
	return i;
}
int strncmp(char *s, char *t, int n){
	int i = 0;
	while(*s == *t && i++ < n){
		if(*s == '\0') return 0;
		s++;
		t++;
	}
	return i == n ? 0 : *s - *t;
}
