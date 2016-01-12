#include <stdio.h>
void repeat(int i, char c);
int main(){
	int tab = 8, i = 0, r = 0;
	char c;
	while((c = getchar()) != EOF){
		if(c == '\n'){
			i = 0;
			printf("%c", c);
			continue;
		}
		else if(c == '\t'){
			r = 8 - i % tab;	
			repeat(r, '#');
			i += r;
			continue;
		}
		printf("%c", c);
		i++;

	}
	return 0;
}

void repeat(int i, char c){
	while(i > 0){
		printf("%c", c);
		i--;
	}
}
