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
Date::Date(std::ifstream& inFile)
{
	inFile.read((char*)this, sizeof(*this));
}
Date::Date(int day, int month, int year) noexcept(false)
{
	/// <summary>
	/// Constractor for Date with only date that given
	/// </summary>
	try 
	{
		this->day = UNDEFINED, this->month = UNDEFINED, this->year = UNDEFINED;
		setYear(year);
		setMonth(month);
		setDay(day);
		this->minutes = 00;
		this->hours = 00;
	}
	catch (DateException& e)	
	{
		throw e;
	}
}
Date::Date(int day, int month, int year, int minutes, int hours)
{
	/// <summary>
	/// Constractor for Date with full date given with time
	/// </summary>
	try
	{
		this->day = UNDEFINED, this->month = UNDEFINED, this->year = UNDEFINED, this->minutes = UNDEFINED, this->hours = UNDEFINED;
		setYear(year);
		setMonth(month);
		setDay(day);
		setMinutes(minutes);
		setHour(hours);
	}
	catch (DateException& e)
	{
		throw e;
	}
}
void Date::save(std::ofstream& outFile) const
{
	outFile.write((const char*)this, sizeof(*this));
}
void Date::setDate(int day, int month, int year) 
{
	try
	{
		setYear(year);
		setMonth(month);
		setDay(day);
	}
	catch (DateException& e)
	{
		throw e;
	}
}
void Date::setHour(int hour)
{
	if (hour < HOUR_MIN || HOUR_MAX < hour)
		throw DateException("Hour value can be set between 00 to 23 ");
	else
		this->hours = hour;
}
void Date::setMinutes(int mins)
{
	if (mins < MINS_MIN || MINS_MAX < mins)
		throw DateException("Minutes value can be set between 00 to 59 ");
	else
		this->minutes = mins;
}
void Date::setDay(int day) 
{
	if (day < DAY_MIN || DAY_MAX < day)
		throw DateException("Day value can be set between 1 to 31 ");
	if (day == DAY_MAX && (month == FEB || month == APR || month == JUN || month == SEP || month == NOV))
		throw DateException("There is no date on the 31st of this month ");
	if (day == FEB30 && month == FEB)
		throw DateException("There is no date 30 in the month of February ");
	if (year % 4 != 0 && month == FEB && day == FEB29) // if year divide by four and month febuary so there is 29 in feb and date is legal
		throw DateException("There is no date 29 in the month of February in this year ");
	this->day = day;
}
void Date::setMonth(int month)
{
	if (month < 1 || 12 < month)
		throw DateException("Month value can be set between 1 to 12 ");
	this->month = month;
}
void Date::setYear(int year)
{
	if (year < 1)
		throw DateException("Year value can be only positive number ");
	this->year = year;
}
bool Date::isDefined() const
{
	return (year != UNDEFINED) && (month != UNDEFINED) && (day != UNDEFINED) && (hours != UNDEFINED) && (minutes != UNDEFINED);
}
