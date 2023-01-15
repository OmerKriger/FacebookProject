#include <iostream>
using namespace std;
#include "Facebook.h"
Facebook::Facebook()
{
	if (TEST)
		__Init__();
}

Facebook::~Facebook()
{
	if (COMPARE_TEST)
	{
		testCompareOperators();
	}
	list<Member*>::const_iterator mItr = this->members.begin();
	list<Member*>::const_iterator mItrEnd = this->members.end();
	list<Page*>::const_iterator pItr = this->fanPages.begin();
	list<Page*>::const_iterator pItrEnd = this->fanPages.end();

	for (; pItr != pItrEnd; ++pItr)
		delete (*pItr);
	for (; mItr != mItrEnd; ++mItr)
		delete (*mItr);
	cout << "Facebook out, over!" << endl;
}
void Facebook::testCompareOperators() const
{
	int res;
	// test member between member
	{
		list<Member*>::const_iterator mItr1 = this->members.begin();
		list<Member*>::const_iterator mItrEnd1 = this->members.end();
		for (; mItr1 != mItrEnd1; ++mItr1)
		{
			list<Member*>::const_iterator mItr2 = this->members.begin();
			list<Member*>::const_iterator mItrEnd2 = this->members.end();
			for (; mItr2 != mItrEnd2; ++mItr2)
			{
				if (mItr2 != mItr1)
				{
					if (*(*mItr1) < *(*mItr2))
						res = 1;
					else
						res = 0;
					cout << "Name: " << (*mItr1)->getName() << "Friend Number: " << (*mItr1)->getAmountOfFriends() << " < " << "Name: " << (*mItr2)->getName() << " Friend Number: " << (*mItr2)->getAmountOfFriends() << ", Result: " << res << endl;
					if (*(*mItr1) > *(*mItr2))
						res = 1;
					else
						res = 0;
					cout << "Name: " << (*mItr1)->getName() << "Friend Number: " << (*mItr1)->getAmountOfFriends() << " > " << "Name: " << (*mItr2)->getName() << " Friend Number: " << (*mItr2)->getAmountOfFriends() << ", Result: " << res << endl;
					cout << endl << endl;
				}
			}
		}
	}
	{
		list<Member*>::const_iterator mItr1 = this->members.begin();
		list<Member*>::const_iterator mItrEnd1 = this->members.end();
		for (; mItr1 != mItrEnd1; ++mItr1)
		{
			list<Page*>::const_iterator mItr2 = this->fanPages.begin();
			list<Page*>::const_iterator mItrEnd2 = this->fanPages.end();
			for (; mItr2 != mItrEnd2; ++mItr2)
			{
				// member
				if (*(*mItr1) < *(*mItr2))
					res = 1;
				else
					res = 0;
				cout << "Name: " << (*mItr1)->getName() << "Friend Number: " << (*mItr1)->getAmountOfFriends() << " < " << "Page Name: " << (*mItr2)->getName() << " Fans Number: " << (*mItr2)->getSizeOfFans() << ", Result: " << res << endl;
				if (*(*mItr1) > *(*mItr2))
					res = 1;
				else
					res = 0;
				cout << "Name: " << (*mItr1)->getName() << "Friend Number: " << (*mItr1)->getAmountOfFriends() << " > " << "Page Name: " << (*mItr2)->getName() << " Fans Number: " << (*mItr2)->getSizeOfFans() << ", Result: " << res << endl;
				// page 
				if (*(*mItr2) < *(*mItr1))
					res = 1;
				else
					res = 0;
				cout << "Page Name: " << (*mItr2)->getName() << " Fans Number: " << (*mItr2)->getSizeOfFans() << " < " << "Name: " << (*mItr1)->getName() << "Friend Number: " << (*mItr1)->getAmountOfFriends() << ", Result: " << res << endl;
				if (*(*mItr2) > *(*mItr1))
					res = 1;
				else
					res = 0;
				cout << "Page Name: " << (*mItr2)->getName() << " Fans Number: " << (*mItr2)->getSizeOfFans() << " > " << "Name: " << (*mItr1)->getName() << "Friend Number: " << (*mItr1)->getAmountOfFriends() << ", Result: " << res << endl;
				cout << endl << endl;
			}
		}
	}
	// page for page
	{
		list<Member*>::const_iterator mItr1 = this->members.begin();
		list<Member*>::const_iterator mItrEnd1 = this->members.end();
		for (; mItr1 != mItrEnd1; ++mItr1)
		{
			list<Member*>::const_iterator mItr2 = this->members.begin();
			list<Member*>::const_iterator mItrEnd2 = this->members.end();
			for (; mItr2 != mItrEnd2; ++mItr2)
			{
				if (mItr2 != mItr1)
				{
					if (*(*mItr1) < *(*mItr2))
						res = 1;
					else
						res = 0;
					cout << "page Name: " << (*mItr1)->getName() << "fans Number: " << (*mItr1)->getAmountOfFriends() << " < " << "page Name: " << (*mItr2)->getName() << " fans Number: " << (*mItr2)->getAmountOfFriends() << ", Result: " << res << endl;
					if (*(*mItr1) > *(*mItr2))
						res = 1;
					else
						res = 0;
					cout << "page Name: " << (*mItr1)->getName() << "fans Number: " << (*mItr1)->getAmountOfFriends() << " > " << "page Name: " << (*mItr2)->getName() << " fans Number: " << (*mItr2)->getAmountOfFriends() << ", Result: " << res << endl;
					cout << endl << endl;
				}
			}
		}
	}

}
void Facebook::__Init__()
{
	// This function create default data in system
	// creating defualt Members
	string emptyStr = "";
	try
	{
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
		this->getMember("Omer Kriger").addStatus("In case I don't see ya good afternoon, good evening and goodnight.", 1, emptyStr);
		this->getMember("Omer Kriger").addStatus("CrossFit is just Fight Club if the first two rules were the opposite.", 1, emptyStr);
		this->getMember("Nir Peretz").addStatus("Something clever", 1, emptyStr);
		this->getMember("Nir Peretz").addStatus("More clever than the first status", 1, emptyStr);
		this->getMember("Mark Zuckerberg").addStatus("Shlomo Artzi stole my songs !!", 1, emptyStr);
		this->getMember("Mark Zuckerberg").addStatus("Maybe your battery is dead in your IP.", 1, emptyStr);
	}
	catch (...)
	{
		FacebookException("The setup for Testing (default data) creating failed (Facebook::__Init__)", FacebookException::facebookErrorList::INIT_FAILED);
	}
}

void Facebook::createMember(const string& name, Date bDay)
{
	if (memberNameCheck(name) == true)
		throw FacebookException("This name already exist in the system ", FacebookException::facebookErrorList::MEMBER_EXIST);
	if (!bDay.isDefined())
		throw DateException("The birthday is not defined well.");
	try
	{
		Member* pMember = new Member(name, bDay);
		members.push_back(pMember);
	}
	catch (MemberException& e)
	{
		throw e;
	}
}

bool Facebook::memberNameCheck(const string& name) const // checking if the name is exist Member return true for found and false for not found
{
	list<Member*>::const_iterator itr = this->members.begin();
	list<Member*>::const_iterator itrEnd = this->members.end();
	for (; itr != itrEnd; ++itr )
		if ((*itr)->getName() == name)
			return true;
	return false;
}

void Facebook::createFanPage(const string& name)
{
	if (pageNameCheck(name) == true) // is already in the system
		throw FacebookException("This name already exist in the system", FacebookException::facebookErrorList::PAGE_EXIST);
	try
	{
		Page* pPage = new Page(name);
		fanPages.push_back(pPage);
	}
	catch (PageException& e)
	{
		throw e;
	}
}

bool Facebook::pageNameCheck(const string& name) const // checking if the name is exist Page return true for found and false for not found
{ 
	list<Page*>::const_iterator itr = this->fanPages.begin();
	list<Page*>::const_iterator itrEnd = this->fanPages.end();
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getName() == name)
			return true;
	return false;
}

void Facebook::showAllMembers() const
{
	list<Member*>::const_iterator itr = this->members.begin();
	list<Member*>::const_iterator itrEnd = this->members.end();
	cout << "-------- All Members in Facebook: --------" << endl;
	for (int i = 0; itr != itrEnd; ++itr, ++i)
		cout << "Member #" << i + 1 << " Name: " << (*itr)->getName() << endl;
	cout << "----------- End of Member List -----------" << endl << endl;
}

void Facebook::showAllPages() const
{
	list<Page*>::const_iterator itr = this->fanPages.begin();
	list<Page*>::const_iterator itrEnd = this->fanPages.end();
	cout << "--------- All Pages in Facebook: ---------" << endl;
	for (int i=0; itr != itrEnd; ++itr, ++i)
		cout << "Fan Page #" << i + 1 << " Name: " << (*itr)->getName() << endl;
	cout << "---------- End of Fan Page List ----------" << endl << endl;
}

Member& Facebook::getMember(const string& name) // return member by ref from array of members
{
	list<Member*>::const_iterator itr = this->members.begin();
	list<Member*>::const_iterator itrEnd = this->members.end();
	for (; itr != itrEnd; ++itr)
		if (name == (*itr)->getName())
			return **itr;
	throw FacebookException("This Member isn't found.", FacebookException::facebookErrorList::MEMBER_NOT_FOUND);
}
const Member& Facebook::getMember(const string& name) const // return member by const ref from array of members
{
	list<Member*>::const_iterator itr = this->members.begin();
	list<Member*>::const_iterator itrEnd = this->members.end();
	for (; itr != itrEnd; ++itr)
		if (name == (*itr)->getName())
			return **itr;
	throw FacebookException("This Member isn't found. ", FacebookException::facebookErrorList::MEMBER_NOT_FOUND);
}
const Page& Facebook::getPage(const string& name) const // return page by const ref from array of pages
{
	list<Page*>::const_iterator itr = this->fanPages.begin();
	list<Page*>::const_iterator itrEnd = this->fanPages.end();
	for (; itr != itrEnd; ++itr)
		if (name == (*itr)->getName())
			return **itr;
	throw FacebookException("This Page isn't found.", FacebookException::facebookErrorList::PAGE_NOT_FOUND);
}
Page& Facebook::getPage(const string& name) // return page by ref from array of pages
{
	list<Page*>::const_iterator itr = this->fanPages.begin();
	list<Page*>::const_iterator itrEnd = this->fanPages.end();
	for (; itr != itrEnd; ++itr)
		if (name == (*itr)->getName())
			return **itr;
	throw FacebookException("This Page isn't found. ", FacebookException::facebookErrorList::PAGE_NOT_FOUND);
}