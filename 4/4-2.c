/**
 * 对atof函数进行扩充,例它可以处理形如123.45e-6的科学表示法,其中浮点数后面可能会紧眼一个e或E以及一个指数(可能有正负号).
 */
#include <stdio.h>
int isspace(char c);
int isdigit(char c);
double atof(char s[]);

int main(){
	char s[] = "1.2345678e3";
	double f = atof(s);
	printf("g=%g, f=%f\n", f, f);
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

