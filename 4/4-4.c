/**
 * 在栈操作中添加几个命令,分别用于在不弹出元素的情况下打印栈顶元素;
 * 复制栈顶元素;交换栈顶两个元素的值.另外增加一个命令用于清空栈.
 */
#include <stdio.h>
double pop();
void push(char c);
double last();
void copy();
void swap();
void clear();
void print_stack();

int main(){
	int i = 0;
	while(i++ < 5) push(i);
	print_stack();
	pop();
	printf("pop:");
	print_stack();
	double l = last();
	printf("last=%f\n", l);
	swap();
	printf("swap:");
	print_stack();
	copy();
	printf("copy:");
	print_stack();
	return 0;
}

double stack[100];
int p = 0;
void push(char c){
	if(p < 100){
		stack[p++] = c;
	}
}
double pop(){
	if(p > 0){
		return stack[--p];
	}
	return 0;
}
double last(){
	double c = pop();
	if(c){
		push(c);
	}
	return c;
}
void copy(){
	double c = pop();
	if(c){
		push(c);
		push(c);
	}
}
void swap(){
	double c = pop();
	double c2 = pop();
	if(c && c2){
		push(c);
		push(c2);
	}
}
void clear(){
	p = 0;
}
void print_stack(){
	int p2 = p;
	while(p2-- > 0) printf("%f ", stack[p2]);
	printf("\n");
}
