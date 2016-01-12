#include <stdio.h>
int any(char s[], char n[]);
int strpos(char s[], char needle);
int main(){
	char s1[] = "abcdef";
	char s2[] = "123 test abc e";
	int p = any(s1, "ce");
	int p2 = any(s2, "bt");
	printf("s1 first pos is %d char is %c\n", p, s1[p]);
	printf("s2 first pos is %d char is %c\n", p2, s2[p2]);
}

int any(char s[], char n[]){
	int i = 0, p = -1;
	while(s[i] != '\0'){
		if(strpos(n, s[i]) >= 0){
			p = i;
			break;
		}
		i++;
	}
	return p;
}

int strpos(char s[], char needle){
	int i = 0, n = -1;
	while(s[i] != '\0'){
		if(s[i] == needle){
			n = i;
			break;
		}
		i++;
	}
	return n;
}
