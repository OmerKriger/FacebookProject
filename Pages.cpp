#include "Page.h"
#include "Member.h"
#include "supportFunctions.h"
#include <iostream>
using namespace std;

bool Page::addFan(Member* Friend) {}
bool Page::searchFan(char* fName) {}
bool Page::removeFan(char* fName) {}
bool Page::showFans() {}
bool Page::addStatus() {}

bool Page::setName(char* str)
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
const char* Page::getName() 
{
	return name;
}
