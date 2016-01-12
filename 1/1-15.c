#include <stdio.h>
void tempTransform(int upper, int step);
int main(){
    int step = 20;
    int upper = 200;
	tempTransform(upper, step);
}
void tempTransform(int upper, int step){
    printf("%7s\t%4s\n", "celsius", "fahr");
	int celsius = 0;
	float fahr = 0;
    while(celsius <= upper){
		fahr = celsius * 9.0 / 5.0 + 32;
		printf("%3d\t%6.1f\n", celsius, fahr);
		celsius += step;
	}
}
