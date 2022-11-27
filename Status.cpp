#include "Status.h"
#include "supportFunctions.h"
#pragma warning(disable : 4996)

Status::Status(const char* text, sType statusType = sType::tText)
{
	this->statusType = sType::tText;
	if (statusType == sType::tText) // right now only text status
	{
		setText(text, statusType);
	}
	setDate();
}

Status::~Status()
{
	delete[] text;
}

bool Status::setDate() 
{
	time_t now = time(NULL);
	if (!now)
		return false;
	struct tm nowLocal;
	nowLocal = *localtime(&now);
	Date date(nowLocal.tm_mday, nowLocal.tm_mon + 1, nowLocal.tm_year + 1900, nowLocal.tm_min, nowLocal.tm_hour);
	this->date = date;
	return true;
}

/* for now through date
const char* Status::getTime() const
{
	return ;
}
*/
bool Status::setText(const char* str, sType type = sType::tText)
{
	if (text != nullptr)
	{
		cout << "Status Can't be change\n";
		return false;
	}
	else if (strlen(str) < 1)
	{
		cout << "Status can't be empty\n";
		return false;
	}
	else if (statusType != sType::tText)
	{
		cout << "This status Type isn't supported right now\n";
		return false;
	}
	else
	{
		text = _strdup(str);
		return checkAllocate(text);
	}

}

const char* Status::getText() const 
{
	return text;
}

const Date& Status::getDate() const
{
	return date;
}


void Status::showStatus()
{
	cout << "date: " << date.getDay() << "." << date.getMonth() << "." << date.getYear() << "\n";
	cout << "time: " << date.getHours() << ":" << date.getMin() << "\n";
	cout << "" << text;
}