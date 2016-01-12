#include <stdio.h>
#define IN 1
#define OUT 0
int main(){
	int i = 0;
    char c;
	char word[30];
	int state = OUT;

	while((c = getchar()) != EOF){
		if(c == ' ' || c == '\t' || c == '\n'){
			if(i > 0){
				word[i] = '\0';
        		printf("%s\n", word);
			}
			i = 0;
		}else{
			word[i++] = c;
		}
	}
}


