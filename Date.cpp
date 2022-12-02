#pragma warning(disable : 4996)
#include <iostream>
using namespace std;
#include "Date.h"

Date::Date()
{
	/// <summary>
	/// Constractor for Date default with time of when it created
	/// </summary>
	time_t now = time(NULL);
	struct tm nowLocal;
	localtime_s(&nowLocal,&now);
	this->day = nowLocal.tm_mday;
	this->month = nowLocal.tm_mon + 1;
	this->hours = nowLocal.tm_hour;
	this->minutes = nowLocal.tm_min;
	this->year = nowLocal.tm_year + 1900;	
}
Date::Date(int day, int month, int year)
{
	/// <summary>
	/// Constractor for Date with only date that given
	/// </summary>
	this->day = day;
	this->month = month;
	this->year = year;
	this->minutes = 00;
	this->hours = 00;
}
Date::Date(int day, int month, int year, int minutes, int hours)
{
	/// <summary>
	/// Constractor for Date with full date given with time
	/// </summary>
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