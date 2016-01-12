/**
 * 编写一个函数escape(s, t),将字符串t复制到字符串s中,并在复制过程中将换行符,制表符等不可见字符分别转换为\n,\t等相应的转义字符序列.
 * 要求使用switch语句.再写一个具有相反功能的函数,在复制过程中将转义字符序列转换为实际字符.
 */
#include <stdio.h>
void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int main(){
	char t[] = "abc\tdef\ntest";
	char s[100];
	escape(s, t);
	printf("escape=%s\n", s);
	unescape(t, s);
	printf("unescape=%s\n", t);
}
void escape(char s[], char t[]){
	int i = 0, j = 0;
	while(t[i] != '\0'){
		s[j] = t[i];
		switch(s[j]){
			case '\n': 
				s[j] = '\\';
				s[++j] = 'n';
				break;
			case '\t':
				s[j] = '\\';
				s[++j] = 't';
				break;
			default:
				break;
		}
		i++;
		j++;
	}
	s[j] = '\0';
}

void unescape(char s[], char t[]){
	int i = 0, j = 0;
	while(t[i] != '\0'){
		s[j] = t[i];
		if(t[i] == '\\'){
			switch(t[i+1]){
				case 'n':
					s[j] = '\n';
					i++;
					break;
				case 't':
					s[j] = '\t';
					i++;
					break;
				default:
					break;
			}
		}
		j++;
		i++;
	}
	s[j] = '\0';
}
