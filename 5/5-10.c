/**
 * 编写程序expr,以计算从命令行输入的逆波兰表达式的值,其中每个运算符或操作数用一个单独的参数表示.
 * 例如,命令expr 2 3 4 + *将计算表达式2 * (3 + 4)的值.
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLEN 100
#define OPERATOR -5
int head = 0;
int stack[MAXLEN];
int push(int i){
	if(head >= MAXLEN){
		return -1;
	}
	stack[head++] = i;
	return i;
}
int pop(){
	if(head > 0){
		return stack[--head];
	}
	return -1;
}
int getop(char *arg){
	int n;
	if(!isdigit(*arg)){
		return OPERATOR;
	}
	return atoi(arg);
}
int main(int argc, char *argv[]){
	int op;
	char *arg;
	while(--argc > 0){
		arg = *++argv;
		op = getop(arg);
		if(op == OPERATOR){
			switch(arg[0]){
				case '+':
					push(pop() + pop());
					break;
				case '-':
					push(pop() - pop());
					break;
				case '*':
					push(pop() * pop());
					break;
				case '/':
					push(pop() / pop());
					break;
			}
		}else{
			push(op);
		}
	}
	printf("res=%d\n", pop());
	return 0;
}

