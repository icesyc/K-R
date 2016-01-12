/**
 * 增加字段处理功能,以使用排序程序可以根据行内的不同字段进行排序,每个字段按照一个单独的选项集合进行排序.
 * (在对本书索引进行排序时,索引条目使用了-df选项，而对页码排序时使用了-n选项.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 1000
#define MAXLINE 100
#define NUMERIC 1
#define REVERSE 2
#define FOLD 4
#define DIR 8

void qsort2(void *v[], int left, int right, int (*comp)(void *, void *));
void swap(void *v[], int i, int j);
void getarg(int argc, char *argv[]);
int numcmp(char *a, char *b);
int charcmp(char *a, char *b);
int fieldcmp(char *a, char *b);
int getln(char *line, int max);
int readlines(char *lines[], int maxlines);
//获取一行中的某个字段
int getfield(char *t, char *s, int n);

int option = 0;
int field = 0;
int main(int argc, char *argv[]){
	int n;
	int (*cmp)(void *, void *) = fieldcmp;
	char *lines[MAXLINE];
	getarg(argc, argv);
	n = readlines(lines, MAXLINE);
	qsort2(lines, 0, n-1, cmp);
	if(option & REVERSE)
		for(int i = n - 1; i > 0; i--){
			printf("%s", lines[i]);
		}
	else
		for(int i = 0; i < n; i++){
			printf("%s", lines[i]);
		}
	return 0;
}

void getarg(int argc, char *argv[]){
	char *arg;
	while(--argc > 0){
		arg = *++argv;
		if(*arg == '-' && *(arg+1) == 'n'){
			option |= NUMERIC;
		}
		else if(*arg == '-' && *(arg+1) == 'r'){
			option |= REVERSE;
		}
		else if(*arg == '-' && *(arg+1) == 'f'){
			option |= FOLD;
		}
		else if(*arg == '-' && *(arg+1) == 'd'){
			option |= DIR;
		}
		else if(*arg == '-' && *(arg+1) == 'k'){
			field = atoi(arg+2);
		}
	}
}
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *)){
	if(left >= right){
		return;
	}
	int last, i;
	void *mid = v[left];
	last = left;
	for(i = left+1; i <= right; i++){
		if((*comp)(v[i], mid) < 0){
			swap(v, i, ++last);
		}
	}
	swap(v, left, last);
	qsort2(v, left, last-1, comp);
	qsort2(v, last+1, right, comp);
}

void swap(void *v[], int i, int j){
	char *tmp;
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}
int numcmp(char *a, char *b){
	float f1, f2;
	f1 = atof(a);
	f2 = atof(b);
	if(f1 > f2){
		return 1;
	}else if(f1 < f2){
		return -1;
	}else{
		return 0;
	}
}
int getln(char *s, int max){
    char c;
    int i = 0;
    while((c = getchar()) != '\n' && c != EOF && i < max){
        *s++ = c;   
        i++;
    }   
	if(c == '\n'){
		*s++ = c;
		i++;
	}
	if(c == '\n' || c == EOF){
    	*s = '\0';
	}
    return i;   
}
int readlines(char *lines[], int maxlines){
	char line[MAXLEN];
	int len, n = 0;
	while((len = getln(line, MAXLEN)) > 0 && n < maxlines){
		lines[n] = malloc(len + 1);
		strcpy(lines[n], line);
		n++;
	}
	return n;
	
}
int charcmp(char *a, char *b){
	int fold = option & FOLD ? 1 : 0;
	int dir = option & DIR ? 1 : 0;
	int num = option & NUMERIC ? 1 : 0;
	char s, t;
	
	if(num){
		return numcmp(a, b);
	}	
	do{
		if(dir){
			while(!isalnum(*a) && *a != ' ' && *a != '\0') a++;
			while(!isalnum(*b) && *b != ' ' && *b != '\0') b++;
		}
		if(fold){
			s = tolower(*a);
			t = tolower(*b);
		}else{
			s = *a;
			t = *b;	
		}
		if(s == '\0' && s == t){
			return 0;
		}
		a++;
		b++;
	}while(s == t);
	return s - t;
}
int fieldcmp(char *a, char *b){
	char s1[MAXLEN], s2[MAXLEN];
	int n = field;
	if(n == 0){
		return charcmp(a, b);
	}
	getfield(s1, a, n);
	getfield(s2, b, n); 
	return charcmp(s1, s2);
}
int getfield(char *t, char *s, int n){
	int i = 1;
	while(*s){
		if(isspace(*s)){
			i++;
			while(isspace(*s)) s++;
		}
		if(i == n){
			while(!isspace(*s)) *t++ = *s++;
			*t = '\0';
			return i;
		}
		s++;
	}
	return -1;
}
