/**
 * 函数day_of_year和month_day中没有进行错误检查,请解决该问题.
 */
#include <stdio.h>
int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);
static char mon[2][13] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int main(){
	int m, d;
	int dy = day_of_year(2015, 4, 31);
	month_day(2015, 560, &m, &d);
	printf("%d, %d, %d\n", dy, m, d);
	return 0;
}


int day_of_year(int year, int month, int day){
	int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	if(month < 1 || month > 12 || day < 1 || day > mon[leap][month]){
		return -1;
	}
	for(int i = 1; i < month;  i++){
		day += mon[leap][i];		
	}
	return day;	
}

int month_day(int year, int yearday, int *pmonth, int *pday){
	int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	int i;
	for(i = 1; i < 13 && yearday > mon[leap][i]; i++){
		yearday -= mon[leap][i];
	}
	if(i > 12){
		*pmonth = -1;
		*pday = -1;
		return -1;
	}
	*pmonth = i;
	*pday = yearday;
	return 0;
}
