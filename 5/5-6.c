/**
 * 采用指针而非数组索引方式改写前面章节练习中的某些程序,例如getline(第1,4章),atoi,itoa以及它们的变体形式.(第2,3,4章),
 * reverse(第3章),strindex, getop(第4章)等等.
 */
#include <stdio.h>
#include <ctype.h>
int getline2(char *s, int lim);
int atoi(char *s);
void itoa(int n, char *s);
int strindex(char *s, char *t);
void reverse(char *s);
int getop(char *s);

int main(){
	char s[100];
	/*
	getline2(s, 100);
	printf("%s\n", s);
	*/
	printf("%d\n", atoi("1234"));
	char s2[50] = "this is a test";
	reverse(s2);
	printf("%s\n", s2);
	itoa(13420, s2);
	printf("%s\n", s2);
	printf("%d\n", strindex(s2, "42"));
	getop(s2);
	return 0;
}
int getline2(char *s, int lim){
	char c;
	int i = 0;
	while(i < lim && (c = getchar()) != EOF && c != '\n'){
		*s++ = c;
		i++;
	}
	if(c == '\n'){
		*s++ = '\n';
		i++;
	}
	*s = '\0';
	return i;
}
int aoti(char *s){
	int i = 0;
	while(*s >= '0' && *s <= '9'){
		i = i * 10 + (*s - '0');
		s++;
	}
	return i;
}
void itoa(int n, char *s){
	char *p = s;
	while(n > 0){
		*p++ = n % 10 + '0';
		n /= 10;
	}
	*p = '\0';
	reverse(s);
}
void reverse(char *s){
	char *p = s;
	while(*p) p++;
	int tmp;
	p--;
	for(; s < p; s++, p--){
		tmp = *s;
		*s = *p;
		*p = tmp;
	}
}
int strindex(char *s, char *t){
	char *p, *s1, *s2;
	for(s1 = s; *s1 != '\0'; s1++){
		for(s2 = s1, p = t; *p != '\0'; p++, s2++){
			if(*p != *s2) break;
		}
		if(*p == '\0' && p > t){
			return s1 - s;
		}
	}
	return -1;
}



int getop(char *s){
	int c;
	char *p = s;
	while((*s = c = getchar()) == ' ' || c == '\t');
	*(s+1) = '\0';
	//处理普通操作符
	if(!isdigit(c) && c != '.' && c != '-'){
		return c;
	}
	
	//处理数字
	while(isdigit(c = getchar())){
		*++s = c;
	}
	
	if(c == '.'){
		*++s = c;
		while(isdigit(c = getchar())){
			*++s = c;
		}
	}
	*(s+1) = '\0';
	printf("num=%s\n", p);
	return 0;
}
