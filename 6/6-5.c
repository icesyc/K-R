/**
 * 编写函数undef，它将从由lookup和install维护的表中删除一个变量名及其定义
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 1000
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

int main(){
	install("name", "1");
	install("test", "2");
	install("ice", "3");
	undef("name");
	nlist *p = lookup("name");
	printf("%s\n", p != NULL ? p->defn : "not found");
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
