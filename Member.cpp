#include "Member.h"
#include "Page.h"
#include "Status.h"
#include "supportFunctions.h"
#include "Date.h"
#define DAY_SHIFT 1000000
#define MONTH_SHIFT 10000
#define YEAR_SHIFT 1
#define MAX_FRIEND_LATEST_STATUS 10
#define MATCH_STRING 0
#define NOT_FOUND -1

// C'tors in Members

Member::Member(const char* name, Date bDay)
{
	setName(name);
	birthDay = bDay;
	myStatus = nullptr;
	F_S_newestStatusIndex = 0;
	InterestPages = nullptr;
	friends = nullptr;
	logSizeFriends = logSizeMyStatus = logSizeFriendsStatus = logSizeInterestPages = 0;
	phySizeFriends = phySizeMyStatus = phySizeInterestPages = 0;
}

// Friends functions in Member
 
bool Member::addFriend(Member* newFriend)
{
	if (searchFriend(newFriend->name) == NOT_FOUND) // we can't add friend already in friends
		return false;
	if (phySizeFriends <= logSizeFriends)
		addSpaceFriendList();
	friends[logSizeFriends] = newFriend;
	logSizeFriends++;
	/*
	Place to put somecode for remove the friendship from the friend
	*/
	return true;
}
bool Member::removeFriend(Member* Friend) 
{
	int indexOfFriend = searchFriend(Friend->name);
	if (indexOfFriend != NOT_FOUND) // we can't remove friend who is not in friends
		return false;
	friends[indexOfFriend] = friends[logSizeFriends - 1];
	logSizeFriends--;
	/*
	Place to put somecode for remove the friendship from the friend
	*/
	return true;
}
int Member::searchFriend(char* fName) 
{
	for (unsigned int i = 0; i < logSizeFriends; i++)
		if (strcmp(friends[i]->name,fName) == MATCH_STRING)
			return i; // return index (for right now returned value is really a bool)
	return -1;
}
int Member::searchPage(const char* pName)
{
	for (unsigned int i = 0; i < logSizeInterestPages; i++)
		if (strcmp(InterestPages[i]->getName(), pName) == MATCH_STRING)
			return i; // return index (for right now returned value is really a bool)
	return -1;
}

// Pages functions in Member

bool Member::addPage(Page* newPage)
{
	if (searchPage(newPage->getName()) == NOT_FOUND) // we can't add friend already in friends
		return false;
	if (phySizeInterestPages <= logSizeInterestPages)
		addSpaceFriendList();
	InterestPages[logSizeInterestPages] = newPage;
	logSizeInterestPages++;
	return true;
}

// Status Functions in Members

void Member::showMyStatus() 
{
	const char* text;
	cout << "My Statuses are:" << endl;
	for (unsigned int i = 0; i < logSizeMyStatus; i++)
	{
		text = myStatus[i]->getText();
		cout << "Status " << i + 1 << "# : " << text << endl;
	}
} 

bool Member::addStatus(const char* text, sType type)
{
	if (phySizeMyStatus <= logSizeMyStatus)
		addSpaceMyStatusList();
	Status* status = new Status(text, type);
	myStatus[logSizeMyStatus] = status;
	logSizeMyStatus++;
	return true;
}

bool Member::postStatus() { return 0; }

// add space to lists functions
bool Member::addSpaceFriendList()
{
	int newSize;
	if (phySizeFriends == 0)
		newSize = 1;

	else
		newSize = phySizeFriends * 2;
	Member** newFriends = new Member * [newSize];
	for (int i = 0; i < logSizeFriends; i++)
		newFriends[i] = friends[i];


	bool allocateSuccess = checkAllocate(friends);
	if (allocateSuccess)
	{
		phySizeFriends = newSize;
		delete[] friends;
		friends = newFriends;
	}
	return allocateSuccess;
}
bool Member::addSpaceMyStatusList()
{
	int newSize;
	if (phySizeMyStatus == 0)
		newSize = 1;
	else
		newSize = phySizeMyStatus * 2;

	Status** newMyStatus = new Status * [newSize];
	for (int i = 0; i < logSizeMyStatus; i++)
		newMyStatus[i] = myStatus[i];

	bool allocateSuccess = checkAllocate(newMyStatus);
	if (allocateSuccess)
	{
		phySizeMyStatus = newSize;
		delete[] myStatus;
		myStatus = newMyStatus;
	}
	return allocateSuccess;
}
bool Member::addSpaceInterestPagesList()
{
	int newSize;
	if (phySizeInterestPages == 0)
		newSize = 1;
	else
		newSize = phySizeInterestPages * 2;

	Page ** newInterestPages = new Page * [newSize];
	for (int i = 0; i < logSizeInterestPages; i++)
		newInterestPages[i] = InterestPages[i];

	bool allocateSuccess = checkAllocate(InterestPages);
	if (allocateSuccess)
	{
		phySizeInterestPages = newSize;
		delete[] InterestPages;
		InterestPages = newInterestPages;
	}
	return allocateSuccess;
}
// need to decide if remove or not

//bool Member::addSpaceFriendsStatusList()
//{
//	if (phySizeFriendsStatus == MAX_FRIEND_LATEST_STATUS) // check if trying to add more space than defined
//		return false;
//	int newSize;
//	if (phySizeFriendsStatus == 0)
//		newSize = 1;
//	else
//	{
//		newSize = phySizeFriendsStatus * 2;
//		if (newSize > MAX_FRIEND_LATEST_STATUS)
//			newSize = MAX_FRIEND_LATEST_STATUS;
//	}
//	FriendsStatus = new Status * [newSize];
//	bool allocateSuccess = checkAllocate(FriendsStatus);
//	if (allocateSuccess)
//		phySizeFriendsStatus = newSize;
//	return allocateSuccess;
//} 

// setters/getters
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
const char* Member::getName() const
{
	return name;
}



