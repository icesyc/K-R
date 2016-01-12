/**
 * 改成minprintf函数，使它能完成printf函数的更多功能。
 */
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void minprintf(char *fmt, ...);
int main(int argc, char *argv[]){
	minprintf("test %s %d %f", "a", 12, 5.8);
	return 0;
}
void minprintf(char *fmt, ...){
	char *p;
	int ival;
	double dval;
	char *sval;
	va_list ap;
	va_start(ap, fmt);
	char localfmt[100];
	for(p = fmt; *p; p++){
		if(*p != '%'){
			putchar(*p);
			continue;
		}
		int i = 0;
		while(!isalpha(*p) && *p != EOF){
			localfmt[i++] = *p++;
		}
		localfmt[i++] = *p;
		localfmt[i] = '\0';

		switch(*p){
			case 'd':
				ival = va_arg(ap, int);
				printf(localfmt, ival);
				break;
			case 's':
				sval = va_arg(ap, char *);
				while(*sval){
					putchar(*sval++);
				}
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf(localfmt, dval);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);
}