#include <stdio.h>
int main(){
    int c;
    while((c = getchar()) != EOF){
        printf("%c", c);
        if(c == '\n'){
			while((c = getchar()) == '\n');
			printf("%c", c);
	    }
    }
}
