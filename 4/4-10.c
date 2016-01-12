/**
 * 另一种方法是通用getline函数读入整个输入行,这种情况下可以不使用getch和ungetch函数.请运用这一方法修改计算器程序.
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define TYPE_MATH 1
#define TYPE_NUM 2

double atof(char s[]);
double push(double i);
double pop();
int getop(char s[]);
int getln(char ln[], int limit);

int main(){
	int type;
	char s[100];
	double op;
	while((type = getop(s)) != EOF){
		switch(type){
			case TYPE_NUM:
				push(atof(s));
				break;
			case '+':
				op = pop();
				push(pop() + op);
				break;
			case '-':
				op = pop();
				push(pop() - op);
				break;
			case '*':
				op = pop();
				push(pop() * op);
				break;
			case '/':
				op = pop();
				if(op != 0.0){
					push(pop() / op);	
				}
				break;
			case '%':
				op = pop();
				if(op != 0.0){
					push((int)pop() % (int)op);
				}	
				break;
			case TYPE_MATH:
				if(strcmp(s, "sin") == 0){
					push(sin(pop()));
				}else if(strcmp(s, "exp") == 0){
					push(exp(pop()));
				}else if(strcmp(s, "pow") == 0){
					double op = pop();
					push(pow(pop(), op));
				}else {
					printf("error math command %s\n", s);
				}	
				break;
			case '\n':
				printf("res=%f\n", pop());	
				break;
			default:
				printf("error command %c\n", type);
				break;
		}
	}
	return 0;
}

double atof(char s[]){
	int i = 0, sign = 1;
	double f, pow;

	//去掉空白字符
	while(isspace(s[i])) i++;

	//处理符号
	if(s[i] == '-'){
		sign = -1;
		i++;
	} else if(s[i] == '+'){
		sign = 1;
		i++;
	}

	//处理数字
	for(f = 0.0; isdigit(s[i]); i++){
		f = f * 10 + (s[i] - '0');	
	}
	//处理小数
	if(s[i] == '.'){
		i++;
	}
	
	for(pow = 1; isdigit(s[i]); i++){
		f = f * 10 + (s[i] - '0');
		pow *= 10;
	}
	f *= sign / pow;

	//处理科学计数
	int exp = 0;
	double exp_base = 10;
	if(s[i] == 'e' || s[i] == 'E'){
		i++;
	}
	if(s[i] == '-'){
		i++;
		exp_base = 0.1;
	}

	for(exp = 0; isdigit(s[i]); i++){
		exp = exp * 10 + (s[i] - '0');	
	}
	while(exp-- > 0){
		f *= exp_base;
	}
	return f;
}

double stack[100];
int p = 0;
double push(double i){
	if(p >= 100){
		return -1;
	}		
	return stack[p++] = i;
}
double pop(){
	return p > 0 ? stack[--p] : 0.0;
}
double last(){
	return stack[p-1];
}

char line[100];
int li = 0;
int getop(char s[]){
	int i = 0, c;
	
	if(line[li] == '\0'){
		if(getln(line, 100) == 0){
			return EOF;	
		}
		li = 0;
	}
		
	//去除空格
	while(line[li] == ' ' || line[li] == '\t') li++;

	//处理数学操作符
	while(islower(line[li])){
		s[i++] = line[li++];
	}
	s[i] = '\0';
	if(i > 0){
		return TYPE_MATH;
	}

	//处理普通操作符
	c = s[i++] = line[li++];
	if(!isdigit(c) && c != '.' && c != '-'){
		return c;
	}
	
	//处理负号
	if(c == '-' && !isdigit(line[li])){
		return c;
	}

	//处理数字
	while(isdigit(line[li])){
		s[i++] = line[li++];
	}
	
	if(line[li] == '.'){
		s[i++] = line[li++];
		while(isdigit(line[li])){
			s[i++] = line[li++];
		}
	}
	s[i] = '\0';
	printf("num=%s\n", s);
	return TYPE_NUM;
}
int getln(char ln[], int limit){
	int i = 0;
	char c;
	while((c = getchar()) != EOF && c != '\n' && i < limit){
		ln[i++] = c;
	}
	if(c == '\n'){
		ln[i++] = c;
	}
	ln[i] = '\0';
	return i;
}
