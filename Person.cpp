#include "Person.h"
#include "Page.h"
#include "Status.h"
#include "supportFunctions.h"

#define DAY_SHIFT 1000000
#define MONTH_SHIFT 10000
#define YEAR_SHIFT 1
#define MAX_FRIEND_LATEST_STATUS 10

// Friends functions in Person
 
bool Person::addFriend(Person* newFriend)
{
}
bool Person::removeFriend(Person* dFriend) 
{
}
bool Person::searchFriend(char* fName) 
{
}

// Pages functions in Person

bool Person::addPage(Page* newPage)
{
}


// Status Functions in Persons

void Person::showMyStatus() 
{
	const char* text;
	cout << "My Statuses are:" << endl;
	for (int i = 0; i < logSizeMyStatus; i++)
	{
		text = myStatus[i]->getText();
		cout << "Status " << i + 1 << "# : " << text << endl;
	}
}

bool Person::addStatus()
{
}
bool Person::postStatus() 
{
}

// add space to lists functions
bool Person::addSpaceFriendList()
{
	int newSize;
	if (phySizeFriends == 0)
		newSize = 1;
	else
		newSize = phySizeFriends*2;

	friends = new Person * [newSize];
	bool allocateSuccess = checkAllocate(friends);
	if (allocateSuccess)
		phySizeFriends = newSize;
	return allocateSuccess;
}
bool Person::addSpaceMyStatusList()
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
bool Person::addSpaceFriendsStatusList()
{
	if (phySizeFriendsStatus == MAX_FRIEND_LATEST_STATUS) // check if trying to add more space than defined
		return false;
	int newSize;
	if (phySizeFriendsStatus == 0)
		newSize = 1;
	else
	{
		newSize = phySizeFriendsStatus * 2;
		if (newSize > MAX_FRIEND_LATEST_STATUS)
			newSize = MAX_FRIEND_LATEST_STATUS;
	}
	FriendsStatus = new Status * [newSize];
	bool allocateSuccess = checkAllocate(FriendsStatus);
	if (allocateSuccess)
		phySizeFriendsStatus = newSize;
	return allocateSuccess;
}
bool Person::addSpaceInterestPagesList()
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

// setters/getters
bool Person::setName(char* str)
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
const char* Person::getName()
{
	return name;
}
bool Person::setBirthDay(int day, int month, int year)
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



