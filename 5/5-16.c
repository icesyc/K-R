/**
 * 增加选项-d(代表目录顺序).该选项表明,只对字母,数字和空格进行比较.要保证该选项可以和-f组合在一起使用.
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
int getln(char *line, int max);
int readlines(char *lines[], int maxlines);

int option = 0;
int main(int argc, char *argv[]){
	int n;
	getarg(argc, argv);
	int (*cmp)(void *, void *);
	cmp = option & NUMERIC ? numcmp : charcmp;
	char *lines[MAXLINE];
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
	char s, t;
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
