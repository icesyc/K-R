/**
 * 修改undcl程序,使它在把文字描述转换为声明的过程中不会生成多余的圆括号.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXTOKEN 100
int gettoken();
char getch();
void ungetch(char c);
void dcl();
void dirdcl();
int nexttoken();

enum {NAME, PARENS, BRACKETS};
char token[MAXTOKEN];
int tokentype;
int pretoken = 0;
char name[MAXTOKEN];
char out[1000];

int main(int argc, char *argv[]){
	char temp[MAXTOKEN];
	while(gettoken() != EOF){
		if(tokentype == PARENS || tokentype == BRACKETS){
			strcat(out, token);	
		}
		else if(tokentype == '*'){
			nexttoken();
			if(tokentype == PARENS || tokentype == BRACKETS){
				sprintf(temp, "(*%s)", out);
			}else{
				sprintf(temp, "*%s", out);
			}
			strcpy(out, temp);
		}
		else if(tokentype == NAME){
			sprintf(temp, "%s %s", token, out);
			strcpy(out, temp);
		}
	}
	printf("%s\n", out);
	return 0;
}

char buff[MAXTOKEN];
int buffpos = 0;
char getch(){
	if(buffpos > 0){
		return buff[--buffpos];
	} 
	return getchar();
}
void ungetch(char c){
	if(buffpos < MAXTOKEN){
		buff[buffpos++] = c;
	}
}

int gettoken(){
	char c;
	char *p = token;
	if(pretoken == 1){
		pretoken = 0;
		return tokentype;
	}
	while((c = getch()) == '\t' || c == ' ');
	*p++ = c;
	if(c == '('){
		c = getch();
		if(c == ')'){
			*p++ = c;
			tokentype = PARENS;
		}else{
			ungetch(c);
			tokentype = '(';
		}
	}
	else if(c == '['){
		while((*p++ = getch()) != ']');
		tokentype = BRACKETS;
	}
	else if(isalpha(c)){
		while(isalnum(c = getch())){
			*p++ = c;
		}
		ungetch(c);
		tokentype = NAME;	
	}else{
		tokentype = c;
	}
	*p = '\0';
	return tokentype;
}

void errormsg(char *msg){
	printf("%s\n", msg);
	pretoken = 1;
}
int nexttoken(){
	int type;
	type = gettoken();
	pretoken = 1;
	return type;
}
