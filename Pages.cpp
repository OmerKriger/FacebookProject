#include <iostream>
using namespace std;
#include "Page.h"

#define NOT_FOUND -1
#define MATCH 0

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
	if (searchFan(member->getName()))
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
	if (phySizeFans == 0)
		newSize = 1;
	else
		newSize = phySizeFans * 2;
	Member** pNewFans = new Member * [newSize];
	if (checkAllocate(pNewFans) == false)
		return false;
	if (fans != nullptr)
		for (int i = 0; i < logSizeFans; i++)
			pNewFans[i] = fans[i];
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
	if (wall != nullptr)
		for (int i = 0; i < logSizeWall; i++)
			pNewWall[i] = wall[i];
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
	for (int i = 0; i <= logSizeFans; i++)
		cout << "Fan #" << i + 1 << ": " << fans[i]->getName() << endl;
	cout << "---- End of Fan List ----" << endl << endl;
}
bool Page::addStatus(const char* str)
{
	Status* status = new Status(str, sType::tText);
	if (phySizeWall <= logSizeWall + 1)
		if (addSpaceInWall() == false)
			return false;
	wall[logSizeWall] = status;
	logSizeFans++;
	return true;
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
