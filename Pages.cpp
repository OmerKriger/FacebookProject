#include "Page.h"
#include "Member.h"
#include "supportFunctions.h"
#include <iostream>
using namespace std;
#include "supportFunctions.h"
Page::Page(const char* name)
{
	this->name = _strdup(name);
	logSizeWall = logSizeFans = phySizeFans = phySizeWall = 0;
	fans = nullptr;
	wall = nullptr;
}

bool Page::addFan(Member* Friend) { return 0; }
bool Page::searchFan(char* name) { return 0; }
bool Page::removeFan(char* name) { return 0; }
void Page::showFans() const { }
bool Page::addStatus() { return 0; }

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
