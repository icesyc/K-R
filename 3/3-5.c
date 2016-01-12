/**
 * 编写函数itob(n,s,b),将整数n转换为以b为底的数,并将转换结果以字符的形式保存在字符串s中.
 * 例如: itob(n,s,16)把整数n格式化成16进制整数保存在s中.
 */
#include <stdio.h>
#define abs(x) ((x) < 0 ? -(x) : (x))

void reverse(char s[], int n);
void itob(int n, char s[], int b);
int main(){
	int n = 127;
	char s[100];
	itob(n, s, 16);
	printf("16 based n=%s\n", s);
	itob(n, s, 10);
	printf("10 based n=%s\n", s);
}

void itob(int n, char s[], int b){
	int sign = 0, i = 0, c = 0;
	if(n > 0) sign = 1;
	do{
		c = abs(n % b);
		s[i++] = c < 10 ? c + '0' : c - 10 + 'a';
	}while((n /= b) != 0);
	if(sign == 0) s[i++] = '-';
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
