#include <iostream>
using namespace std;
#include "Status.h"

Status::Status(const char* text, const char* name) : creator(name)
{
	this->statusType = sType::tText;
	setText(text, statusType);
}

Status::~Status()
{
	delete[] text;
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
	/// <summary>
	/// The function show individual status and print the time and date created
	/// and the text of this status
	/// </summary>
	int len = strlen(this->text);
	cout << "--------- " << this->getCreator() << "'s Status ------------------" << endl; // header
	cout << "| Date: " << date.getDay() << "." << date.getMonth() << "." << date.getYear() << endl; // print the date and time
	cout << "| Time: " << date.getHours() << ":" << date.getMin() << endl;
	cout << "| Text: "; // here starting print the text of status
	for (int i = 0; i < len; i++) // for loop run on the text and when print \n after it print "| " for the design
		if (text[i] == '\n')
			cout << text[i] << "| ";
		else
			cout << text[i];
	cout << endl << "--------------------------------------------------" << endl << endl; // bottom of status

}

const char* Status::getCreator() const
{
	return creator;
}