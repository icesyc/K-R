#include <stdio.h>
int main(){
	float celsius;
    int lower, upper, step, fahr;
    step = 20;
    upper = 300;
    fahr = 0;
    printf("%3s\t%6s\n", "fahr", "celsius");
    while(fahr < upper){
		celsius = (fahr - 32) * 5.0 / 9.0;
    	printf("%3d\t%6.1f\n", fahr, celsius);
        fahr += step;
    }
}
