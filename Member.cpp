#include <iostream>
using namespace std;
#include "Member.h"
#include "Utilities.h"
#include "Page.h"
#include "Status.h"
#include "Date.h"

// C'tors in Members
Member::Member(const string& name, Date bDay)
{
	try
	{
		setName(name);
		birthDay = bDay;
	}
	catch (MemberException& e)
	{
		throw e;
	}
}
Member::~Member()
{
	list<Status*>::iterator itr = this->myStatus.begin();
	list<Status*>::iterator itrEnd = this->myStatus.end();
	for (; itr != itrEnd; ++itr)
		delete (*itr);
}

// Friends functions in Member
void Member::addFriend(Member* newFriend)
{
	if (newFriend == this) // friend cannot add him self
		throw MemberException("Friend cannot create friendships with himself.\n", MemberException::memberErrorList::FRIEND_HIMSELF);
	list<Member*>::iterator itrOfFriend = find(friends.begin(), friends.end(), newFriend); // search for newFriend in friends
	if (itrOfFriend != friends.end()) // if friend is found return false
		throw MemberException("This Members are already friends.\n", MemberException::memberErrorList::ALREADY_FRIENDS);
	friends.push_back(newFriend);
	try
	{
		newFriend->addFriend(this);
	}
	catch (MemberException& e)
	{
		if (e.getErrorCode() != MemberException::memberErrorList::ALREADY_FRIENDS)
			throw e;
	}
}
void Member::removeFriend(Member* dFriend)
{
	list<Member*>::iterator itrOfFriend = find(friends.begin(),friends.end(), dFriend);
	if (itrOfFriend == friends.end()) // we can't remove friend who is not in friends
		throw MemberException("This two Members isn't a friends",MemberException::memberErrorList::NOT_FRIENDS);
	friends.erase(itrOfFriend);
	try
	{
		dFriend->removeFriend(this);
	}
	catch (MemberException& e)
	{
		if (e.getErrorCode() != MemberException::memberErrorList::NOT_FRIENDS)
			throw e;
	}
}

// Pages functions in Member
void Member::addPage(Page& newPage)
{
	list<Page*>::iterator itrOfPage = find(InterestPages.begin(), InterestPages.end(), &newPage); // search for newFriend in friends
	if (itrOfPage != InterestPages.end()) // if friend is found return false
		throw MemberException("This Member already follow after this Page !", MemberException::memberErrorList::ALREADY_FOLLOW);
	InterestPages.push_back(&newPage);
	// say to page add this friend to his list
	try {
		newPage.addFan(this);
	}
	catch (PageException& e)
	{
		throw e;
	}
}
void Member::removePage(const Page& dPage)
{
	list<Page*>::iterator itrPage = find(InterestPages.begin(), InterestPages.end(), &dPage);
	if (itrPage == InterestPages.end()) // we can't remove page who is not in followed
		throw MemberException("This member isn't follow after this page !", MemberException::memberErrorList::NOT_FOLLOW);
	try
	{
		(*itrPage)->removeFan(this);
		InterestPages.erase(itrPage);
	}
	catch (PageException& e)
	{
		throw e;
	}
}
void Member::showMyInterestPages() const
{
	if (InterestPages.size() == 0)
	{
		cout << "System: " << this->getName() << " has no page followed." << endl << endl;
		return;
	}
	cout << "-------- All Followed Pages by " << this->getName() << " --------" << endl;
	list<Page*>::const_iterator itr = this->InterestPages.begin();
	list<Page*>::const_iterator itrEnd = this->InterestPages.end();
	for(int i = 0;itr!=itrEnd;++itr, ++i)
		cout << "Fan Page #" << i << " Name: " << (*itr)->getName() << endl;
	cout << "----------- End of Followed Pages List -----------" << endl << endl;
}

// Status Functions in Members

void Member::showMyStatus() const
{
	if (myStatus.size() == 0)
	{
		cout << "System: " << this->getName() << " has no Status." << endl << endl;
		return;
	}
	cout << "-------- All Status of " << this->getName() << " --------" << endl;
	list<Status*>::const_iterator itr = this->myStatus.begin();
	list<Status*>::const_iterator itrEnd = this->myStatus.end();
	for (int i = 0; itr != itrEnd; ++itr, ++i)
	{
		const Date& date = (*itr)->getDate();
		cout << "Status " << i + 1 << "# : " << (*itr)->getText() << " || ";
		cout << date.getDay() << "." << date.getMonth() << "." << date.getYear() << " ";
		if (date.getHours() < 10)
			cout << "0";
		cout << date.getHours() << ":";
		if (date.getMin() < 10)
			cout << "0";
		cout << "" << date.getMin() << endl;
	}
	cout << "----------- End of Status List of "<< this->getName() << " -----------" << endl << endl;

} 
void Member::addStatus(const string& text)
{
	try
	{
		Status* status = new Status(text, this->getName()); // change after we put strings in status.
		myStatus.push_front(status);
	}
	catch (StatusException& e)
	{
		throw e;
	}
}
void Member::showLastFriendsStatus() const
{
	bool somethingPrinted = false;
	if (friends.size() == 0)
	{
		cout << "System: This Member has no friends." << endl << endl;
		return;
	}
	else
	{
		list<Member*>::const_iterator itr = this->friends.begin();
		list<Member*>::const_iterator itrEnd = this->friends.end();
		for (int i = 0; itr != itrEnd; ++itr, ++i)
		{
			if ((*itr)->getAmountOfStatus() > 0 && somethingPrinted == false) // change flag for status printed
				somethingPrinted = true;
			(*itr)->showMyLastStatuses(); // print statuses of friends
		}
	}
	if (somethingPrinted == false) // if no status printed
		cout << "System: This Member's friends has no statuses." << endl << endl;
}
void Member::showMyLastStatuses() const 
{
	/// <summary>
	/// This function member show his statuses from the list of statuses
	/// </summary>
	list<Status*>::const_iterator itr = myStatus.begin();
	list<Status*>::const_iterator itrEnd = myStatus.end();
	for (int i = 0; itr != itrEnd && i <= AMOUNT_SHOW_FRIENDS_STATUSES; ++itr, ++i)
		(*itr)->showStatus();
}

// setters/getters/voids
void Member::setName(const string& str)
{
	if (name.empty() == false)
		throw MemberException("Name can't be changed after has been setted !\n", MemberException::memberErrorList::NAME_SETTED);
	if (str.size() <= 1)
		throw MemberException("Name is too short !\n", MemberException::memberErrorList::ILLEGAL_NAME);
	name = str;
}
void Member::showMyFriends() const
{
	if (friends.size() == 0)
	{
		cout << "System: " << this->getName() << " has no friends." << endl << endl;
		return;
	}
	cout << "-------- All Friends of " << this->getName() << " --------" << endl;
	list<Member*>::const_iterator itr = this->friends.begin();
	list<Member*>::const_iterator itrEnd = this->friends.end();
	for (int i = 0; itr != itrEnd; ++itr, ++i)
		cout << "Friend #" << i + 1 << " Name: " << (*itr)->getName() << endl;
	cout << "----------- End of Friends List -----------" << endl << endl;
}

// Operators
bool Member::operator<(const Member& other) const
{
	return this->friends.size() < other.friends.size();
}
bool Member::operator>(const Member& other) const
{
	return this->friends.size() > other.friends.size();
}
bool Member::operator<(const Page& other) const
{
	return this->friends.size() < other.getSizeOfFans();
}
bool Member::operator>(const Page& other) const
{
	return this->friends.size() > other.getSizeOfFans();
}

const Member& Member::operator+=(Member& other)
{
	this->addFriend(&other);
	return *this;
}

const Member& Member::operator+=(Page& page)
{
	page.addFan(this);
	return *this;
}

