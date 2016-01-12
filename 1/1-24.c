/**
 * 检查C语言的基本的语法错误,包括各种括号和单双引号的匹配
 *
 * @author iceshi
 */
#include <stdio.h>
//定义一下状态机的各种状态
#define CODE 1
#define COMMENT 2
#define CHAR 3
#define STRING 4
#define SINGLE_COMMENT 7
#define MULTI_COMMENT 8
#define ERROR -1

//定义错误类型
#define ERROR_BRACE 1
#define ERROR_BRACKET 2
#define ERROR_PARENTHESES 3
#define ERROR_CHAR 4
#define ERROR_STRING 5

int main(){
	char c, nc;
	c = getchar();
	int state = CODE;
	//用于保存括号的层级
	int stack[100], level = 0, error = 0;
	while((nc = getchar()) != EOF){
		switch(state){
			case CODE:
				if(c == '\''){
					state = CHAR;
					break;
				}
				if(c == '\"'){
					state = STRING;
					break;
				}
				if(c == '/' && nc == c){
					state = SINGLE_COMMENT;
					break;
				}
				if(c == '/' && nc == '*'){
					state = MULTI_COMMENT;
					break;
				}
				if(c == '{' || c == '[' || c == '('){
					stack[level++] = c;				
					break;
				}
				if(c == '}'){
					if(stack[level-1] != '{'){
						state = ERROR;
						error = ERROR_BRACE;	
						break;
					}
					level--;
					break;
				}
				if(c == ']'){
					if(stack[level-1] != '['){
						state = ERROR;
						error = ERROR_BRACKET;
						break;
					}
					level--;
					break;
				}
				if(c == ')'){
					if(stack[level-1] != '('){
						state = ERROR;
						error = ERROR_PARENTHESES;
						break;
					}
					level--;
					break;
				}
				break;
			case SINGLE_COMMENT:
				if(c == '\n'){
					state = CODE;
				}
				break;
			case MULTI_COMMENT:
				if(c == '*' && nc == '/'){
					state = CODE;
				}
				break;
			case CHAR:
				if(c == '\''){
					state = CODE;
					break;
				}
				//单引号只能有一个char
				if(nc != '\''){
					state = ERROR;
					error = ERROR_CHAR;
				}
				break;
			case STRING:
				if(c == '\"'){
					state = CODE;
					break;
				}
				//双引号不能包含换行
				if(c == '\n'){
					state = ERROR;
					error = ERROR_STRING;
				}
				break;
			default:
				break;
		}	
		if(state == ERROR){
			switch(error){
				case ERROR_BRACE:
					printf("syntax error: } should match {.\n");
					break;
				case ERROR_BRACKET:
					printf("syntax error: ] should match [.\n");
					break;
				case ERROR_PARENTHESES:
					printf("syntax error: ) should match (.\n");
					break;
				case ERROR_CHAR:
					printf("syntax error: apos should have no more than 1 character in it.\n");
					break;
				case ERROR_STRING:
					printf("\\n could not be included in quote.\n");
					break;	
				default:
					printf("syntax error: unknown error.\n");
					break;
			}
			break;
		}
		c = nc;
	}
	//检查完后再看一下state,是否有未闭合的情况
	switch(state){
		case CHAR:
			state = ERROR;
			printf("apos should be closed.");
			break;
		case STRING:
			state = ERROR;
			printf("quote should be closed.");
			break;
		case MULTI_COMMENT:
			state = ERROR;
			printf("multi comment should be closed.");
			break;
		case CODE:
			if(level > 0){
				state = ERROR;
				c = stack[level-1];
				if(c == '{') c = '}';
				else if(c == '[') c = ']';
				else if(c == '(') c = ')';
				printf("can not find end tag %c\n", c);	
			}
			break;
		default:
			break;
	}
	if(state != ERROR){
		printf("syntax ok!\n");
	}
	
}

