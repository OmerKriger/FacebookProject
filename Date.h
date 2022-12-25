#ifndef __DATE_H
#define __DATE_H
#include <time.h>

enum DateDefines
{
	UNDEFINED = -1,
	DAY_MIN = 1,
	DAY_MAX = 31,
	MONTH_MIN = 1,
	MONTH_MAX =12,
	HOUR_MAX = 23,
	HOUR_MIN = 0,
	MINS_MAX = 59,
	MINS_MIN = 0,
	FEB = 2,
	APR = 4,
	JUN = 6,
	SEP = 9,
	NOV = 11,
	FEB30 = 30,
	FEB29 = 29,
	DIV4 = 4,
};
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
