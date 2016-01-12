#include <stdio.h>
#define IN 1
#define OUT 0
int main(){
	int nl, nw, nc;
	nl = nw = nc = 0;
	int state = OUT;
    char c;
	while((c = getchar()) != EOF){
		nc++;
		if(c == '\n'){
			nl++;
		}
		if(c == ' ' || c == '\n' || c == '\t'){
			state = OUT;	
		}
		else if(state == OUT){
			state = IN;
			nw++;
		}
	}
	printf("line=%d, word=%d, char=%d\n", nl, nw, nc);
}
