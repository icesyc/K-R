/**
 * 对程序entab和detab的功能做一些扩充,以接受下列缩写的命令:
 * entab -m +n 表示制表符从第m列开始,每隔n列停止.选择(对使用者而言)比较方便的默认行为.
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
	
	int start = 0, increment = 8;
	while(--argc > 0){
		char *arg = *++argv;
		if(arg[0] == '-'){
			start = atoi(++arg);
		}
		else if(arg[0] == '+'){
			increment = atoi(++arg);
		}
	}	
	for(pos = 0; pos < MAXLEN; pos++){
		if((pos - start) % increment  == 0){
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
