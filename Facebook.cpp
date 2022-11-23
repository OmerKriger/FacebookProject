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
	// need to complete
}

void Facebook::__Init__()
{
	createMember("Omer Kriger", 10, 5, 1998);
	createMember("Nir Peretz", 9, 8, 1997);
	createMember("Mark Zuckerberg", 14, 5, 1984);
	createFanPage("Eduardo Saverin");
	createFanPage("Nike");
	createFanPage("Google");
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
	if (members == nullptr)
		members = pNewMembers;
	else
		for (int i = 0; i < lSizeMembers; i++)
			pNewMembers[i] = members[i];
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
	if (fanPages == nullptr)
		fanPages = pNewPages;
	else
		for (int i = 0; i < lSizeMembers; i++)
			pNewPages[i] = fanPages[i];
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

bool Facebook::menu(char selection) 
{
	switch(selection)
	{
	case 1: break;
	case 2: break;
	case 3: break;
	case 4: break;
	case 5: break;
	case 6: break;
	case 7: break;
	case 8: break;
	case 9: break;
	case 10: break;
	case 11: break;
	case 12: break;
	default:
		return false;
	}
	return true;
}

void Facebook::printMenu() 
{
	cout << "1 - create Member: " << endl;
	cout << "2 - create Page: " << endl;
	cout << "3 - create Status: " << endl;
	cout << "4 - Show of Friend/Page Status: " << endl;
	cout << "5 - Show of Friens 10 Latest Status: " << endl;
	cout << "6 - Make two members friends:" << endl;
	cout << "7 - remove two members from be friends:" << endl;
	cout << "8 - add member to page:" << endl;
	cout << "9 - remove members from page:" << endl;
	cout << "10 - show all friends:" << endl;
	cout << "11 - show friends of friend:" << endl;
	cout << "12 - exit" << endl;
	}
