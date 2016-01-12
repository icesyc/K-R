/**
 * 类似于上一节中的函数minprintf，编写scanf函数的一个简化版本。
 */
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
void minscanf(char *fmt, ...);
int main(int argc, char *argv[]){
	unsigned n;
	char str[100];
	minscanf("%s|%d", str, &n);
	printf("str=%s n=%u\n", str, n);
	return 0;
}
void minscanf(char *fmt, ...){
	char *p;
	unsigned *ip;
	double *dp;
	char *sp;
	char localfmt[100];
	va_list ap;
	va_start(ap, fmt);
	int i;
	for(p = fmt; *p != '\0'; p++){
		if(*p != '%'){
			localfmt[i++] = *p;
			continue;
		}
		localfmt[i++] = *p++;
		while(*p != EOF && !isalpha(*p)){
			localfmt[i++] = *p++;
		}
		localfmt[i++] = *p;	
		localfmt[i] = '\0';
		printf("fmt=%s\n", localfmt);
		switch(*p){
			case 'u':
				ip = va_arg(ap, unsigned *);
				scanf(localfmt, ip);
				break;
			case 's':
				sp = va_arg(ap, char *);
				scanf(localfmt, sp);
				break;
			case 'f':
				dp = va_arg(ap, double *);
				scanf(localfmt, dp);
				break;
			default:
				scanf(localfmt);
				break;
		}
		i = 0;
	}
	va_end(ap);
}
