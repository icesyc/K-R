#include <stdio.h>
int squeeze(char s[], char n[]);
int strpos(char s[], char needle);
int main(){
	char s1[] = "abcdef";
	char s2[] = "123 test abc e";
	squeeze(s1, "be");
	squeeze(s2, "123a ");
	printf("%s\n", s1);
	printf("%s\n", s2);
}

int squeeze(char s[], char n[]){
	int i = 0, j = 0;
	while(s[i] != '\0'){
		if(strpos(n, s[i]) == -1){
			s[j++] = s[i];
		}	
		i++;
	}
	s[j] = '\0';
	return 0;
}

int strpos(char s[], char needle){
	int i = 0, n = -1;
	while(s[i] != '\0'){
		if(s[i] == needle){
			n = i;
		}
		i++;
	}
	return n;
}
