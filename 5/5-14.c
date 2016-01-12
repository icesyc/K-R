/**
 * 修改排序程序,使它能处理-r标记.该标记表明，以逆序(递减)方式排序.要保证-r和-n能够组合在一起使用.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1000
#define MAXLINE 100

void qsort2(void *v[], int left, int right, int (*comp)(void *, void *));
void swap(void *v[], int i, int j);
void getarg(int argc, char *argv[]);
int numcmp(char *a, char *b);
int getln(char *line, int max);
int readlines(char *lines[], int maxlines);

int num = 0;
int rev = 1;
int main(int argc, char *argv[]){
	int n;
	getarg(argc, argv);
	printf("num=%d, rev=%d\n", num, rev);
	int (*cmp)(void *, void *) = num == 1 ? numcmp : strcmp;
	char *lines[MAXLINE];
	n = readlines(lines, MAXLINE);
	qsort2(lines, 0, n-1, cmp);
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
			num = 1;	
		}
		else if(*arg == '-' && *(arg+1) == 'r'){
			rev = -1;	
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
		if((*comp)(v[i], mid) * rev < 0){
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
        i++;
        *s++ = c;
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
