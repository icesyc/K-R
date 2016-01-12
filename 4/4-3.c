/**
 * 在有了基本框架后,对计算器程序进行扩充就比较简单了,在该程序中加入取模(%)运算符,并注意考虑负数的情况.
 */
#include <stdio.h>
#define TYPE_OP 1
#define TYPE_NUM 2

int isspace(char c);
int isdigit(char c);
double atof(char s[]);
double push(double i);
double pop();
double last();
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

int isspace(char c){
	return c == ' ' || c == '\t';
}
int isdigit(char c){
	return c >= '0' && c <= '9';
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
		
	if(c != '-' && c != '.' && !isdigit(c)){
		return c;
	}
	s[i++] = c;
	while(isdigit(c = getch())){
		s[i++] = c;
	}
	//如果只有一个负号,是减法
	if(i == 1 && s[0] == '-'){
		ungetch(c);
		return s[0];
	}

	if(c == '.'){
		s[i++] = c;
		while(isdigit(c = getch())){
			s[i++] = c;
		}
	}
	s[i] = '\0';
	if(c != EOF){
		ungetch(c);
	}
	return TYPE_NUM;
}
