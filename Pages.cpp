#include <iostream>
using namespace std;
#include "Page.h"
#include "Member.h"
#include "Date.h"
#include "supportFunctions.h"
#define NOT_FOUND -1
#define MATCH 0
Page::Page(const char* name)
{
	this->name = _strdup(name);
	lSizeWall = lSizeFans = pSizeFans = pSizeWall = 0;
	fans = nullptr;
	wall = nullptr;
}
Page::~Page()
{
	delete[]name;
	delete[]fans;
	for (int i = 0; i < lSizeWall; i++)
		delete wall[i];
	delete[]wall;
}

bool Page::addFan(Member* member) 
{
	if (member == nullptr)
		return false;
	if (searchFan(member->getName()))
		return false;
	if (pSizeFans <= lSizeFans + 1)
		if (addSpaceInFans() == false)
			return false;
	fans[lSizeFans] = member;
	lSizeFans++;
	return true;
}
bool Page::addSpaceInFans()
{
	int newSize;
	if (pSizeFans == 0)
		newSize = 1;
	else
		newSize = pSizeFans * 2;
	Member** pNewFans = new Member * [newSize];
	if (checkAllocate(pNewFans) == false)
		return false;
	if (fans != nullptr)
		for (int i = 0; i < lSizeFans; i++)
			pNewFans[i] = fans[i];
	fans = pNewFans;
	pSizeFans = newSize;
	return true;
}
bool Page::addSpaceInWall()
{
	int newSize;
	if (pSizeWall == 0)
		newSize = 1;
	else
		newSize = pSizeWall * 2;
	Status** pNewWall = new Status * [newSize];
	if (checkAllocate(pNewWall) == false)
		return false;
	if (wall != nullptr)
		for (int i = 0; i < lSizeWall; i++)
			pNewWall[i] = wall[i];
	wall = pNewWall;
	pSizeWall = newSize;
	return true;
}
int Page::searchFan(const char* name) 
{
	int index;
	for (index = 0; index < lSizeFans; index++)
		if (strcmp(name, fans[index]->getName()) == MATCH)
			return index;
	return NOT_FOUND;
}
bool Page::removeFan(const char* name)
{
	int index = searchFan(name);
	if (index == NOT_FOUND)
		return false;
	fans[index] = fans[lSizeFans - 1];
	lSizeFans--;
}
void Page::showFans() const 
{
	cout << "The Fan List of Page " << name << ":" << endl;
	for (int i = 1; i <= lSizeFans; i++)
		cout << "Fan #" << i << ": " << fans[i]->getName() << endl;
	cout << "---- End of Fan List ----" << endl << endl;
}
bool Page::addStatus(const char* str) 
{ 

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
