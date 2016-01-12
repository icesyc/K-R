/**
 * 编写一个程序，以合理的方式打印任何输入。
 * 该程序至少能够根据用户的习惯以八进制或十六进制打印非图形字符，并截断长文本行。
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define COL_NUM 10

int inc(int pos, int len){
	if(pos + len > COL_NUM){
		putchar('\n');
		return len;
	}else{
		return pos + len;
	}
}
int main(){
	char c;
	int pos = 0;
	while((c = getchar()) != EOF){
		if(iscntrl(c) || c == ' '){
			pos = inc(pos, 4);
			printf("\\%03o", c);
		}else{
			pos = inc(pos, 1);
			putchar(c);
		}
	}
	return 0;
}
