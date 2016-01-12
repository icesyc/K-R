/**
 * 扩展dcl程序的功能,使它能够处理包含其它成分的声明,例如带有函数参数类型的声明,带有类似于const限定符的声明等.
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
int cmpstr(const void *a, const void *b);
void paramdcl();
void dclspec();
int typespec();
int typequal();
int nexttoken();
void errormsg(char *msg);

enum {NAME, PARENS, BRACKETS};
char token[MAXTOKEN];
int tokentype;
int pretoken = 0;
char name[MAXTOKEN];
char out[1000];

int main(int argc, char *argv[]){
	char datatype[MAXTOKEN];
	while(gettoken() != EOF){
		strcpy(datatype, token);
		dcl();
	}

	printf("%s: %s %s\n", name, out, datatype);
	return 0;
}

void dcl(){
	int np = 0;
	while(gettoken() == '*') np++;
	dirdcl();
	while(np-- > 0){
		strcat(out, " pointer to");
	}
}

void dirdcl(){
	int type;
	if(tokentype == '('){
		dcl();
		if(tokentype != ')'){
			printf("error: missing )\n");
		}
	}
	else if(tokentype == NAME){
		if(*name == '\0'){
			strcpy(name, token);
		}
	}
	else {
		pretoken = 1;
	}
	while((type = gettoken()) == PARENS || type == BRACKETS || type == '('){
		if(type == PARENS){
			strcat(out, " function returning");
		}
		else if(type == BRACKETS){
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}else{
			strcat(out, " function expecting");
			paramdcl();	
			strcat(out, " and returning");
		}
	}
}

//参数解析
void paramdcl(){
	int type;
	do{
		dclspec();
	}while(tokentype == ',');
	if(tokentype != ')'){
		errormsg("missing ) in param declaration\n");
	}
}
void dclspec(){
	char temp[MAXTOKEN];
	temp[0] = '\0';
	gettoken();
	do{
		if(tokentype != NAME){
			pretoken = 1;
			dcl();
		}
		//类型符号
		else if(typespec() || typequal()){
			strcat(temp, " ");
			strcat(temp, token);
			gettoken();
		}
		else{
			errormsg("unknown type in param list\n");
		}
	}while(tokentype != ',' && tokentype != ')');
	if(tokentype == ','){
		strcat(temp, ",");
	}
	strcat(out, temp);
}
int typespec(){
	static char *types[] = {"char", "int", "void"};
	char *pt = token;
	void *found = bsearch(&pt, types, sizeof(types) / sizeof(char *), sizeof(char *), cmpstr);
	return found != NULL;
}

int typequal(){
	static char *types[] = {"const", "volatile"};
	char *pt = token;
	void *found = bsearch(&pt, types, sizeof(types) / sizeof(char *), sizeof(char *), cmpstr);
	return found != NULL;
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
int cmpstr(const void *a, const void *b){
	return strcmp(*(char **)a, *(char **)b);
}
int nexttoken(){
	int type;
	type = gettoken();
	pretoken = 1;
	return type;
}
