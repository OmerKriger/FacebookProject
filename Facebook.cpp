#include <iostream>
using namespace std;
#include "Facebook.h"
#include "Member.h"
#include "Page.h"
#include "supportFunctions.h"
#include "Date.h"
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
		for (int i = 0; i < lSizeMembers ; i++)
			pNewMembers[i] = members[i];
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
		for (int i = 0; i < lSizeMembers; i++)
			pNewPages[i] = fanPages[i];
	fanPages = pNewPages;
	pSizeFanPages = newSize;
	return true;
}

bool Facebook::createMember(const char* name, int day, int month, int year) 
{
	if (memberNameCheck(name))
		return false;
	Date bday(day,month,year);
	Member* pMember = new Member(name, bday);
	if (pSizeMembers <= lSizeMembers + 1)
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
			return false;
	return true;
}

bool Facebook::pageNameCheck(const char* name)
{
	for (int i = 0; i < lSizeFanPages; i++)
		if (strcmp(fanPages[i]->getName(), name) == MATCH)
			return false;
	return true;
}

bool Facebook::createFanPage(const char* name) 
{
	if (pageNameCheck(name))
		return false;
	Page* pPage = new Page(name);
	if (pSizeFanPages <= lSizeFanPages + 1)
		if (addSpaceForFanPages() == false)
			return false;
	fanPages[lSizeFanPages] = pPage;
	lSizeFanPages++;
	return true;
}

void Facebook::showAllMembers() const 
{
	cout << "All Members in Facebook:" << endl;
	for (int i = 0; i < lSizeMembers; i++)
		cout << "Member #" << i+1 << ": " << members[i]->getName() << endl;
	cout << "---- End of Member List ----" << endl << endl;
}

void Facebook::showAllPages() const 
{
	cout << "All Pages in Facebook:" << endl;
	for (int i = 0; i < lSizeFanPages; i++)
		cout << "Fan Page #" << i + 1 << ": " << fanPages[i]->getName() << endl;
	cout << "---- End of Fan Page List ----" << endl << endl;
}
