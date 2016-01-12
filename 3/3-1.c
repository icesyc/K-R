/**
 * 上在面有关折半查找的例子中,while循环语句内内执行了两次测试， 其实只要一次就够了
 * (代价是将更多的测试在循环外执行).重写该函数,使用在循环内部只执行一次测试.比较两种版本函数的运行时间.
 */
#include <stdio.h>
int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);
int main(){
	int v[] = {1,3,5,7,9,11};
	printf("pos=%d\n", binsearch(11, v, 6));
	printf("2pos=%d\n", binsearch2(11, v, 6));
	return 0;
}

int binsearch(int x, int v[], int n){
	int low, high, mid;
	low = 0;
	high = n - 1;
	while(low <= high){
		mid = (low + high) / 2;
		if(x > v[mid]){
			low = mid + 1;
		}else if(x < v[mid]){
			high = mid - 1;
		}else{
			return mid;
		}	
	}
	return -1;
}

int binsearch2(int x, int v[], int n){
	int low, high, mid, save;
	low = mid = 0;
	high = n - 1;
	while(low <= high && x != v[mid]){
		mid = (low + high) / 2;
		if(x > v[mid]){
			low = mid + 1;
		}else{
			high = mid - 1;
		}
	}
	return x == v[mid] ? mid : -1;
}
