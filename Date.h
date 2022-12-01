#ifndef __DATE_H
#define __DATE_H
#include <time.h>
class Date
{
	int day, month, year, minutes, hours;
	bool setDate(int day, int month, int year);
	bool setDay(int day);
	bool setMonth(int month);
	bool setYear(int year);
public:
	Date();
	Date(int day, int month, int year);
	Date(int day, int month, int year, int minutes, int hours);
	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }
	int getMin() { return minutes; }
	int getHours() { return hours; }
};
#endif
