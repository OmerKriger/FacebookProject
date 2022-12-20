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
	bool setHour(int hour);
	bool setMinutes(int mins);
public:
	Date();
	Date(int day, int month, int year);
	Date(int day, int month, int year, int minutes, int hours);
	const int& getDay() const { return day; }
	const int& getMonth() const { return month; }
	const int& getYear() const { return year; }
	const int& getMin() const { return minutes; }
	const int& getHours() const { return hours; }
	bool isDefined() const;
};
#endif
