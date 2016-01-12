/**
 * 编写函数strrindex(s,t),它返回字符串t在s中最右边出现的位置.如果s中不包含t,则返回-1
 */
#include <stdio.h>
int strrindex(char s[], char t[]);
int main(){
	char s[] = "this is a test is";
	char t[] = "is";
	int idx = strrindex(s, t);
	printf("%s in %s index = %d\n", t, s, idx);
	return 0;
}
int strrindex(char s[], char t[]){
	int i, j, k, idx = -1;
	for(i = 0; s[i] != '\0'; i++){
		for(j = i, k = 0; t[k] != '\0'; j++, k++){
			if(t[k] != s[j]) break;
		}
		if(k > 0 && t[k] == '\0'){
			idx = i;
		}
	}
	return idx;
}
