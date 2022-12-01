#include <iostream>
using namespace std;
#include "supportFunctions.h"
#include "Facebook.h"

// ----------------------------------------- Support Functions for Actions -----------------------------------------

void printMenu()
{
	cout << CREATE_MEMBER <<" - create Member" << endl;
	cout << CREATE_PAGE << " - create Page" << endl; 
	cout << CREATE_STATUS_FOR_FRIEND << " - create Status for Friend" << endl;
	cout << CREATE_STATUS_FOR_PAGE << " - create Status for Page" << endl;
	cout << SHOW_FRIEND_STATUS <<" - Show of Friend Status" << endl;
	cout << SHOW_PAGE_STATUS <<" - Show of Page Status" << endl;
	cout << SHOW_LATEST10_OF_FRIEND << " - Show of Friends 10 Latest Status: " << endl;
	cout << MAKE_FRIENDSHIP << " - make friendship with member" << endl;
	cout << CANCEL_FRIENDSHIP <<" - cancel friendship with member" << endl;
	cout << FOLLOW_PAGE << " - make member follow Fan Page" << endl;
	cout << UNFOLLOW_PAGE << " - make member unfollow Fan Page:" << endl;
	cout << SHOW_ALL_MEMBERS << " - show all members" << endl;
	cout << SHOW_ALL_FANS_OF_PAGE << " - show all fan pages" << endl;
	cout << SHOW_ALL_MEMBERS_FOLLOW_PAGE << " - show all registers to Fan Page" << endl;
	cout << SHOW_FRIENDS_OF_FRIEND << " - show friends of friend" << endl;
	cout << EXIT << " - exit" << endl;
}

void actionsForMenu(char selection, Facebook& facebook)
{
	/// <summary>
	/// Function get the choose from user and call the function related to this act
	/// </summary>
	switch (selection)
	{
	case CREATE_MEMBER:
		if (createMember(facebook) == false)
			cout << "Member creating failed !" << endl;
		else
			cout << "Member created !" << endl << endl;
		break;
	case CREATE_PAGE:
		if (createPage(facebook) == false)
			cout << "Page creating failed !" << endl;
		else
			cout << "Page created !" << endl << endl;
		break;
	case CREATE_STATUS_FOR_FRIEND:
		if (createStatusForMember(facebook))
			cout << "Member Status Created" << endl;
		else
			cout << "Member Status Creating failed !" << endl << endl;
		break;
	case CREATE_STATUS_FOR_PAGE:
		if(createStatusForPage(facebook))
			cout << "Page Status Created" << endl;
		else
			cout << "Page Status Creating failed !" << endl << endl;
		break;
	case SHOW_FRIEND_STATUS:
		showStatusOfMember(facebook); break;
	case SHOW_PAGE_STATUS:
		showStatusOfPage(facebook); break;
	case SHOW_LATEST10_OF_FRIEND:
		showLastStatusOfFriends(facebook); break;
	case MAKE_FRIENDSHIP:
		cout << "feature: not supported yet";
		break;
	case CANCEL_FRIENDSHIP:
		cout << "feature: not supported yet";
		break;
	case FOLLOW_PAGE:
		if (followMemberToPage(facebook))
			cout << "Member following on Fan Page was registered" << endl;
		else
			cout << "Member following on Fan Page failed !" << endl;
		break;
	case UNFOLLOW_PAGE:
		if(unfollowMemberToPage(facebook))
			cout << "Member following on Fan Page was cancelled" << endl;
		else
			cout << "Member cancelation following on Fan Page failed !" << endl;
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
		cout << "~*~*~ Your choice isn't in the menu, please try again ~*~*~" << endl << endl;
	}
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

bool getString(char* str, int maxLen)
{
	/// <summary>
	/// Function get pointer to string and max len and get from user the text if is too short ask for type again
	/// </summary>
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
	/// <summary>
	/// Function get string of birthday and return by pointers the day month and year in ints
	/// </summary>
	int num = 0;
	int value = 0;
	for (int i = 0; i < MAX_BIRTHDAY_STR; i++)
	{
		if ('0' <= birthday[i] && birthday[i] <= '9') // if number convert from char to int value (char by char)
		{
			num *= 10;
			num += (int)birthday[i] - '0';
		}
		else if (birthday[i] == '.' || birthday[i] == '/' || birthday[i] == '\n' || birthday[i] == '\0') // check for splicer like / or . or end line or end of text
		{ 
			// check which value we recived and set by pointer the value
			if (value == DAY)
				*day = num;
			else if (value == MONTH)
				*month = num;
			else if (value == YEAR)
				*year = num;
			num = 0; // reset value for next round
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
	/// <summary>
	/// This function ask the user if he would like to see friend list
	/// and show him if said yes
	/// </summary>
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
	/// <summary>
	/// This function ask the user if he would like to see page list
	/// and show him if said yes
	/// </summary>
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

bool putEntersInString(char* text)
{
	int i= ENTERS_FREQ,len = strlen(text);
	while (i<len) // run on the string in jumps till i bigger than len of text
	{
		if (text[i] == ' ') // if found space we will change it to enter
		{
			text[i] = '\n'; // change space to enter
			i += ENTERS_FREQ; // jump to next time we should hit enter
		}
		else // if not found space we will continue for next char
			i++;
	}
	return true;
}

// --------------------------------------------- Functions for Actions ---------------------------------------------

bool createMember(Facebook& facebook)
{
	char name[MAX_NAME_LEN] = { 0 }, birthday[MAX_BIRTHDAY_STR] = { 0 };
	int day=0, month=0, year=0;
	// ask for name
	cout << "Creating a new Member in Facebook:" << endl << "Please enter a full name (max 30 chars): ";
	getString(name, MAX_NAME_LEN);
	while (facebook.memberNameCheck(name) == true)
	{
		cout << "The name '" << name << "' is already exist, please try a different name" << endl << "Name: ";
		getString(name, MAX_NAME_LEN);
	}
	do // ask for birth day
	{
		cout << "Please enter birthday in format DD.MM.YYYY: " << endl;
		getString(birthday, MAX_BIRTHDAY_STR);
	} while (convertStrToIntDate(birthday, &day, &month, &year) == false);

	return facebook.createMember(name, day, month, year); // create member and return if successed
}

bool createPage(Facebook& facebook) 
{
	char name[MAX_PAGE_NAME_LEN] = { 0 };
	// ask for name of page
	cout << "Creating a new Fan Page in Facebook:" << endl << "Please enter a name for the page (max 30 chars): ";
	getString(name, MAX_PAGE_NAME_LEN);
	while (facebook.pageNameCheck(name) == true)
	{
		cout << "The name '" << name << "' is already exist, please try a different name" << endl << "Name: ";
		getString(name, MAX_PAGE_NAME_LEN);
	}
	return facebook.createFanPage(name); // trying create the name and send if successed
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
	facebook.getMember(name).showMyFriends(); // calling for function of this member to show his friends
}

void showFanPagesOfMember(Facebook& facebook)
{
	char name[MAX_NAME_LEN];
	askForFriendList(facebook);
	cout << "Please type the member name you would like to see the pages this member follow: " << endl;
	getString(name, MAX_NAME_LEN);
	while (facebook.memberNameCheck(name) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type name of member you would like to see the pages this member follow ";
		getString(name, MAX_NAME_LEN);
	}
	facebook.getMember(name).showMyInterestPages(); // calling for function of this member to show his interest pages
}

void showStatusOfMember(Facebook& facebook)
{
	char name[MAX_NAME_LEN];
	askForFriendList(facebook);
	cout << "Please type the member name you would like to see his Status: " << endl;
	getString(name, MAX_NAME_LEN);
	while (facebook.memberNameCheck(name) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type name of member you would like to see his Status ";
		getString(name, MAX_NAME_LEN);
	}
	facebook.getMember(name).showMyStatus(); // calling for function of this member to show his status
}

void showStatusOfPage(Facebook& facebook)
{
	char name[MAX_PAGE_NAME_LEN];
	askForPageList(facebook);
	cout << "Please type the name of page you would like to see his Status: " << endl;
	getString(name, MAX_PAGE_NAME_LEN);
	while (facebook.pageNameCheck(name) == false)
	{
		cout << "This page isn't exist, Please try again." << endl << "Type name of page you would like to see his Status ";
		getString(name, MAX_PAGE_NAME_LEN);
	}
	facebook.getPage(name).showPageStatus(); // calling for function of this page to show his statys
}

void showLastStatusOfFriends(Facebook& facebook)
{
	/// <summary>
	/// The function ask for member from user and the friend show all of his friends statuses
	/// </summary>
	/// <param name="facebook"></param>
	char name[MAX_NAME_LEN];
	askForFriendList(facebook);
	cout << "Please type the member name you would like to see Status of his friends: " << endl;
	getString(name, MAX_NAME_LEN);
	while (facebook.memberNameCheck(name) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type name of member you would like to see Status of his friends: ";
		getString(name, MAX_NAME_LEN);
	}
	facebook.getMember(name).showLastFriendsStatus(); // calling for function of this member to show his friends statuses
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
		cout << "This member isn't exist, Please try again." << endl << "Type name of member you would like to will follow page ";
		getString(memberName, MAX_NAME_LEN);
	}
	// ask for which page to follow
	askForPageList(facebook);
	cout << "Please type the page name you that you would like " << memberName << " will follow: " << endl;
	getString(pageName, MAX_PAGE_NAME_LEN);
	while (facebook.pageNameCheck(pageName) == false)
	{
		cout << "This page isn't exist, Please try again." << endl << "Type the name of page you that you would like " << memberName << "will follow: " << endl;
		getString(pageName, MAX_PAGE_NAME_LEN);
	}
	// create following between member and page
	return facebook.getMember(memberName).addPage(facebook.getPage(pageName)); // make the member follow after the page
}

bool unfollowMemberToPage(Facebook& facebook)
{
	char memberName[MAX_NAME_LEN] = { 0 };
	char pageName[MAX_PAGE_NAME_LEN] = { 0 };
	askForFriendList(facebook);
	// ask for which friend
	cout << "Please type the member name you would like unfollow page " << endl;
	getString(memberName, MAX_NAME_LEN);
	while (facebook.memberNameCheck(memberName) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type name of member you would like unfollow page: ";
		getString(memberName, MAX_NAME_LEN);
	}
	// ask for which page to follow
	facebook.getMember(memberName).showMyInterestPages();
	cout << "Please type the name of page you that you would like " << memberName << " will unfollow: " << endl;
	getString(pageName, MAX_PAGE_NAME_LEN);
	while (facebook.pageNameCheck(pageName) == false)
	{
		cout << "This page isn't exist, Please try again." << endl << "Type the page name you that you would like " << memberName << "will unfollow: " << endl;
		getString(pageName, MAX_PAGE_NAME_LEN);
	}
	// make unfollowing between member and page
	return facebook.getMember(memberName).removePage(facebook.getPage(pageName)); // unfollow the member from the page
}

bool createStatusForMember(Facebook& facebook)
{
	char memberName[MAX_NAME_LEN] = { 0 };
	char statusText[MAX_STATUS_LEN] = { 0 };
	// ask for member
	askForFriendList(facebook);
	cout << "Please type the name of member you would like create status for: " << endl;
	getString(memberName, MAX_NAME_LEN);
	while (facebook.memberNameCheck(memberName) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type name of member you would like unfollow page: ";
		getString(memberName, MAX_NAME_LEN);
	}
	// ask for text to status
	cout << "Please type the Text for the status and hit enter to finish (MAX:"<< MAX_STATUS_LEN-1 << " Chars): " << endl;
	getString(statusText, MAX_STATUS_LEN);
	putEntersInString(statusText); // put \n in the string every fixed chars that defined
	return facebook.getMember(memberName).addStatus(statusText); // create the status for this member with the text typed in
}

bool createStatusForPage(Facebook& facebook)
{
	char pageName[MAX_PAGE_NAME_LEN] = { 0 };
	char statusText[MAX_STATUS_LEN] = { 0 };
	// ask for page
	askForPageList(facebook);
	cout << "Please type the name of fan page you would like create status for: " << endl;
	getString(pageName, MAX_PAGE_NAME_LEN);
	while (facebook.pageNameCheck(pageName) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type name of fan page you would like unfollow page: ";
		getString(pageName, MAX_PAGE_NAME_LEN);
	}
	// ask for text to status
	cout << "Please type the Text for the status and hit enter to finish (MAX:" << MAX_STATUS_LEN - 1 << " Chars): " << endl;
	getString(statusText, MAX_STATUS_LEN);
	putEntersInString(statusText); // put \n in the string every fixed chars that defined
	return facebook.getPage(pageName).addStatus(statusText); // create the status for this page with the text typed in
}



