/**
 * 用指针方式代替数组下标方式改写函数day_of_year和month_day
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
	int dy = day_of_year(2015, 5, 10);
	month_day(2015, 130, &m, &d);
	printf("%d, %d, %d\n", dy, m, d);
	return 0;
}


int day_of_year(int year, int month, int day){
	int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	char *p = mon[leap];
	if(month < 1 || month > 12 || day < 1 || day > mon[leap][month]){
		return -1;
	}
	while(--month){
		day += *++p;
	}
	return day;	
}

int month_day(int year, int yearday, int *pmonth, int *pday){
	int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	char *p = mon[leap];
	while(yearday > *++p){
		yearday -= *p;
	}
	*pmonth = p - mon[leap];
	*pday = yearday;
	if(*pmonth > 12){
		*pmonth = -1;
		*pday = -1;
		return -1;
	}
	return 0;
}
