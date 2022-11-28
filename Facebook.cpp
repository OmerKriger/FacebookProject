#include <iostream>
using namespace std;
#include "Facebook.h"
#define MATCH 0


Facebook::Facebook()
{
	lSizeMembers = lSizeFanPages = pSizeFanPages = pSizeMembers = 0;
	members = nullptr;
	fanPages = nullptr;
}

Facebook::~Facebook()
{
	for (int i = 0; i < lSizeFanPages; i++)
		delete fanPages[i];
	delete[] fanPages;
	for (int i = 0; i < lSizeFanPages; i++)
		delete members[i];
	delete[] members;
}

void Facebook::__Init__()
{
	createMember("Omer Kriger", 10, 5, 1998);
	createMember("Nir Peretz", 9, 8, 1997);
	createMember("Mark Zuckerberg", 14, 5, 1984);
	createFanPage("Eduardo Saverin");
	createFanPage("Nike");
	createFanPage("Google");
	// need add init for status and connections to friends and pages
}

bool Facebook::addSpaceForMembers() 
{
	int newSize;
	if (pSizeMembers == 0)
		newSize = 1;
	else
		newSize = pSizeMembers * 2;
	Member** pNewMembers = new Member* [newSize];
	if (checkAllocate(pNewMembers) == false)
		return false;
	if (members != nullptr)
	{
		for (int i = 0; i < lSizeMembers; i++)
			pNewMembers[i] = members[i];
		delete[] members;
	}
	members = pNewMembers;
	pSizeMembers = newSize;
	return true;
}

bool Facebook::addSpaceForFanPages() 
{
	int newSize;
	if (pSizeFanPages == 0)
		newSize = 1;
	else
		newSize = pSizeFanPages * 2;
	Page** pNewPages = new Page * [newSize];
	if (checkAllocate(pNewPages) == false)
		return false;
	if (fanPages != nullptr)
	{
		for (int i = 0; i < lSizeFanPages; i++)
			pNewPages[i] = fanPages[i];
		delete[] fanPages;
	}
	fanPages = pNewPages;
	pSizeFanPages = newSize;
	return true;
}

bool Facebook::createMember(const char* name, int day, int month, int year) 
{
	if (memberNameCheck(name) == true)
	{
		cout << "This name already exist in the system" << endl;
		return false;
	}
	Date bday(day, month, year);
	Member* pMember = new Member(name, bday);
	if (pSizeMembers <= lSizeMembers)
		if (addSpaceForMembers() == false)
			return false;
	members[lSizeMembers] = pMember;
	lSizeMembers++;
	return true;
}

bool Facebook::memberNameCheck(const char* name)
{
	for (int i = 0; i < lSizeMembers; i++)
		if (strcmp(members[i]->getName(), name) == MATCH)
			return true;
	return false;
}

bool Facebook::createFanPage(const char* name) 
{
	if (pageNameCheck(name) == true)
	{
		cout << "This name already exist in the system" << endl;
		return false;
	}
	Page* pPage = new Page(name);
	if (pSizeFanPages <= lSizeFanPages)
		if (addSpaceForFanPages() == false)
			return false;
	fanPages[lSizeFanPages] = pPage;
	lSizeFanPages++;
	return true;
}

bool Facebook::pageNameCheck(const char* name)
{
	for (int i = 0; i < lSizeFanPages; i++)
		if (strcmp(fanPages[i]->getName(), name) == MATCH)
			return true;
	return false;
}

void Facebook::showAllMembers() const 
{
	cout << "-------- All Members in Facebook: --------" << endl;
	for (int i = 0; i < lSizeMembers; i++)
		cout << "Member #" << i+1 << " Name: " << members[i]->getName() << endl;
	cout << "----------- End of Member List -----------" << endl << endl;
}

void Facebook::showAllPages() const 
{
	cout << "--------- All Pages in Facebook: ---------" << endl;
	for (int i = 0; i < lSizeFanPages; i++)
		cout << "Fan Page #" << i + 1 << " Name: " << fanPages[i]->getName() << endl;
	cout << "---------- End of Fan Page List ----------" << endl << endl;
}

Member& Facebook::getMember(const char* name)
{
	for (int i = 0; i < lSizeMembers; i++)
		if (strcmp(name, members[i]->getName()) == MATCH)
			return *(members[i]);
}
const Member& Facebook::getMember(const char* name) const
{
	for (int i = 0; i < lSizeMembers; i++)
		if (strcmp(name, members[i]->getName()) == MATCH)
			return *(members[i]);
}

const Page& Facebook::getPage(const char* name) const
{
	for (int i = 0; i < lSizeFanPages; i++)
		if (strcmp(name, fanPages[i]->getName()) == MATCH)
			return *fanPages[i];
}
Page& Facebook::getPage(const char* name)
{
	for (int i = 0; i < lSizeFanPages; i++)
		if (strcmp(name, fanPages[i]->getName()) == MATCH)
			return *fanPages[i];
}
