/**
 * 修改程序entab和detab(第1章练习中编写的函数),使它们接受一组作为参数的制表符停止位.
 * 如果启动程序时不带参数,则使用默认的制表符停止位设置.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 100
void settab(int argc, char *argv[]);
void detab();
void entab();
int main(int argc, char *argv[]){
	settab(argc, argv);
	detab();
	//entab();
}
int tab[MAXLEN];

void settab(int argc, char *argv[]){
	int pos;
	for(pos = 0; pos < MAXLEN; pos++){
		tab[pos] = 0;
	}
	if(argc < 2){
		for(pos = 0; pos < MAXLEN; pos++){
			if(pos % 8 == 0){
				tab[pos] = 1;
			}
		}
		return;
	}
	while(--argc > 0){
		pos = atoi(*++argv);
		if(pos > 0 && pos < MAXLEN){
			tab[pos] = 1;
		}
	}	
}
void detab(){
	int i = 1;
	char c;
	while((c = getchar()) != EOF){
		if(c == '\n'){
			i = 1;
			printf("%c", c);
			continue;
		}
		else if(c == '\t'){
			do{
				printf("%c", '#');
			}
			while(tab[i++] != 1);
			continue;
		}
		printf("%c", c);
		i++;

	}
}

void entab(){
    int i = 1, s = 0;
    char c;
    while((c = getchar()) != EOF){
        if(c == '\n'){
            i = 1;
            s = 0;
            printf("\n");
            continue;
        }   
        if(c == ' '){
            s++;
            if(tab[i++] == 1){ 
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
}
