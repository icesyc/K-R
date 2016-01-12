/**
 * 修改itoa函数,使得该函数可以接收三个参数,其中,第三个参数为最小字段宽度.
 * 为了保证转换后所得到的结果至少具有第三个参数指定的最小宽度,在必要时应在所得结果的左边填充一定的空格.
 */
#include <stdio.h>
#define abs(x) ((x) < 0 ? -(x) : (x))

void reverse(char s[], int n);
void itoa(int n, char s[], int b);
int main(){
	int n = 127;
	char s[100];
	itoa(n, s, 8);
	printf("%d\t=%s\n", n, s);
	n = -4890;
	itoa(n, s, 8);
	printf("%d\t=%s\n", n, s);
}

void itoa(int n, char s[], int b){
	int sign = 0, i = 0, c = 0;
	if(n > 0) sign = 1;
	do{
		c = abs(n % 10);
		s[i++] = c + '0';
	}while((n /= 10) != 0);
	if(sign == 0) s[i++] = '-';
	while(i < b){
		s[i++] = ' ';
	}
	s[i] = '\0';
	reverse(s, i);
}

//反转字符串
void reverse(char s[], int n){
    int i, j, tmp;
    i = 0, j = n - 1;
    while(i < j){
        tmp = s[i];
        s[i++] = s[j];
        s[j--] = tmp;
    }
}
