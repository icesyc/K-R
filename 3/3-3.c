/**
 * 编写函数expand(s1, s2),将字符串s1中类似于a-z一类的速记符号在字符串s2中扩展为等价的完整列表abc...xyz.该函数可以处理大小写字母和数字,
 * 并可以处理a-b-c, a-z0-9与-a-z等类似的情况,作为前导和尾随的-字符原样排印.
 */
#include <stdio.h>
#define NORMAL 0
#define LOWER_CHAR 1
#define UPPER_CHAR 2
#define NUMBER 3
void expand(char s1[], char s2[]);
int isdigit(char c);
int isupper(char c);
int islower(char c);

int main(){
	char s1[] = "-a-gf-Ab-0-9A-F-";
	char s2[100];
	expand(s1, s2);
	printf("expanded=%s\n", s2);
	return 0;
}

void expand(char s1[], char s2[]){
	int i = 0, j = 0, k = 0;
	int state = NORMAL;
	int start = 0, end = 0;

	//使用状态机来处理
	while(s1[i] != '\0'){
		if(state != NORMAL){
			if(s1[i] != '-'){
				state = NORMAL;
				continue;
			}
			if((state == LOWER_CHAR && islower(s1[i+1])) ||
			   (state == UPPER_CHAR && isupper(s1[i+1])) ||
			   (state == NUMBER && isdigit(s1[i+1]))){
				for(k=start+1; k<= s1[i+1]; k++) s2[j++] = k;
				i += 2;
			}else{
				//跳过-
				s2[j++] = s1[i++];
			}
			state = NORMAL;
			continue;
		}

		//normal的处理
		if(islower(s1[i])){
			state = LOWER_CHAR;
			start = s1[i];
		}
		else if(isupper(s1[i])){
			state = UPPER_CHAR;
			start = s1[i];
		}
		else if(isdigit(s1[i])){
			state = NUMBER;
			start = s1[i];
		}
		s2[j++] = s1[i++];
	}
	s2[j] = '\0';
}

int isdigit(char c){
	return c >= '0' && c <= '9';
}
int islower(char c){
	return c >= 'a' && c <= 'z';
}
int isupper(char c){
	return c >= 'A' && c <= 'Z';
}
