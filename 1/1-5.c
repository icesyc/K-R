#include <stdio.h>
int main(){
	float celsius;
    int upper, step, fahr;
    step = 20;
    upper = 300;
    printf("%3s\t%6s\n", "fahr", "celsius");
    while(upper >= 0){
		celsius = (upper - 32) * 5.0 / 9.0;
    	printf("%3d\t%6.1f\n", upper, celsius);
        upper -= step;
    }
}
