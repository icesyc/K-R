/**
 * 类似于isupper这样的函数可以通过某种方式实现以达到节省空间或时间的目的。考虑节省空间或时间的实现方式。
 */
#include <stdio.h>
#define isupper2(c) ((c) >= 'A' && (c) <= 'Z' ? 1 : 0)

int isupper(char c){
	return c >= 'A' && c <= 'Z';
}
int main(){
	printf("%d\n", isupper('c'));
	printf("%d\n", isupper2('T'));
	return 0;
}