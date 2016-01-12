/**
 * 编写一个递归版本的reverse(s)函数,以将字符串s倒置.
 */
#include <stdio.h>
#include <string.h>
int reverse(char s[]);
int main(){
	char s[] = "abcde";
	reverse(s);
	printf("reverse=%s\n", s);
}
int reverse(char s[]){
	static int i = 0;
	int len, j;
	len = strlen(s);
	j = len - 1 - i;
	if(i >= j){
		return 0;
	}
	char tmp = s[i];
	s[i++] = s[j];
	s[j] = tmp;
	reverse(s);
	return 0;
}

