#include <stdio.h>
void histogram(int word[]);
void vhistogram(int word[]);
int main(){
	int wordLength[30];
	int wl = 0, i, j;
	char c;
	for(i = 0; i < 30; i++) wordLength[i] = 0;
    while((c = getchar()) != EOF){
		if(c == '\n' || c == ' ' || c == '\t'){
			if(wl > 0){
				wordLength[wl]++;
				wl = 0;
			}
		}else{
			wl++;	
		}
	}
	histogram(wordLength);
	vhistogram(wordLength);
}
//horizontal histogram
void histogram(int word[]){
	int i, j, wl;
	for(i = 0; i < 30; i++){
		wl = word[i];
		if(wl == 0) continue;
		printf("%d=", i);
		for(j= 0; j < wl; j++) printf("#");
		printf("\n");
	}
}
//vertical histogram
void vhistogram(int word[]){
    int i, j, max = 0;
    for(i = 0; i < 30; i++){
        if(word[i] > max){
            max = word[i];
        }
    }
	while(max > 0){
        for(j = 0; j < 30; j++){
			if(word[j] == 0) continue;
			printf("%3s", word[j] >= max ? "#" : " ");
        }
		printf("\n");
		max--;
    }
	
    for(i = 0; i < 30; i++){
		if(word[i] == 0) continue;
        printf("%3d", i);
    }
	printf("\n");
}
