#ifndef __DATE_H
#define __DATE_H
#include <time.h>
#include <fstream>
#include "Exceptions.h"

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
	void setDate(int day, int month, int year) noexcept(false);
	void setDay(int day) noexcept(false);
	void setMonth(int month) noexcept(false);
	void setYear(int year) noexcept(false);
	void setHour(int hour) noexcept(false);
	void setMinutes(int mins) noexcept(false);
public:
	Date();
	Date(std::ifstream& inFile);
	Date(int day, int month, int year) noexcept(false);
	Date(int day, int month, int year, int minutes, int hours) noexcept(false);
	void save(std::ofstream& outFile)	const;
	const int& getDay() const { return day; }
	const int& getMonth() const { return month; }
	const int& getYear() const { return year; }
	const int& getMin() const { return minutes; }
	const int& getHours() const { return hours; }
	bool isDefined() const;
};
#endif
