#include <iostream>
using namespace std;
#include "supportFunctions.h"
#include "Facebook.h"

// ----------------------------------------- Support Functions for Actions -----------------------------------------

void printMenu()
{
	cout << "1 - create Member" << endl;
	cout << "2 - create Page" << endl; 
	cout << "3 - create Status for Friend" << endl;
	cout << "4 - create Status for Page" << endl;
	cout << "5 - Show of Friend Status" << endl;
	cout << "6 - Show of Page Status" << endl;
	cout << "7 - Show of Friends 10 Latest Status: " << endl;
	cout << "8 - make friendship with member" << endl;
	cout << "9 - cancel friendship with member" << endl;
	cout << "10 - make member follow Fan Page" << endl;
	cout << "11 - make member unfollow Fan Page:" << endl;
	cout << "12 - show all members" << endl;
	cout << "13 - show all fan pages" << endl;
	cout << "14 - show all registers to Fan Page" << endl;
	cout << "15 - show friends of friend" << endl;
	cout << "16 - exit" << endl;
}

bool checkAllocate(void* ptr)
{
	if (ptr == nullptr)
	{
		cout << "Allocation failed\n";
		return false;
	}
	else
		return true;
}

void actionsForMenu(char selection, Facebook& facebook)
{
	switch (selection)
	{
	case CREATE_MEMBER:
		if (createMember(facebook) == false)
			cout << "Something gone wrong !" << endl;
		else
			cout << "Member created !" << endl << endl;
		break;
	case CREATE_PAGE:
		if (createPage(facebook) == false)
			cout << "Something gone wrong !" << endl;
		else
			cout << "Page created !" << endl << endl;
		break;
	case CREATE_STATUS_FOR_FRIEND:

		break;
	case CREATE_STATUS_FOR_PAGE:

		break;
	case SHOW_FRIEND_STATUS:

		break;
	case SHOW_PAGE_STATUS:

		break;
	case SHOW_LATEST10_OF_FRIEND:

		break;
	case MAKE_FRIENDSHIP:

		break;
	case CANCEL_FRIENDSHIP:

		break;
	case FOLLOW_PAGE:
		if (followMemberToPage(facebook))
			cout << "Member Following on Fan Page was registered" << endl;
		else
			cout << "Member Following on Fan Page failed !" << endl;
		break;
	case UNFOLLOW_PAGE:
		break;
	case SHOW_ALL_MEMBERS:
		facebook.showAllMembers(); break;
	case SHOW_ALL_FANS_OF_PAGE:
		facebook.showAllPages(); break;
	case SHOW_ALL_MEMBERS_FOLLOW_PAGE:
		showFanPagesOfMember(facebook); break;
	case SHOW_FRIENDS_OF_FRIEND:
		showFriendsOfMember(facebook); break;
	case EXIT: break;
	default:
		cout << "** Your choice isn't in the menu, please try again **" << endl << endl;
	}
}

void* mRealloc(void* ptr, int newSize, int oldSize)
{
	// might be problematic without sizeof()
	void* newPtr = new void* [newSize];
	if (!checkAllocate(newPtr))
		return nullptr;
	newPtr = memcpy(newPtr, ptr, sizeof(void*));
	delete[] ptr;
	return newPtr;
}

bool getString(char* str, int maxLen)
{
	
	cin.getline(str, maxLen);
	while (strlen(str) < MINIMUM_STRING)
	{
		cout << "A minimum length is "<< MINIMUM_STRING << " chars, try again" << endl;
		cin.getline(str, maxLen);
	}
	return true;
}

bool convertStrToIntDate(char* birthday, int* day, int* month, int* year)
{
	int num = 0;
	int value = 0;
	for (int i = 0; i < MAX_BIRTHDAY_STR; i++)
	{
		if ('0' <= birthday[i] && birthday[i] <= '9')
		{
			num *= 10;
			num += (int)birthday[i] - '0';
		}
		else if (birthday[i] == '.' || birthday[i] == '/' || birthday[i] == '\n' || birthday[i] == '\0')
		{
			if (value == DAY)
				*day = num;
			else if (value == MONTH)
				*month = num;
			else if (value == YEAR)
				*year = num;
			num = 0;
			value++; // skip to next value
		}
	}
	if (*day != 0 && *month != 0 && *year != 0)
		return true;
	else
		return false;
}

void askForFriendList(Facebook& facebook)
{
	char answer;
	cout << "Do you need the member lists ? (Y/N): ";
	cin >> answer;
	cin.get();
	while (answer != 'Y' && answer != 'y' && answer != 'n' && answer != 'N')
	{
		cout << "You choose isn't defined, please try again" << endl;
		cout << "Do you need the member lists ? (Y/N): ";
		cin >> answer;
		cin.get();
	}
	if (answer == 'Y' or answer == 'y')
		facebook.showAllMembers();
	cout << endl;
}

void askForPageList(Facebook& facebook)
{
	char answer;
	cout << "Do you need the fan page lists ? (Y/N): ";
	cin >> answer;
	cin.get();
	while (answer != 'Y' && answer != 'y' && answer != 'n' && answer != 'N')
	{
		cout << "You choose isn't defined, please try again" << endl;
		cout << "Do you need the fan page ? (Y/N): ";
		cin >> answer;
		cin.get();
	}
	if (answer == 'Y' or answer == 'y')
		facebook.showAllPages();
	cout << endl;
}

// --------------------------------------------- Functions for Actions ---------------------------------------------

bool createMember(Facebook& facebook)
{
	char name[MAX_NAME_LEN] = { 0 }, birthday[MAX_BIRTHDAY_STR] = { 0 };
	int day=0, month=0, year=0;
	cout << "Creating a new Member in Facebook:" << endl << "Please enter a full name (max 30 chars): ";
	getString(name, MAX_NAME_LEN);
	while (facebook.memberNameCheck(name) == true)
	{
		cout << "The name '" << name << "' is already exist, please try a different name" << endl << "Name: ";
		getString(name, MAX_NAME_LEN);
	}
	do
	{
		cout << "Please enter birthday in format DD.MM.YYYY: " << endl;
		getString(birthday, MAX_BIRTHDAY_STR);
	} while (convertStrToIntDate(birthday, &day, &month, &year) == false);

	return facebook.createMember(name, day, month, year);
}

bool createPage(Facebook& facebook)
{
	char name[MAX_PAGE_NAME_LEN] = { 0 };
	cout << "Creating a new Fan Page in Facebook:" << endl << "Please enter a name for the page (max 30 chars): ";
	getString(name, MAX_PAGE_NAME_LEN);
	while (facebook.pageNameCheck(name) == false)
	{
		cout << "The name '" << name << "' is already exist, please try a different name" << endl << "Name: ";
		getString(name, MAX_PAGE_NAME_LEN);
	}
	return facebook.createFanPage(name);
}

void showFriendsOfMember(Facebook& facebook)
{
	
	char name[MAX_NAME_LEN];
	askForFriendList(facebook);
	cout << "Please type the member name you would like to see his friends: " << endl;
	getString(name, MAX_NAME_LEN);
	while (facebook.memberNameCheck(name) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type name of member you would like to see his friends: ";
		getString(name, MAX_NAME_LEN);
	}
	facebook.getMember(name).showMyFriends();
}

void showFanPagesOfMember(Facebook& facebook)
{
	char name[MAX_PAGE_NAME_LEN];
	askForFriendList(facebook);
	cout << "Please type the member name you would like to see the pages this member follow: " << endl;
	getString(name, MAX_PAGE_NAME_LEN);
	while (facebook.memberNameCheck(name) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type name of member you would like to see the pages this member follow ";
		getString(name, MAX_PAGE_NAME_LEN);
	}
	facebook.getMember(name).showMyInterestPages();
}

bool followMemberToPage(Facebook& facebook)
{
	char memberName[MAX_NAME_LEN] = { 0 };
	char pageName[MAX_PAGE_NAME_LEN] = { 0 };
	askForFriendList(facebook);
	// ask for which friend
	cout << "Please type the member name you would like will follow page " << endl;
	getString(memberName, MAX_NAME_LEN);
	while (facebook.memberNameCheck(memberName) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type name of member you would like to see his friends: ";
		getString(memberName, MAX_NAME_LEN);
	}
	// ask for which page to follow
	askForPageList(facebook);
	cout << "Please type the page name you that you would like " << memberName << " will follow: " << endl;
	getString(pageName, MAX_PAGE_NAME_LEN);
	while (facebook.pageNameCheck(pageName) == false)
	{
		cout << "This page isn't exist, Please try again." << endl << "Type the page name you that you would like " << memberName << "will follow: " << endl;
		getString(pageName, MAX_PAGE_NAME_LEN);
	}
	// create following between member and page
	return facebook.getMember(memberName).addPage(facebook.getPage(pageName));
}

bool unfollowMemberToPage(Facebook& facebook)
{
	return 0;
}

