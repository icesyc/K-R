/**
 * 编写一个程序，根据它自身被调用时存放在argv[0]中的名字，实现将大写字母转换为小写字母或将小写字母转换为大写字母的功能。
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]){
	char *p = argv[0];
	char c;
	if(strcmp(p, "lower") == 0){
		while((c = getchar()) != EOF){
			putchar(tolower(c));
		}
	}else{
		while((c = getchar()) != EOF){
			putchar(toupper(c));
		}
	}
	return 0;
}
