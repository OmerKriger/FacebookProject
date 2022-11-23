#include "Status.h"
#include "supportFunctions.h"
#pragma warning(disable : 4996)
bool Status::setTime() 
{
	char* Test = ctime(&timestamp);
	cout << "Status Time set to " << timestamp << endl << "Test: " << Test << endl; // test after run can be removed
	if (Test == nullptr)
		return false;
	else
		return true;
}

const time_t& Status::getTime() const
{
	return time;
}

bool Status::setText(char* str, sType type = tText)
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
	else if (statusType != tText)
	{
		cout << "This status Type isn't support right now\n";
		return false;
	}
	else
	{
		text = _strdup(str);
		return checkAllocate(time);
	}

}

const char* Status::getText() const 
{
	return text;
}