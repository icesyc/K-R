/**
 * 编写一个函数rightrot(x,n),该函数返回将x循环右移(即从最右端移出的位将从最左端移入)n位后所得到的值
 */
#include <stdio.h>
unsigned int rightrot(unsigned int x, int n);
int bitlen(int n);
int bindec(char *bin);
char *decbin(int n);
int main(){
	int x, n = 3;
	char s[] = "110101";
	x = bindec(s);
	x = rightrot(x, n);
	printf("%s\n", decbin(x));
	return 0;
}
unsigned int rightrot(unsigned int x, int n){
	int l, r;	
	l = bitlen(x);
	r = x & ~(~0 << n);
	return (x >> n) | (r << (l - n));
}
int bitlen(int n){
	int l = 0;
	while((~0 & n) > 0){
		n = n >> 1;
		l++;
	}
	return l;
}
int bindec(char *bin){
	int n = 0, i = 0;
	while(bin[i] != '\0'){
		n = (n << 1) + (bin[i] - '0');
		i++;
	}
	return n;
}
char s[32];
char *decbin(int n){
	int j = 0;
	int flag = 0;
	for(int i = 31; i >= 0; i--){
		if((n & (1 << i)) > 0){
			flag = 1;	
			s[j++] = '1';
		}else{
			if(flag == 1){
				s[j++] = '0';
			}	
		}
	}
	s[j] = '\0';
	return s;
}
