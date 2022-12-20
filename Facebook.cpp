#include <iostream>
using namespace std;
#include "Facebook.h"

Facebook::~Facebook()
{
	vector<Member*>::const_iterator mItr = this->members.begin();
	vector<Member*>::const_iterator mItrEnd = this->members.end();
	vector<Page*>::const_iterator pItr = this->fanPages.begin();
	vector<Page*>::const_iterator pItrEnd = this->fanPages.end();

	for (; pItr != pItrEnd; ++pItr)
		delete (*pItr);
	for (; mItr != mItrEnd; ++mItr)
		delete (*mItr);
	cout << "Facebook out, over!" << endl;
}

void Facebook::__Init__()
{
	// This function create default data in system
	
	// creating defualt Members
	this->createMember("Omer Kriger", Date(10, 5, 1998));
	this->createMember("Nir Peretz", Date(9, 8, 1997));
	this->createMember("Mark Zuckerberg", Date(14, 5, 1984));
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

bool Facebook::createMember(const char* name, Date bDay)
{
	if (memberNameCheck(name) == true)
	{
		cout << "This name already exist in the system" << endl;
		return false;
	}
	if (!bDay.isDefined())
	{
		cout << "The birthday is not defined well." << endl;
		return false;
	}
	Member* pMember = new Member(name, bDay);
	if (members.capacity() <= members.size())
		members.reserve(members.capacity() * 2);
	members.push_back(pMember);
	return true;
}

bool Facebook::memberNameCheck(const char* name) const // checking if the name is exist Member return true for found and false for not found
{
	vector<Member*>::const_iterator itr = this->members.begin();
	vector<Member*>::const_iterator itrEnd = this->members.end();
	for (; itr != itrEnd; ++itr )
		if (strcmp((*itr)->getName(), name) == MATCH)
			return true;
	return false;
}

bool Facebook::createFanPage(const char* name) 
{
	if (pageNameCheck(name) == true) // is already in the system
	{
		cout << "This name already exist in the system" << endl;
		return false;
	}
	Page* pPage = new Page(name);
	if (fanPages.capacity() <= fanPages.size() && fanPages.capacity() != 0)
		fanPages.reserve(fanPages.capacity() * 2);
	fanPages.push_back(pPage);
	return true;
}

bool Facebook::pageNameCheck(const char* name) const // checking if the name is exist Page return true for found and false for not found
{ 
	vector<Page*>::const_iterator itr = this->fanPages.begin();
	vector<Page*>::const_iterator itrEnd = this->fanPages.end();
	for (; itr != itrEnd; ++itr)
		if (strcmp( (*itr)->getName() , name) == MATCH)
			return true;
	return false;
}

void Facebook::showAllMembers() const
{
	vector<Member*>::const_iterator itr = this->members.begin();
	vector<Member*>::const_iterator itrEnd = this->members.end();
	cout << "-------- All Members in Facebook: --------" << endl;
	for (int i = 0; itr != itrEnd; ++itr, ++i)
		cout << "Member #" << i << " Name: " << (*itr)->getName() << endl;
	cout << "----------- End of Member List -----------" << endl << endl;
}

void Facebook::showAllPages() const
{
	vector<Page*>::const_iterator itr = this->fanPages.begin();
	vector<Page*>::const_iterator itrEnd = this->fanPages.end();
	cout << "--------- All Pages in Facebook: ---------" << endl;
	for (int i=0; itr != itrEnd; ++itr, ++i)
		cout << "Fan Page #" << i << " Name: " << (*itr)->getName() << endl;
	cout << "---------- End of Fan Page List ----------" << endl << endl;
}

Member& Facebook::getMember(const char* name) // return member by ref from array of members
{
	vector<Member*>::const_iterator itr = this->members.begin();
	vector<Member*>::const_iterator itrEnd = this->members.end();
	for (; itr != itrEnd; ++itr)
		if (strcmp(name, (*itr)->getName()) == MATCH)
			return **itr;
}
const Member& Facebook::getMember(const char* name) const // return member by const ref from array of members
{
	vector<Member*>::const_iterator itr = this->members.begin();
	vector<Member*>::const_iterator itrEnd = this->members.end();
	for (; itr != itrEnd; ++itr)
		if (strcmp(name, (*itr)->getName()) == MATCH)
			return **itr;
}

const Page& Facebook::getPage(const char* name) const // return page by const ref from array of pages
{
	vector<Page*>::const_iterator itr = this->fanPages.begin();
	vector<Page*>::const_iterator itrEnd = this->fanPages.end();
	for (; itr != itrEnd; ++itr)
		if (strcmp(name, (*itr)->getName()) == MATCH)
			return **itr;
}
Page& Facebook::getPage(const char* name) // return page by ref from array of pages
{
	vector<Page*>::const_iterator itr = this->fanPages.begin();
	vector<Page*>::const_iterator itrEnd = this->fanPages.end();
	for (; itr != itrEnd; ++itr)
		if (strcmp(name, (*itr)->getName()) == MATCH)
			return **itr;
}
