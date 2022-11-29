#include <iostream>
using namespace std;
#include "Status.h"

Status::Status(const char* text, const char* name) : creator(name)
{
	this->statusType = sType::tText;
	setText(text, statusType);
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
	int len = strlen(this->text);
	cout << "--------- " << this->getCreator() << "'s Status Start ---------" << endl;
	cout << "| Date: " << date.getDay() << "." << date.getMonth() << "." << date.getYear() << endl;
	cout << "| Time: " << date.getHours() << ":" << date.getMin() << endl;
	cout << "| Text: ";
	for (int i = 0; i < len; i++)
		if (text[i] == '\n')
			cout << text[i] << "| ";
		else
			cout << text[i];
	cout << "---------------- Status End ----------------" << endl << endl;

}

const char* Status::getCreator() const
{
	return creator;
}