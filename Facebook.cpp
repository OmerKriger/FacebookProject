#include <iostream>
using namespace std;
#include "Facebook.h"
#define MATCH 0


Facebook::Facebook()
{
	logSizeMembers = logSizeFanPages = phySizeFanPages = phySizeMembers = 0;
	members = nullptr;
	fanPages = nullptr;
}

Facebook::~Facebook()
{
	for (int i = 0; i < logSizeFanPages; i++)
		delete fanPages[i];
	delete[] fanPages;
	for (int i = 0; i < logSizeMembers; i++)
		delete members[i];
	delete[] members;
	cout << "Facebook out, over!" << endl;
}

/// <summary>
/// need to be finish Init
/// </summary>
void Facebook::__Init__()
{
	// creating defualt Members
	this->createMember("Omer Kriger", 10, 5, 1998);
	this->createMember("Nir Peretz", 9, 8, 1997);
	this->createMember("Mark Zuckerberg", 14, 5, 1984);
	// creating defualt Pages
	this->createFanPage("Eduardo Saverin");
	this->createFanPage("Nike");
	this->createFanPage("NBA");
	this->createFanPage("Toto Wolff");
	// creating default connections between Members and Pages
	this->getMember("Omer Kriger").addPage(this->getPage("Nike"));
	this->getMember("Omer Kriger").addPage(this->getPage("Toto Wolff"));
	this->getMember("Nir Peretz").addPage(this->getPage("Nike"));
	this->getMember("Nir Peretz").addPage(this->getPage("NBA"));
	this->getMember("Mark Zuckerberg").addPage(this->getPage("Eduardo Saverin"));
	// creating default connections between Members
	this->getMember("Omer Kriger").addFriend(&(this->getMember("Nir Peretz")));
	this->getMember("Omer Kriger").addFriend(&(this->getMember("Mark Zuckerberg")));
	this->getMember("Nir Peretz").addFriend(&(this->getMember("Mark Zuckerberg")));
	// creating default Status for Pages
	this->getPage("Eduardo Saverin").addStatus("You wake up in the morning and discover Mark stole your stocks....");
	this->getPage("Eduardo Saverin").addStatus("I Hate Mark Zuckerberg !!");
	this->getPage("Nike").addStatus("Just Do It.");
	this->getPage("Nike").addStatus("I need a new Air Jorden.");
	this->getPage("Toto Wolff").addStatus("No, Mikey, No, No, Mikey, That Was So Not Right!");
	this->getPage("Toto Wolff").addStatus("Danke Seb.");
	// creating default Status for Members
	this->getMember("Omer Kriger").addStatus("In case I don't see ya good afternoon, good evening and goodnight.");
	this->getMember("Omer Kriger").addStatus("CrossFit is just Fight Club if the first two rules were the opposite.");
	this->getMember("Nir Peretz").addStatus("Something clever");
	this->getMember("Nir Peretz").addStatus("More clever than the first status");
	this->getMember("Mark Zuckerberg").addStatus("Shlomo Artzi stole my songs !!");
	this->getMember("Mark Zuckerberg").addStatus("Maybe your battery is dead in your IP.");
}

bool Facebook::addSpaceForMembers()
{
	int newSize;
	if (phySizeMembers == 0)
		newSize = 1;
	else
		newSize = phySizeMembers * 2;
	Member** pNewMembers = new Member * [newSize];
	if (checkAllocate(pNewMembers) == false)
		return false;
	if (members != nullptr)
	{
		for (int i = 0; i < logSizeMembers; i++)
			pNewMembers[i] = members[i];
		delete[] members;
	}
	members = pNewMembers;
	phySizeMembers = newSize;
	return true;
}

bool Facebook::addSpaceForFanPages()
{
	int newSize;
	if (phySizeFanPages == 0)
		newSize = 1;
	else
		newSize = phySizeFanPages * 2;
	Page** pNewPages = new Page * [newSize];
	if (checkAllocate(pNewPages) == false)
		return false;
	if (fanPages != nullptr)
	{
		for (int i = 0; i < logSizeFanPages; i++)
			pNewPages[i] = fanPages[i];
		delete[] fanPages;
	}
	fanPages = pNewPages;
	phySizeFanPages = newSize;
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
	if (phySizeMembers <= logSizeMembers)
		if (addSpaceForMembers() == false)
			return false;
	members[logSizeMembers] = pMember;
	logSizeMembers++;
	return true;
}

bool Facebook::memberNameCheck(const char* name)
{
	for (int i = 0; i < logSizeMembers; i++)
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
	if (phySizeFanPages <= logSizeFanPages)
		if (addSpaceForFanPages() == false)
			return false;
	fanPages[logSizeFanPages] = pPage;
	logSizeFanPages++;
	return true;
}

bool Facebook::pageNameCheck(const char* name)
{
	for (int i = 0; i < logSizeFanPages; i++)
		if (strcmp(fanPages[i]->getName(), name) == MATCH)
			return true;
	return false;
}

void Facebook::showAllMembers() const
{
	cout << "-------- All Members in Facebook: --------" << endl;
	for (int i = 0; i < logSizeMembers; i++)
		cout << "Member #" << i + 1 << " Name: " << members[i]->getName() << endl;
	cout << "----------- End of Member List -----------" << endl << endl;
}

void Facebook::showAllPages() const
{
	cout << "--------- All Pages in Facebook: ---------" << endl;
	for (int i = 0; i < logSizeFanPages; i++)
		cout << "Fan Page #" << i + 1 << " Name: " << fanPages[i]->getName() << endl;
	cout << "---------- End of Fan Page List ----------" << endl << endl;
}

Member& Facebook::getMember(const char* name)
{
	for (int i = 0; i < logSizeMembers; i++)
		if (strcmp(name, members[i]->getName()) == MATCH)
			return *(members[i]);
}
const Member& Facebook::getMember(const char* name) const
{
	for (int i = 0; i < logSizeMembers; i++)
		if (strcmp(name, members[i]->getName()) == MATCH)
			return *(members[i]);
}

const Page& Facebook::getPage(const char* name) const
{
	for (int i = 0; i < logSizeFanPages; i++)
		if (strcmp(name, fanPages[i]->getName()) == MATCH)
			return *fanPages[i];
}
Page& Facebook::getPage(const char* name)
{
	for (int i = 0; i < logSizeFanPages; i++)
		if (strcmp(name, fanPages[i]->getName()) == MATCH)
			return *fanPages[i];
}
