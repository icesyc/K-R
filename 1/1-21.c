#include <stdio.h>
int main(){
	int tab = 8, i = 0, s = 0;
	char c;
	while((c = getchar()) != EOF){
		if(c == '\n'){
			i = 0;
			s = 0;
			printf("\n");
			continue;
		}
		if(c == ' '){
			s++;
			i++;
			if(i % tab == 0){
				printf("\t");
				s = 0;
			}
			continue;
		}
		if(c == '\t'){
			s = 0;
			i = 0;
			printf("%c", c);
			continue;
		}
		while(s > 0){
			printf(" ");
			s--;
		}
		printf("%c", c);
		i++;
	}
	return 0;
}

