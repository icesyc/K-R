/**
 * 在求对二的补码时,表达式x&=(x-1)可以删除x中最右边值为1的一个二进制位.请解释这样做的道理.用这一方法重写bitcount函数,以加快其执行速度.
 */
#include <stdio.h>
int bindec(char *bin);
int bitcount(int n);
int main(){
	char s[] = "1101011001011";
	int bc = bitcount(bindec(s));
	printf("bitcount=%d\n", bc);
	return 0;
}
int bitcount(int n){
	int c = 0;
	while(n > 0){
		n &= n - 1;
		c++;
	}
	return c;
}
int bindec(char *bin){
    int n = 0, i = 0;
    while(bin[i] != '\0'){
        n = (n << 1) + (bin[i] - '0');
        i++;
    }
    return n;
}
