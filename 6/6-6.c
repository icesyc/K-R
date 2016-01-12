/**
 * 以本节介绍的函数为基础，编写一个适合C语言程序使用的#define处理器的简单版本（即无参数的情况）。你会发现getch和ungetch函数非常有用。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 1000
#define MAXWORD 1000
typedef struct nlist{
	char *name;
	char *defn;
	nlist *next;

} nlist;
nlist *hashtable[HASHSIZE];
unsigned hash(char *s);
nlist *install(char *name, char *defn);
nlist *lookup(char *name);
int undef(char *name);
void getdef();
void error(char c, char *s);
int getword(char *word, int lim);
char getch();
void ungetch(char c);
void ungets(char *s);
void skipblanks();
int main(){
	char w[MAXWORD];
	nlist *p;
	while(getword(w, MAXWORD) != EOF){
		if(strcmp(w, "#") == 0){
			getdef();
		}else if(!isalpha(w[0])){
			printf("%s", w);
		}else if((p = lookup(w)) == NULL){
			printf("%s", w);
		}else{
			printf("%s", p->defn);
		}
	}
	return 0;
}

unsigned hash(char *s){
	unsigned val = 0;
	while(*s){
		val = val * 31 + *s++;
	}
	return val %HASHSIZE;
}
nlist *install(char *name, char *defn){
	nlist *p = lookup(name);
	if(p == NULL){
		unsigned hashval = hash(name);
		p = (nlist *)malloc(sizeof(nlist));
		p->name = (char *)malloc(strlen(name)+1);
		strcpy(p->name, name);
		p->next = hashtable[hashval];
		hashtable[hashval] = p;
	}else{
		free((void *)p->defn);
	}
	p->defn = (char *)malloc(strlen(defn)+1);
	strcpy(p->defn, defn);
	return p;
}
nlist *lookup(char *name){
	nlist *p = hashtable[hash(name)];
	while(p != NULL){
		if(strcmp(p->name, name) == 0){
			return p;
		}
		p = p->next;
	}
	return NULL;
}
int undef(char *name){
	nlist *p = hashtable[hash(name)];
	nlist *prev = NULL;
	while(p != NULL){
		if(strcmp(p->name, name) == 0){
			break;
		}
		prev = p;
		p = p->next;
	}
	if(p == NULL){
		return 0;
	}
	if(prev == NULL){
		hashtable[hash(name)] = p->next;
	}else{
		prev->next = p->next;
	}
	free((void *)p->name);
	free((void *)p->defn);
	free((void *)p);
	return 1;
}
void getdef(){
	char c;
	char dir[MAXWORD], name[MAXWORD], defn[MAXWORD];
	skipblanks();
	c = getword(dir, MAXWORD);
	if(!isalpha(dir[0])){
		error(c, "getdef: expecting a directive after #");
	}
	if(strcmp(dir, "define") == 0){
		skipblanks();
		c = getword(name, MAXWORD);
		if(!isalpha(name[0])){
			error(c, "getdef: non-alpha - name expected");
		}else{
			skipblanks();
			int i;
			for(i = 0; i < MAXWORD - 1; i++){
				defn[i] = getch();
				if(defn[i] == '\n' || defn[i] == EOF){
					break;
				}
			}
			defn[i] = '\0';
			if(i == 0){
				error(c, "getdef: non-alpha - incompleted define");
			}else{
				install(name, defn);
			}
		}
	}else if(strcmp(dir, "undef") == 0){
		skipblanks();
		c = getword(name, MAXWORD);
		if(!isalpha(c)){
			error(c, "getdef: non-alpha - in undef");
		}else{
			undef(name);
		}
	}else{
		//error(c, "getdef: expecting a directive after #");
	}
}
void error(char c, char *s){
	printf("%s\n", s);
	while(c != EOF && c != '\n'){
		c = getch();
	}
}
int getword(char *word, int lim){
	char *w = word;
	char c, nc;
	c = getch();
	if(c != EOF){
		*w++ = c;
	}
	if(isalpha(c) || c == '_'){
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
				*w++ = c;
				*w++ = nc;
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
void skipblanks(){
	char c;
	while((c = getch()) == ' ' || c == '\t');
	ungetch(c);
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
void ungets(char *s){
	int len = strlen(s);
	while(len > 0){
		ungetch(s[--len]);
	}
}
