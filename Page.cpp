#include <iostream>
#include "Page.h"
using namespace std;
#define MATCH 0
#define NOT_FOUND -1

// C'tors

Page::Page(const string& name) : Entity(name)
{}

Page::~Page()
{
	list<Status*>::iterator itr = wall.begin();
	list<Status*>::iterator itrEnd = wall.end();
	for (; itr != itrEnd; ++itr)
	{
		delete (*itr);
	}
}

// Add / Remove

void Page::addConnection(Entity* member)
{
	if (member == nullptr)
		throw PageException("This member doesn't exist ", PageException::pageErrorList::NOT_FOLLOW);
	list<Entity*>::iterator itrOfFan = find(connections.begin(), connections.end(), member);
	if (itrOfFan != connections.end())
		throw PageException("This member already follows the page. ", PageException::pageErrorList::ALREADY_FOLLOWED);
	connections.push_back(member);
}

void Page::removeConnection(Entity* member)
{
	list<Entity*>::iterator itrOfFan = find(connections.begin(), connections.end(), member);
	if (itrOfFan == connections.end())
		throw PageException("The member is not a fan so we can't remove him. ", PageException::pageErrorList::NOT_FOLLOW);
	connections.erase(itrOfFan);
}

void Page::addStatus(const string& str)
{
	try
	{
		Status* status = new Status(str, this->getName());
		wall.push_back(status);
	}
	catch (StatusException& e)
	{
		throw e;
	}
}

// Prints

void Page::showFans() const
{
	list<Entity*>::const_iterator itr = connections.begin();
	list<Entity*>::const_iterator itrEnd = connections.end();
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
	{ 
		// print all status
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
/*
void Page::setName(const string& str)
{
	if (name.empty() == false)
		throw PageException("Name can't be changed after has been setted ! ", PageException::pageErrorList::NAME_SETTED);
	if (str.size() <= 1)
		throw PageException("Name is too short ! ", PageException::pageErrorList::ILLEGAL_NAME);
	name = str;
}
*/

// Operators

bool Page::operator<(const Page& other) const
{
	return this->connections.size() < other.connections.size();
}

bool Page::operator>(const Page& other) const
{
	return this->connections.size() > other.connections.size();

}

bool Page::operator<(const Member& other) const
{
	return other < (*this); // based on operator< from member
}

bool Page::operator>(const Member& other) const
{
	return other < (*this); // based on operator> from member
}



