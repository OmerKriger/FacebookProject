#include <iostream>
using namespace std;
#include "Member.h"
#include "Page.h"
#include "Status.h"
#include "supportFunctions.h"
#include "Date.h"

// C'tors in Members

Member::Member(const char* name, Date bDay)
{
	setName(name);
	birthDay = bDay;
	myStatus = nullptr;
	InterestPages = nullptr;
	friends = nullptr;
	logSizeFriends = logSizeMyStatus = logSizeInterestPages = 0;
	phySizeFriends = phySizeMyStatus = phySizeInterestPages = 0;
}
Member::~Member()
{
	delete[] name;
	for (int i = 0; i < logSizeMyStatus; i++)
		delete myStatus[i];
	delete[] myStatus;
	delete[] InterestPages;
	delete[] friends;
}

// Friends functions in Member
 
bool Member::addFriend(Member* newFriend)
{
	if (searchFriend(newFriend->name) != NOT_FOUND) // we can't add friend already in friends
		return false;
	if (phySizeFriends <= logSizeFriends)
		addSpaceFriendList();
	friends[logSizeFriends] = newFriend;
	logSizeFriends++;
	if (newFriend->addFriend(this) == false)
		return true;
}
bool Member::removeFriend(Member* Friend) 
{
	int indexOfFriend = searchFriend(Friend->name);
	if (indexOfFriend == NOT_FOUND) // we can't remove friend who is not in friends
		return false;
	friends[indexOfFriend] = friends[logSizeFriends - 1];
	logSizeFriends--;
	if (Friend->removeFriend(this) == false)
		return true;
}
int Member::searchFriend(char* fName) 
{
	for (int i = 0; i < logSizeFriends; i++)
		if (strcmp(friends[i]->name,fName) == MATCH)
			return i; // return index found
	return NOT_FOUND;
}
int Member::searchPage(const char* pName)
{
	for (int i = 0; i < logSizeInterestPages; i++)
		if (strcmp(InterestPages[i]->getName(), pName) == MATCH)
			return i; // return index
	return -1;
}

// Pages functions in Member

bool Member::addPage(Page& newPage)
{
	if (searchPage(newPage.getName()) != NOT_FOUND)
		return false;
	if (phySizeInterestPages <= logSizeInterestPages)
		addSpaceInterestPagesList();
	InterestPages[logSizeInterestPages] = &newPage;
	logSizeInterestPages++;
	// say to page add this friend to his list
	newPage.addFan(this);
	return true;
}
bool Member::removePage(const Page& dPage)
{
	int index = searchPage(dPage.getName());
	if (index == NOT_FOUND)
	{
		cout << "This member isn't follow after this page !" << endl;
		return false;
	}
	this->InterestPages[index] = this->InterestPages[logSizeInterestPages - 1];
	logSizeInterestPages--;
	return true;	
}
void Member::showMyInterestPages() const
{
	if (logSizeInterestPages == 0)
	{
		cout << "System: " << this->getName() << " has no page followed." << endl << endl;
		return;
	}
	cout << "-------- All Followed Pages by " << this->getName() << " --------" << endl;
	for (int i = 0; i < logSizeInterestPages; i++)
		cout << "Fan Page #" << i + 1 << " Name: " << InterestPages[i]->getName() << endl;
	cout << "----------- End of Followed Pages List -----------" << endl << endl;
}

// Status Functions in Members

void Member::showMyStatus() const
{
	if (logSizeMyStatus == 0)
	{
		cout << "System: " << this->getName() << " has no Status." << endl << endl;
		return;
	}
	cout << "-------- All Status of " << this->getName() << " --------" << endl;
	for (int i = 0; i < logSizeMyStatus; i++)
		cout << "Status " << i + 1 << "# : " << myStatus[i]->getText() << endl;
	cout << "----------- End of Status List of "<< this->getName() << " -----------" << endl << endl;

} 
bool Member::addStatus(const char* text)
{
	return addStatus(text, sType::tText);
}
bool Member::addStatus(const char* text, sType type)
{
	if (phySizeMyStatus <= logSizeMyStatus)
		if (addSpaceMyStatusList() == false)
			return false;
	Status* status = new Status(text,this->getName());
	myStatus[logSizeMyStatus] = status;
	logSizeMyStatus++;
	return true;
}
void Member::showLastFriendsStatus() const
{
	bool somethingPrinted = false;
	if (this->logSizeFriends == 0)
	{
		cout << "System: This Member has no friends." << endl << endl;
		return;
	}
	else
	{
		for (int i = 0; i < logSizeFriends; i++)
		{
			if (this->friends[i]->getAmountOfStatus() > 0 && somethingPrinted == false) // change flag for status printed
				somethingPrinted = true;
			this->friends[i]->showMyLastStatuses(); // print statuses of friends
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
	for (int i = logSizeMyStatus-1 ; i >= 0 && i > (logSizeMyStatus - AMOUNT_SHOW_FRIENDS_STATUSES - 1) ; i--)
		myStatus[i]->showStatus();
}
// adding space to lists functions

bool Member::addSpaceFriendList()
{
	int newSize;
	if (phySizeFriends == 0)
		newSize = 1;
	else
		newSize = phySizeFriends * 2;
	Member** newFriends = new Member * [newSize];
	if (checkAllocate(newFriends) == false)
		return false;
	if (friends != nullptr) // if there are already array copy data to new one
	{
		for (int i = 0; i < logSizeFriends; i++) // copy old data
			newFriends[i] = friends[i];
		delete[] friends;
	}
	friends = newFriends;
	phySizeFriends = newSize;
	return true;
}
bool Member::addSpaceMyStatusList()
{
	int newSize;
	if (phySizeMyStatus == 0)
		newSize = 1;
	else
		newSize = phySizeMyStatus * 2;

	Status** newMyStatus = new Status * [newSize];
	if (checkAllocate(newMyStatus) == false)
		return false;
	if (myStatus != nullptr) // if there are already array copy data to new one
	{
		for (int i = 0; i < logSizeMyStatus; i++) // copy old data
			newMyStatus[i] = myStatus[i];
		delete[] myStatus;
	}
	phySizeMyStatus = newSize;
	myStatus = newMyStatus;
	return true;
}
bool Member::addSpaceInterestPagesList()
{
	int newSize;
	if (phySizeInterestPages == 0)
		newSize = 1;
	else
		newSize = phySizeInterestPages * 2;

	Page ** newInterestPages = new Page * [newSize];
	if (checkAllocate(newInterestPages) == false)
		return false;
	if (InterestPages != nullptr) // if there are already array copy data to new one
	{
		for (int i = 0; i < logSizeInterestPages; i++) // copy old data
			newInterestPages[i] = InterestPages[i];
		delete[] InterestPages;
	}
	InterestPages = newInterestPages;
	phySizeInterestPages = newSize;
	return true;
}

// setters/getters/voids
bool Member::setName(const char* str)
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
void Member::showMyFriends() const
{
	if (logSizeFriends == 0)
	{
		cout << "System: " << this->getName() << " has no friends." << endl << endl;
		return;
	}
	cout << "-------- All Friends of " << this->getName() << " --------" << endl;
	for (int i = 0; i < logSizeFriends; i++)
		cout << "Friend #" << i + 1 << " Name: " << friends[i]->getName() << endl;
	cout << "----------- End of Friends List -----------" << endl << endl;
}



