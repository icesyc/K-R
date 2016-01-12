/**
 * 去掉c语言所有注释
 *
 * @author iceshi
 */
#include <stdio.h>
int main(){
	char c, nc;
	//标识是否在字符串中,是否在注释中
	int inSingleQuote = 0, inDoubleQuote = 0, inSingleComment = 0, inMultiComment = 0, inState = 0;
	//使用状态机来处理
	c = getchar();
	while((nc = getchar()) != EOF){
		/* 是否到了单行注释结束状态? */
		if(inSingleComment){
			if(c == '\n'){
				inSingleComment = 0;
				c = 0;
			}else{
				c = nc;
			}
			continue;
		}
		//是否到了多行注释结束状态?
		if(inMultiComment){
			if(c == '*' && nc == '/'){
				inMultiComment = 0;
				c = 0;
			}else{
				c = nc;
			}
			continue;
		}
		if(inSingleQuote && c == '\''){
			inSingleQuote = 0;
		}else if(inDoubleQuote && c == '\"'){
			inDoubleQuote = 0;
		}else if(c == '\''){
			inSingleQuote = 1;
		}else if(c == '\"'){
			inDoubleQuote = 1;
		}else if(c == '/' && nc == '*' && !inSingleQuote && !inDoubleQuote){
			inMultiComment = 1;
		}else if(c == '/' && nc == c && !inSingleQuote && !inDoubleQuote){
			inSingleComment = 1;
		}
		if(!inSingleComment && !inMultiComment){
			printf("%c", c);
		}
		c = nc;
	}
}
