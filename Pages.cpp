#include <iostream>
using namespace std;
#include "Page.h"

#define MATCH 0
#define NOT_FOUND -1

Page::Page(const char* name)
{
	this->name = _strdup(name);
	logSizeWall = logSizeFans = phySizeFans = phySizeWall = 0;
	fans = nullptr;
	wall = nullptr;
}
Page::~Page()
{
	delete[]name;
	delete[]fans;
	for (int i = 0; i < logSizeWall; i++)
		delete wall[i];
	delete[]wall;
}

bool Page::addFan(Member* member)
{
	if (member == nullptr)
		return false;
	if (searchFan(member->getName()) != NOT_FOUND) // If member already follow this page
		return false;
	if (phySizeFans <= logSizeFans)
		if (addSpaceInFans() == false)
			return false;
	fans[logSizeFans] = member;
	logSizeFans++;
	return true;
}
bool Page::addSpaceInFans()
{
	int newSize;
	if (phySizeFans == 0) // check if empty put 1 if not multyply by 2
		newSize = 1;
	else
		newSize = phySizeFans * 2;
	Member** pNewFans = new Member * [newSize]; // create new array
	if (checkAllocate(pNewFans) == false)
		return false;
	if (fans != nullptr) // if there are already array copy data to new one
	{
		for (int i = 0; i < logSizeFans; i++) // copy data from old array
			pNewFans[i] = fans[i];
		delete[] fans;
	}
	fans = pNewFans;
	phySizeFans = newSize;
	return true;
}
bool Page::addSpaceInWall()
{
	int newSize;
	if (phySizeWall == 0)
		newSize = 1;
	else
		newSize = phySizeWall * 2;
	Status** pNewWall = new Status * [newSize];
	if (checkAllocate(pNewWall) == false)
		return false;
	if (wall != nullptr) // if there are already array copy data to new one
	{
		for (int i = 0; i < logSizeWall; i++) // copy new data
			pNewWall[i] = wall[i];
		delete[] wall;
	}
	wall = pNewWall;
	phySizeWall = newSize;
	return true;
}
int Page::searchFan(const char* name)
{
	int index;
	for (index = 0; index < logSizeFans; index++)
		if (strcmp(name, fans[index]->getName()) == MATCH)
			return index;
	return NOT_FOUND;
}
bool Page::removeFan(const char* name)
{
	int index = searchFan(name);
	if (index == NOT_FOUND)
		return false;
	fans[index] = fans[logSizeFans - 1];
	logSizeFans--;
	return true;
}
void Page::showFans() const
{
	cout << "The Fan List of Page " << name << ":" << endl;
	for (int i = 0; i < logSizeFans; i++)
		cout << "Fan #" << i + 1 << ": " << fans[i]->getName() << endl;
	cout << "---- End of Fan List ----" << endl << endl;
}
bool Page::addStatus(const char* str)
{
	Status* status = new Status(str,this->getName()); // create new status with the string sent
	if (phySizeWall <= logSizeWall)
		if (addSpaceInWall() == false)
			return false;
	wall[logSizeWall] = status;
	logSizeWall++;
	return true;
}
void Page::showPageStatus() const
{
	if (logSizeWall == 0)
	{
		cout << "System: " << this->getName() << " has no Status." << endl << endl;
		return;
	}
	cout << "-------- All Status of Page " << this->getName() << " --------" << endl; // announcement for start print status
	for (int i = 0; i < logSizeWall; i++)
	{// print all status
		Date date = wall[i]->getDate();

		cout << "Status " << i + 1 << "# : " << wall[i]->getText() << " || ";
		cout << date.getDay() << "." << date.getMonth() << "." << date.getYear() << " " << date.getHours() << ":";
		int min = date.getMin();
		if (min < 10)
			cout << "0";
		cout << "" << min << endl;
	}
	cout << "----------- End of Status List of " << this->getName() << " -----------" << endl << endl; // announcement for end print status
}
bool Page::setName(const char* str)
{
	if (name != nullptr)
	{
		cout << "Name can't be change !\n";
		return false;
	}
	else if (strlen(str) < 1)
	{
		cout << "Name is too short !\n";
		return false;
	}
	else
	{
		name = _strdup(str);
		return checkAllocate(name);
	}
}
const char* Page::getName() const
{
	return name;
}
