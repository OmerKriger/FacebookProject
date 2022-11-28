#include <iostream>
using namespace std;
#include "Date.h"

Date::Date() // can't delete for some reason the build won't work
{
	this->day = 07;
	this->month = 01;
	this->year = 2022;
	this->minutes = 00;
	this->hours = 00;
	// default date from now
}
Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
	this->minutes = 00;
	this->hours = 00;
}
Date::Date(int day, int month, int year, int minutes, int hours)
{
	this->day = day;
	this->month = month;
	this->year = year;
	this->minutes = minutes;
	this->hours = hours;
}
bool Date::setDate(int day, int month, int year) 
{
	if (!setYear(year))
		return false;
	if (!setMonth(month))
		return false;
	if (!setDay(day))
		return false;
	return true;
}
bool Date::setDay(int day) 
{
	if (day < 1 || 31 < day)
		return false;
	if (day == 31 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11))
		return false;
	if (day == 30 && month == 2)
		return false;
	this->day = day;
	return true;
}
bool Date::setMonth(int month)
{
	if (month < 1 || 12 < month)
		return false;
	this->month = month;
	return true;
}
bool Date::setYear(int year)
{
	if (year < 1)
		return false;
	this->year = year;
	return true;
}