/**
 * 定义宏swap(t,x,y)以交换t类型的两个参数.(使用程序块结构会对你有所帮助.)
 */
#include <stdio.h>
#define swap(t,x,y) t tmp=x; x=y; y=tmp;

int main(){
	int a = 1, b = 2;
	swap(int, a, b);
	printf("swap a=%d, b=%d\n", a, b);
}
