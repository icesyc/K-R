#include <stdio.h>
int main(){
    float fahr;
    int celsius = 0;
    int step = 20;
    int upper = 200;
    printf("%7s\t%4s\n", "celsius", "fahr");
    while(celsius <= upper){
		fahr = celsius * 9.0 / 5.0 + 32;
		printf("%3d\t%6.1f\n", celsius, fahr);
		celsius += step;
	}
}
