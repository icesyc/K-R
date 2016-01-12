/**
 * 在数的对二的补码表示中,我们编写的itoa函数不能处理最大的负数,即n = -2 ^ (字长 - 1)的情况,请解释其原因.
 * 修改该函数,使它在任何机器上运行时都能打印出正确的值.
 */
#include <stdio.h>
#include <limits.h>
#define abs(x) ((x) < 0 ? -(x) : (x))
void itoa(int n, char s[]);
void itoa2(int n, char s[]);
void reverse(char s[], int n);
int main(){
	char s[100];
	itoa(12345, s);
	printf("n=%s\n", s);
	itoa(INT_MIN, s);
	printf("n_min=%s\n", s);
	itoa2(12345, s);
	printf("n2=%s\n", s);
	itoa2(INT_MIN, s);
	printf("n2_min=%s\n", s);
	return 0;
}
void itoa(int n, char s[]){
	int sign, i = 0;
	if(n < 0){
		sign = 0;
		n = -n;
	}else{
		sign = 1;
	}
	do{
		s[i++] = n % 10 + '0';	
	}while((n /= 10) > 0);
	if(sign == 0) s[i++] = '-';
	s[i] = '\0';
	reverse(s, i);
	
}
void itoa2(int n, char s[]){
	int sign, i = 0;
	if(n < 0){
		sign = 0;
		n = -n;
	}else{
		sign = 1;
	}
	do{
		s[i++] = abs(n % 10) + '0';	
	}while((n /= 10) != 0);
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
