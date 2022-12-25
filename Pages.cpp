#include <iostream>
#include "Page.h"
using namespace std;
#define MATCH 0
#define NOT_FOUND -1

// C'tors
Page::Page(const string& name)
{
	this->name = name;
}
Page::~Page()
{
	list<Status*>::iterator itr = wall.begin();
	list<Status*>::iterator itrEnd = wall.end();
	for (;itr!=itrEnd; ++itr)
		delete (*itr);
}
// Add / Remove
bool Page::addFan(Member* member)
{
	if (member == nullptr)
		return false;
	list<Member*>::iterator itrOfFan = find(fans.begin(), fans.end(), member);
	if (itrOfFan != fans.end())
		return false;
	fans.push_back(member);
	return true;
}
bool Page::removeFan(Member* member)
{
	list<Member*>::iterator itrOfFan = find(fans.begin(), fans.end(), member);
	if (itrOfFan == fans.end())
		return false;
	fans.erase(itrOfFan);
	return true;
}
bool Page::addStatus(const string & str)
{
	wall.push_back(new Status(str, this->getName()));// create new status with the string sent // change after we put string in status and merge vector.
	return true;
}
// Prints
void Page::showFans() const
{
	list<Member*>::const_iterator itr = fans.begin();
	list<Member*>::const_iterator itrEnd = fans.end();
	cout << "The Fan List of Page " << name << ":" << endl;
	for (int i=0; itr!=itrEnd; ++itr, ++i)
		cout << "Fan #" << i + 1 << ": " << (*itr)->getName() << endl;
	cout << "---- End of Fan List ----" << endl << endl;
}
void Page::showPageStatus() const
{
	if (wall.size() == 0)
	{
		cout << "System: " << this->getName() << " has no Status." << endl << endl;
		return;
	}
	list<Status*>::const_iterator itr = wall.begin();
	list<Status*>::const_iterator itrEnd = wall.end();
	cout << "-------- All Status of Page " << this->getName() << " --------" << endl; // announcement for start print status
	for(int i=0; itr!= itrEnd; ++itr, ++i)
	{// print all status
		Date date = (*itr)->getDate();
		cout << "Status " << i + 1 << "# : " << (*itr)->getText() << " || ";
		cout << date.getDay() << "." << date.getMonth() << "." << date.getYear() << " ";
		if (date.getHours() < 10)
			cout << "0";
		cout << "" << date.getHours() << ":";
		if (date.getMin() < 10)
			cout << "0";
		cout << "" << date.getMin() << endl;
	}
	cout << "----------- End of Status List of " << this->getName() << " -----------" << endl << endl; // announcement for end print status
}
// Setters / Getters
bool Page::setName(const string& str)
{
	if (name.empty() == false)
	{
		cout << "Name can't be change !\n";
		return false;
	}
	else if (str.size() < 1) // maybe <=
	{
		cout << "Name is too short !\n";
		return false;
	}
	else
	{
		name = str;
		return true;
	}
}
const string& Page::getName() const
{
	return name;
}
int Page::getSizeOfFans() const
{
	return fans.size();
}

// Operators
bool Page::operator<(const Page& other) const
{
	return this->fans.size() < other.fans.size();
}
bool Page::operator>(const Page& other) const
{
	return this->fans.size() > other.fans.size();

}
bool Page::operator<(const Member& other) const
{
	return other < (*this); // based on operator< from member
}
bool Page::operator>(const Member& other) const
{
	return other < (*this); // based on operator> from member
}

