#include <stdio.h>
int htoi(char s[]);
int main(){
	printf("%d\n", htoi("0xff"));
	printf("%d\n", htoi("0X80"));
	printf("%d\n", htoi("7f"));
}

int htoi(char s[]){
	int i, n;
	char c;
	i = 0;
	if(s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) i += 2;
	while(s[i] != '\0'){
		if(s[i] >= '0' && s[i] <= '9'){
			c = s[i] - '0';
		}
		else if(s[i] >= 'a' && s[i] <= 'f'){
			c = s[i] - 'a' + 10;
		}
		else if(s[i] >= 'A' && s[i] <= 'F'){
			c = s[i] - 'A' + 10;
		}
		else {
			break;
		}
		n = n * 16 + c;
		i++;
	}
	return n;
}
