/**
 * 上述getword函数不能正确处理下划线,字符串常量,注释及预处理器控制指令.请编写一个更完善的getword函数.
 */
#include <stdio.h>
#include <ctype.h>

int getword(char *word, int lim);
char getch();
void ungetch(char c);

int main(int argc, char *argv[]){
	char w[100];
	getword(w, 100);
	printf("%s\n", w);
	return 0;
}

int getword(char *word, int lim){
	char *w = word;
	char c, nc;
	while(isspace(c = getch()));
	if(c != EOF){
		*w++ = c;
	}
	if(isalpha(c) || c == '_' || c == '#'){
		while(--lim > 0){
			c = getch();
			if(!isalnum(c) && c != '_'){
				ungetch(c);
				break;
			}
			*w++ = c;
		}
	}else if(c == '\'' || c == '\"'){
		while(--lim > 0){
			nc = getch();
			*w++ = nc;
			if(nc == '\\'){
				*w++ = getch();
				continue;
			}
			if(nc == c || nc == EOF){
				break;
			}
		}
	}else if(c == '/'){
		if((nc = getch()) == '*'){
			while((c = getch())){
				nc = getch();
				if(c == '*' && nc == '/'){
					break;
				}else{
					ungetch(nc);
				}
			}
			c = nc;
		}else{
			ungetch(nc);
		}
	}
	*w = '\0';
	return c;
}

 char buff[100];
 int bp = 0;
 char getch(){
     return bp > 0 ? buff[--bp] : getchar();
 }
 void ungetch(char c){
     if(bp < 100){
         buff[bp++] = c;
     }
 }
