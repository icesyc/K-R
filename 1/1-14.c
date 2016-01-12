#include <stdio.h>
void histogram(int word[]);
int main(){
	int chr[128];
	char c;
	for(int i = 0; i < 128; i++) chr[i] = 0;
 	while((c = getchar()) != EOF){
		chr[c]++;
	}
	histogram(chr);
	return 0;
}

void histogram(int word[]){
	int chr, len;
  	for(int i = 0; i < 128; i++){
		len = word[i];	
		if(len == 0) continue;
		if(i == '\t'){
			printf("\\t=%d", len);
		}else if(i == '\n'){
			printf("\\n=%d", len);
		}else{
			printf("%c=%d", i, len);
		}
		while(len-- > 0) printf("#");
		printf("\n");
	}
}
