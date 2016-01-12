/**
 * 给计算器程序增加访问sin,exp与pow等库函数的操作.
 * 有关这些库函数的详细信息,参见附录B.4节中的头文件<math.h>
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
char getch();
void ungetch(char c);

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

//带buffer的getch和ungetch
char buff[100];
int bp = 0;
char getch(){
	return bp > 0 ? buff[--bp] : getchar();
}
void ungetch(char c){
	if(bp < 100){
		buff[bp++] = c;
	}
}
int getop(char s[]){
	int i = 0, c;
	while((c = getch()) == ' ' || c == '\t');
		
	//处理数学操作符
	while(islower(c)){
		s[i++] = c;
		c = getch();
	}
	
	s[i] = '\0';
	if(i > 0){
		ungetch(c);
		return TYPE_MATH;
	}
	//处理普通操作符
	if(!isdigit(c) && c != '.' && c != '-'){
		return c;
	}
	
	s[i++] = c;
	c = getch();
	//处理负号
	if(s[i-1] == '-' && !isdigit(c)){
		ungetch(c);
		return s[i-1];
	}

	//处理数字
	while(isdigit(c)){
		s[i++] = c;
		c = getch();
	}
	

	if(c == '.'){
		s[i++] = c;
		c = getch();
		while(isdigit(c)){
			s[i++] = c;
			c = getch();
		}
	}
	s[i] = '\0';
	if(c != EOF){
		ungetch(c);
	}
	printf("num=%s\n", s);
	return TYPE_NUM;
}
