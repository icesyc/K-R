/**
 * 快速排序的实现
 */
#include <stdio.h>
void qsort(int v[], int left, int right);
void swap(int v[], int i, int j);
int main(){
	int v[] = {1, 20, 34, 56, 30, 50, 10, 63};
	qsort(v, 0, 7);
	for(int i = 0; i < 8; i++){
		printf("%d ", v[i]);
	}
	printf("\n");
}

void qsort(int v[], int left, int right){
	int last = left, i;
	if(left >= right){
		return;
	}
	swap(v, left, (left + right) / 2);
	for(i = left + 1; i <= right; i++){
		if(v[i] < v[left]){
			swap(v, i, ++last);	
		}
	}
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}
void swap(int v[], int i, int j){
	int tmp;
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}
