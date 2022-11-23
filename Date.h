#ifndef __DATE_H
#define __DATE_H
#include <time.h>
class Date
{
	int day, month, year;
public:
	Date() = delete;
	Date(int day, int month, int year);
	bool setDate(int day,int month,int year);
	bool setDay(int day);
	bool setMonth(int month);
	bool setYear(int year);
	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }
};

#endif
