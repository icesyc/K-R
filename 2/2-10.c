/**
 * 重新编写将大写字母转换为小写字母的函数lower, 并用条件表达式替代其中的if-else结构.
 */
#include <stdio.h>
char lower(char c);
int main(){
	printf("%c\n", lower('B'));
	printf("%c\n", lower('D'));
	return 0;
}

char lower(char c){
	return c >= 'A' && c <= 'Z' ? (c - 'A' + 'a') : c;
}
