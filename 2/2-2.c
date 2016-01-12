#include <stdio.h>
int main(){
	char s[1000], c;
	int lim = 1000, i;
	for(i=0; i<lim-1; i++){
		if((c=getchar()) != '\n'){
			if(c !=EOF){
				s[i] = c;
			}
		}
	}
	printf("%s", s);
}
