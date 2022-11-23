#include "Status.h"
#include "supportFunctions.h"
#pragma warning(disable : 4996)

Status::Status(const char* text, sType statusType = sType::tText)
{
	if (statusType != sType::tText) // right now only text status
	{
		this->statusType = sType::tText;
		setText(text, statusType);
	}
	Date date;
	this->date = date;
	setTime();
}

Status::~Status()
{
	delete[] text;
}

bool Status::setTime() 
{
	char* Test = ctime(&time);
	cout << "Status Time set to " << time << endl << "Test: " << Test << endl; // test after run can be removed
	if (Test == nullptr)
		return false;
	else
		return true;
}

const time_t& Status::getTime() const
{
	return time;
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