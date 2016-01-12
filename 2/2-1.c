#include <stdio.h>
#include <limits.h>
#include <float.h>
void vrange();
void vrange2();

int main(){
	printf("----- limits.h -------\n");
	vrange();	
	printf("----- computed -------\n");
	vrange2();
	return 0;
}

void vrange(){
	printf("signed char min=%d\n", CHAR_MIN);
	printf("signed char max=%d\n", CHAR_MAX);
	printf("unsigned char max=%d\n", UCHAR_MAX);
	printf("signed short min=%d\n", SHRT_MIN);
	printf("signed short max=%d\n", SHRT_MAX);
	printf("unsigned short max=%d\n", USHRT_MAX);
	printf("signed int min=%d\n", INT_MIN);
	printf("signed int max=%d\n", INT_MAX);
	printf("unsigned int max=%u\n", UINT_MAX);
	printf("signed long min=%ld\n", LONG_MIN);
	printf("signed long max=%ld\n", LONG_MAX);
	printf("unsigned long max=%lu\n", ULONG_MAX);
	printf("float min=%f\n", FLT_MIN);
	printf("float max=%f\n", FLT_MAX);
}
void vrange2(){
	signed char sc, sc_min, sc_max;
	unsigned char uc, uc_max;
	signed short ss, ss_min, ss_max;
	unsigned short us, us_max;
	signed int si, si_min, si_max;
	unsigned int ui, ui_max;
	signed long sl, sl_min, sl_max;
	unsigned long ul, ul_max;
	
	sc = -1;
	while(sc < 0){
		sc = sc * 2;
		if(sc < 0) sc_min = sc;
	}
	
	sc = 1;
	while(sc > 0) sc = sc * 2;
	sc_max = sc - 1;

	uc = 1;
	while(uc > 0) uc = uc * 2;
	uc_max = uc - 1;

	ss = -1;
	while(ss < 0){
		ss = ss * 2;
		if(ss < 0) ss_min = ss;
	}

	ss = 1;
	while(ss > 0) ss = ss * 2;
	ss_max = ss - 1;

	si = -1;
	while(si < 0){
		si = si * 2;
		if(si < 0) si_min = si;
	}

	si = 1;
	while(si > 0) si = si * 2;
	si_max = si - 1;

	ui = 1;
	while(ui > 0) ui = ui * 2;
	ui_max = ui - 1;

	sl = -1;
	while(sl < 0){
		sl = sl * 2;
		if(sl < 0) sl_min = sl;
	}

	sl = 1;
	while(sl > 0) sl = sl * 2;
	sl_max = sl - 1;

	ul = 1;
	while(ul > 0) ul = ul * 2;
	ul_max = ul - 1;
	
	//compute float 
	float fa, fb, fc, fm, f_min, f_max;
	fa = 1.0;
	fb = 2.0;
	while(fa != fb){
		fm = fa;
		fa = fa * 2;
		fb = fa + 1.0;
	}	
	fm = fm + fm - 1;

	fa = fb = fc = fm;
	while(fb == fc){
		fc = fa;
		fa = fa * 2;
		fb = fa / 2;
	}		
	f_max = fc;
	
   	printf("signed char min=%d\n", sc_min);
    printf("signed char max=%d\n", sc_max);
    printf("unsigned char max=%d\n", uc_max);
    printf("signed short min=%d\n", ss_min);
    printf("signed short max=%d\n", ss_max);
    printf("unsigned short max=%d\n", us_max);
    printf("signed int min=%d\n", si_min);
    printf("signed int max=%d\n", si_max);
    printf("unsigned int max=%u\n", ui_max);
    printf("signed long min=%ld\n", sl_min);
    printf("signed long max=%ld\n", sl_max);
    printf("unsigned long max=%lu\n", ul_max);		
    printf("float max=%e\n", f_max);		
}
