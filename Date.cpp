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
	this->day = UNDEFINED, this->month = UNDEFINED, this->year = UNDEFINED;
	setYear(year);
	setMonth(month);
	setDay(day);
	this->minutes = 00;
	this->hours = 00;
}
Date::Date(int day, int month, int year, int minutes, int hours)
{
	/// <summary>
	/// Constractor for Date with full date given with time
	/// </summary>
	this->day = UNDEFINED, this->month = UNDEFINED, this->year = UNDEFINED, this->minutes = UNDEFINED, this->hours = UNDEFINED;
	setYear(year);
	setMonth(month);
	setDay(day);
	setMinutes(minutes);
	setHour(hours);
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
bool Date::setHour(int hour)
{
	if (hour < HOUR_MIN || HOUR_MAX < hour)
		return false;
	else
		this->hours = hour;
	return true;

}
bool Date::setMinutes(int mins)
{
	if (mins < MINS_MIN || MINS_MAX < mins)
		return false;
	else
		this->minutes = mins;
	return true;
}
bool Date::setDay(int day) 
{
	if (day < DAY_MIN || DAY_MAX < day)
		return false;
	if (day == DAY_MAX && (month == FEB || month == APR || month == JUN || month == SEP || month == NOV))
		return false;
	if (day == FEB30 && month == FEB)
		return false;
	if (year % 4 != 0 && month == FEB && day == FEB29) // if year divide by four and month febuary so there is 29 in feb and date is legal
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
bool Date::isDefined() const
{
	return (year != UNDEFINED) && (month != UNDEFINED) && (day != UNDEFINED) && (hours != UNDEFINED) && (minutes != UNDEFINED);
}
