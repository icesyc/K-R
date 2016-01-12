/**
 * 希尔排序
 */
#include <stdio.h>
int shell_sort(int v[], int n);
int main(){
	int v[11] = {1, 6, 39, 23, 56, 49, 50, 38, 10, 8, 66};
	shell_sort(v, 10);
	for(int i=0; i<10; i++){
		printf("%d", v[i]);
		printf("%c", i == 9 ? '\n' : ',');
	}
	return 0;
}

int shell_sort(int v[], int n){
	int i, j, gap, tmp;
	gap = n / 2;
	while(gap > 0){
		for(i = gap; i < n; i++){
			j = i - gap;
			//从i-gap开始,发现连续的元素有逆序则交换
			while(j >= 0 && v[j] > v[j+gap]){
				tmp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = tmp;
				j -= gap;
			}
		}	
		gap /= 2;
	}
	return 0;
}
