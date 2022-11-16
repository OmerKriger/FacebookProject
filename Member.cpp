#include "Member.h"
#include "Page.h"
#include "Status.h"
#include "supportFunctions.h"

#define DAY_SHIFT 1000000
#define MONTH_SHIFT 10000
#define YEAR_SHIFT 1
#define MAX_FRIEND_LATEST_STATUS 10
#define MATCH_STRING 0
#define NOT_FOUND -1

// Friends functions in Member
 
bool Member::addFriend(Member* newFriend)
{
	if (searchFriend(newFriend->name) == NOT_FOUND) // we can't add friend already in friends
		return false;
	if (phySizeFriends <= logSizeFriends + 1)
		addSpaceFriendList();
	friends[logSizeFriends] = newFriend;
	logSizeFriends++;
	return true;
}
bool Member::removeFriend(Member* dFriend) 
{
	int indexOfFriend = searchFriend(dFriend->name);
	if (indexOfFriend != NOT_FOUND) // we can't remove friend who is not in friends
		return false;
	Member** newFriendArr = nullptr;
	if (phySizeFriends / 2 >= logSizeFriends - 1)
	{
		newFriendArr = new Member * [phySizeFriends / 2];
		if (checkAllocate(newFriendArr) == false)
			return false;
		else
			phySizeFriends /= 2;
		for (int i = 0 ; i < indexOfFriend; i++)
			newFriendArr[i] = friends[i];
	}
	else
		newFriendArr = friends;

	for (int i = indexOfFriend; i < logSizeFriends-1; i++)
		newFriendArr[i] = friends[i+1];
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
	if (phySizeInterestPages <= logSizeInterestPages + 1)
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

bool Member::addStatus() {}
bool Member::postStatus() {}

// add space to lists functions
bool Member::addSpaceFriendList()
{
	int newSize;
	if (phySizeFriends == 0)
		newSize = 1;
	else
		newSize = phySizeFriends*2;

	friends = new Member * [newSize];
	bool allocateSuccess = checkAllocate(friends);
	if (allocateSuccess)
		phySizeFriends = newSize;
	return allocateSuccess;
}
bool Member::addSpaceMyStatusList()
{
	int newSize;
	if (phySizeMyStatus == 0)
		newSize = 1;
	else
		newSize = phySizeMyStatus * 2;

	myStatus = new Status * [newSize];
	bool allocateSuccess = checkAllocate(myStatus);
	if (allocateSuccess)
		phySizeMyStatus = newSize;
	return allocateSuccess;
}
bool Member::addSpaceInterestPagesList()
{
	int newSize;
	if (phySizeInterestPages == 0)
		newSize = 1;
	else
		newSize = phySizeInterestPages * 2;

	InterestPages = new Page * [newSize];
	bool allocateSuccess = checkAllocate(InterestPages);
	if (allocateSuccess)
		phySizeInterestPages = newSize;
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
bool Member::setName(char* str)
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
const char* Member::getName()
{
	return name;
}
bool Member::setBirthDay(int day, int month, int year)
{
	if (birthDay != -1)
	{
		birthDay = day * DAY_SHIFT + month * MONTH_SHIFT + year*YEAR_SHIFT;
		return true;
	}
	else
	{
		cout << "Birthday date is already setted and can't be change\n";
		return false;
	}

}



