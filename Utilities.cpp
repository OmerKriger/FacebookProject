#include <iostream>
using namespace std;
#include "Utilities.h"
#include "Exceptions.h"

// ----------------------------------------- Support Functions for Actions -----------------------------------------
void Utilities::printMenu() const
{
	cout << Menu::CREATE_MEMBER << " - create Member" << endl;
	cout << Menu::CREATE_PAGE << " - create Page" << endl;
	cout << Menu::CREATE_STATUS_FOR_FRIEND << " - create Status for a Friend" << endl;
	cout << Menu::CREATE_STATUS_FOR_PAGE << " - create Status for a Page" << endl;
	cout << Menu::SHOW_FRIEND_STATUS << " - Show member Status" << endl;
	cout << Menu::SHOW_PAGE_STATUS << " - Show Page Status" << endl;
	cout << Menu::SHOW_LATEST10_OF_FRIEND << " - Show 10 Latest Status of a member's friends" << endl;
	cout << Menu::MAKE_FRIENDSHIP << " - befriend a member" << endl;
	cout << Menu::CANCEL_FRIENDSHIP << " - unfriend a member" << endl;
	cout << Menu::FOLLOW_PAGE << " - make member follow Fan Page" << endl;
	cout << Menu::UNFOLLOW_PAGE << " - make member unfollow Fan Page" << endl;
	cout << Menu::SHOW_ALL_MEMBERS << " - show all members" << endl;
	cout << Menu::SHOW_ALL_FANS_OF_PAGE << " - show all fan pages" << endl;
	cout << Menu::SHOW_ALL_MEMBERS_FOLLOW_PAGE << " - show all followers of Fan Page" << endl;
	cout << Menu::SHOW_FRIENDS_OF_FRIEND << " - show friend list of a member" << endl;
	cout << Menu::EXIT << " - exit" << endl;
}

void Utilities::actionsForMenu(char selection)
{
	/// <summary>
	/// Function get the choose from user and call the function related to this act
	/// </summary>
	switch (selection)
	{
	case Menu::CREATE_MEMBER:
		try
		{
			createMember();
			cout << "Member created!" << endl << endl;
		}
		catch (...) 
		{
			cout << "Member creating failed!" << endl;
		}
		break;
	case Menu::CREATE_PAGE:
		try
		{
			createPage();
			cout << "Page created!" << endl << endl;
		}
		catch (...) 
		{
			cout << "Page creating failed!" << endl;
		}
		break;
	case Menu::CREATE_STATUS_FOR_FRIEND:
		try
		{
			createStatusForMember();
			cout << "Member Status Created" << endl;
		}
		catch (...) 
		{
			cout << "Member Status Creating failed!" << endl << endl;
		}
		break;
	case Menu::CREATE_STATUS_FOR_PAGE:
		try
		{
			createStatusForPage();
			cout << "Page Status Created" << endl;
		}
		catch (...) 
		{
			cout << "Page Status Creating failed!" << endl << endl;
		}
		break;
	case Menu::SHOW_FRIEND_STATUS:
		showStatusOfMember(); break;
	case Menu::SHOW_PAGE_STATUS:
		showStatusOfPage(); break;
	case Menu::SHOW_LATEST10_OF_FRIEND:
		showLastStatusOfFriends(); break;
	case Menu::MAKE_FRIENDSHIP:
		try
		{
			setFriendship();
			cout << "Friendship Created" << endl;
		}
		catch (...) 
		{
			cout << "Friendship Creation failed" << endl << endl;
		}
		break;
	case Menu::CANCEL_FRIENDSHIP:
		try
		{
			deleteFriendship();
			cout << "Friendship deleted" << endl;
		}
		catch (...) 
		{
			cout << "Friendship deletion failed" << endl << endl;
		}
		break;
	case Menu::FOLLOW_PAGE:
		try
		{
			followMemberToPage();
			cout << "The member now follows the Fan Page" << endl;
		}
		catch (...) 
		{
			cout << "Member's follow request failed" << endl;
		}
		break;
	case Menu::UNFOLLOW_PAGE:
		try {
			unfollowMemberToPage();
			cout << "Member's unfollowed the Fan Page successfully" << endl;
		}
		catch (...) 
		{
			cout << "Member's unfollow request failed" << endl;
		}
		break;
	case Menu::SHOW_ALL_MEMBERS:
		facebook.showAllMembers(); break;
	case Menu::SHOW_ALL_FANS_OF_PAGE:
		facebook.showAllPages(); break;
	case Menu::SHOW_ALL_MEMBERS_FOLLOW_PAGE:
		showAllFansOfPage(); break;
	case Menu::SHOW_FRIENDS_OF_FRIEND:
		showFriendsOfMember(); break;
	case Menu::EXIT: break;
	default:
		cout << "~*~*~ Your choice isn't in the menu, please try again ~*~*~" << endl << endl;
	}
}

bool Utilities::checkAllocate(void* ptr) const
{
	if (ptr == nullptr)
	{
		cout << "Allocation failed ";
		return false;
	}
	else
		return true;
}

bool Utilities::getString(string& str) const
{
	/// <summary>
	/// Function get a string and max len and get from user the text if is too short ask for type again
	/// </summary>
	getline(cin, str);
	while (str.size() < MINIMUM_STRING)
	{
		cout << "A minimum length is "<< MINIMUM_STRING << " chars, try again" << endl;
		getline(cin, str);
	}
	return true;
}

void Utilities::convertStrToIntDate(string birthday, int* day, int* month, int* year) noexcept(false)
{
	/// <summary>
	/// Function get string of birthday and return by pointers the day month and year in ints
	/// </summary>
	int num = 0;
	int value = DAY;
	for (int i = 0; i < MAX_BIRTHDAY_STR && i <= birthday.size(); i++)
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
		else 
		{
			throw DateException("Invalid date: Date not format wrong");
		}
	}
	if (*day == 0 || *month == 0 || *year == 0 || *year < 1000)
		throw DateException("Invalid date");
}

void Utilities::askForFriendList() const
{
	/// <summary>
	/// This function ask the user if he would like to see friend list
	/// and show him if said yes
	/// </summary>
	char answer;
	cout << "Do you need the member lists ? (Y/N): ";
	cin >> answer;
	cin.get();
	while (answer != YES_ANSWER_UPPER && answer != YES_ANSWER_LOWER && answer != NO_ANSWER_LOWER && answer != NO_ANSWER_UPPER)
	{
		cout << "You choice isn't defined, please try again" << endl;
		cout << "Do you need the member lists ? (Y/N): ";
		cin >> answer;
		cin.get();
	}
	if (answer == 'Y' or answer == 'y')
		facebook.showAllMembers();
	cout << endl;
}

void Utilities::askForPageList() const
{
	/// <summary>
	/// This function ask the user if he would like to see page list
	/// and show him if said yes
	/// </summary>
	char answer;
	cout << "Do you need the fan page lists ? (Y/N): ";
	cin >> answer;
	cin.get();
	while (answer != YES_ANSWER_UPPER && answer != YES_ANSWER_LOWER && answer != NO_ANSWER_LOWER && answer != NO_ANSWER_UPPER)
	{
		cout << "You choice isn't defined, please try again" << endl;
		cout << "Do you need the fan page ? (Y/N): ";
		cin >> answer;
		cin.get();
	}
	if (answer == 'Y' or answer == 'y')
		facebook.showAllPages();
	cout << endl;
}

bool Utilities::putEntersInString(string& text)
{
	int i= ENTERS_FREQ, len = text.size();
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

void Utilities::createMember()
{
	string name, birthday;
	bool isValid = false;
	int day=0, month=0, year=0;
	// ask for name
	cout << "Creating a new Member in Facebook:" << endl;
	cout << "Please enter a full name (max 30 chars): " << endl;
	getString(name);
	while (facebook.memberNameCheck(name) == true)
	{
		cout << "This member name is already exist, Please try again." << endl;
		cout << "Please enter a full name (max 30 chars): " << endl;
		getString(name);
	} 
	while (isValid == false)
	{

		cout << "Please enter birthday in format DD.MM.YYYY: " << endl;
		getString(birthday);
		try
		{
			convertStrToIntDate(birthday, &day, &month, &year);
			Date bDay(day, month, year);
			facebook.createMember(name, bDay);
			isValid = true;
		}
		catch (DateException& e)
		{
			cout << e.what() << ", please try again" << endl;
		}
		catch (MemberException& e)
		{
			throw e;
		}
		catch (FacebookException& e)
		{
			cout << e.what() << ", please try again" << endl;
		}
		catch (SystemException& e)
		{
			throw e;
		}
		catch (...)
		{
			cout << "Unknown Error";
		}
	}
}

void Utilities::createPage()
{
	string name;
	bool isValid = false;
	// ask for name of page
	cout << "Creating a new Fan Page in Facebook:" << endl;
	while (isValid == false)
	{
		cout << "Please enter a name for the page (max 30 chars): ";
		getString(name);
		try
		{
			facebook.createFanPage(name);
			isValid = true;
		}
		catch (FacebookException& e)
		{
			cout << e.what() << ", please try again" << endl;
		}
		catch (PageException& e)
		{
			throw e;
		}
		catch (SystemException& e)
		{
			throw e;
		}
		catch (...)
		{
			cout << "Unknown Error";
		}
	}
}

void Utilities::showFriendsOfMember() const
{
	string name;
	askForFriendList();
	cout << "Please Type a name of a member to see his friends:: " << endl;
	getString(name);
	while (facebook.memberNameCheck(name) == false)
	{
		cout << "This member doesn't exist, Please try again." << endl << "Type a name of a member to see his friends: ";
		getString(name);
	}
	facebook.getMember(name).showMyFriends(); // calling for function of this member to show his friends
}

void Utilities::showFanPagesOfMember() const
{
	string name;
	askForFriendList();
	cout << "Please type a member name to see the pages he follows: " << endl;
	getString(name);
	while (facebook.memberNameCheck(name) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type a member name to see the pages he follows ";
		getString(name);
	}
	facebook.getMember(name).showMyInterestPages(); // calling for function of this member to show his interest pages
}

void Utilities::showAllFansOfPage() const
{
	string name;
	askForPageList();
	// ask for which page to follow
	cout << "Please type the name of the page to see who follows it: " << endl;
	getString(name);
	while (facebook.pageNameCheck(name) == false)
	{
		cout << "This page isn't exist, Please try again." << endl << "Please type the name of the page to see who follows it : " << endl;
		getString(name);
	}
	facebook.getPage(name).showFans();
}

void Utilities::showStatusOfMember() const
{
	string name;
	askForFriendList();
	cout << "Please type a member's name to see his Status: " << endl;
	getString(name);
	while (facebook.memberNameCheck(name) == false)
	{
		cout << "This member doesn't exist, Please try again." << endl << "Type a member's name you would like to see his Status ";
		getString(name);
	}
	facebook.getMember(name).showMyStatus(); // calling for function of this member to show his status
}

void Utilities::showStatusOfPage() const
{
	string name;
	askForPageList();
	cout << "Please type a name of a page to see his Status: " << endl;
	getString(name);
	while (facebook.pageNameCheck(name) == false)
	{
		cout << "This page isn't exist, Please try again." << endl << "Type a name of a page to see his Status ";
		getString(name);
	}
	facebook.getPage(name).showPageStatus(); // calling for function of this page to show his statys
}

void Utilities::setFriendship()
{
	string nameSource, nameDest;
	askForFriendList();
	cout << "Please type the name of the first member: " << endl;
	getString(nameSource);
	while (facebook.memberNameCheck(nameSource) == false)
	{
		cout << "This member doesn't exist, Please try again." << endl << "Please type the name of the first member: ";
		getString(nameSource);
	}
	cout << "Please type the name of the second member: " << endl;
	getString(nameDest);
	bool samePerson = (nameDest == nameSource ? true : false);
	while (facebook.memberNameCheck(nameDest) == false || samePerson == true)
	{
		if (samePerson)
			cout << "Member can not be friend of himself, Please try again." << endl;
		else
			cout << "This member doesn't exist, Please try again." << endl;
		cout << "Please type the name of the second member: ";
		getString(nameDest);
		samePerson = (nameDest == nameSource ? true : false);
	}
	try 
	{
		facebook.getMember(nameSource) += facebook.getMember(nameDest);
	}
	catch (MemberException& e)
	{
		cout << e.what() << endl;
		throw e;
	}
	catch (SystemException& e)
	{
		throw e;
	}
	catch (...)
	{
		cout << "Unknown Error";
	}
}

void Utilities::deleteFriendship()
{
	string nameSource, nameDest;
	askForFriendList();
	cout << "Please type the name of the first member: " << endl;
	getString(nameSource);
	while (facebook.memberNameCheck(nameSource) == false)
	{
		cout << "This member doesn't exist, Please try again." << endl << "Please type the name of the first member: ";
		getString(nameSource);
	}
	cout << "Please type the name of the second member: " << endl;
	getString(nameDest);
	while (facebook.memberNameCheck(nameDest) == false)
	{
		cout << "This member doesn't exist, Please try again." << endl << "Please type the name of the second member: ";
		getString(nameDest);
	}
	try 
	{
		facebook.getMember(nameSource).removeFriend(&(facebook.getMember(nameDest)));
	}
	catch (MemberException& e)
	{
		cout << e.what() << endl;
		throw e;
	}
	catch (SystemException& e)
	{
		throw e;
	}
	catch (...)
	{
		cout << "Unknown Error";
	}
}

void Utilities::showLastStatusOfFriends() const
{
	/// <summary>
	/// The function ask for member from user and the friend show all of his friends statuses
	/// </summary>
	/// <param name="facebook"></param>
	string name;
	askForFriendList();
	cout << "Please type a member's name to see the Status of his friends: " << endl;
	getString(name);
	while (facebook.memberNameCheck(name) == false)
	{
		cout << "This member doesn't exist, Please try again." << endl << "Please type a member's name to see the Status of his friends: ";
		getString(name);
	}
	facebook.getMember(name).showLastFriendsStatus(); // calling for function of this member to show his friends statuses
}

void Utilities::followMemberToPage()
{
	string memberName, pageName;
	askForFriendList();
	// ask for which friend
	cout << "Please type a member's name you would like to follow a page " << endl;
	getString(memberName);
	while (facebook.memberNameCheck(memberName) == false)
	{
		cout << "This member doesn't exist, Please try again." << endl << "Type a member's name you would like to follow a page ";
		getString(memberName);
	}
	// ask for which page to follow
	askForPageList();
	cout << "Please type the page name that you would like " << memberName << " to follow: " << endl;
	getString(pageName);
	while (facebook.pageNameCheck(pageName) == false)
	{
		cout << "This page isn't exist, Please try again." << endl << "Type the name of  a page that you would like " << memberName << " to follow: " << endl;
		getString(pageName);
	}
	// create following between member and page
	try
	{
		facebook.getMember(memberName) += facebook.getPage(pageName);
	}
	catch (MemberException& e)
	{
		cout << e.what() << endl;
		throw e;
	}
	catch (PageException& e)
	{
		cout << e.what() << endl;
		throw e;
	}
	catch (SystemException& e)
	{
		throw e;
	}
	catch (...)
	{
		cout << "Unknown Error";
	}
}

void Utilities::unfollowMemberToPage()
{
	string memberName, pageName;
	askForFriendList();
	// ask for which friend
	cout << "Please type the member name that you would like to unfollow a page " << endl;
	getString(memberName);
	while (facebook.memberNameCheck(memberName) == false)
	{
		cout << "This member isn't exist, Please try again." << endl << "Type name of member you would like to unfollow a page: ";
		getString(memberName);
	}
	// ask for which page to follow
	facebook.getMember(memberName).showMyInterestPages();
	cout << "Please type the name of the page that you would like " << memberName << " to unfollow: " << endl;
	getString(pageName);
	while (facebook.pageNameCheck(pageName) == false)
	{
		cout << "This page doesn't exist, Please try again." << endl << "Type the page's name that you would like " << memberName << "to unfollow: " << endl;
		getString(pageName);
	}
	// make unfollowing between member and page
	try
	{
		facebook.getMember(memberName).removePage(facebook.getPage(pageName)); // unfollow the member from the page
	}
	catch (MemberException& e)
	{
		cout << e.what() << endl;
		throw e;
	}
	catch (PageException& e)
	{
		cout << e.what() << endl;
		throw e;
	}
	catch (SystemException& e)
	{
		throw e;
	}
	catch (...)
	{
		cout << "Unknown Error";
	}
}

void Utilities::createStatusForMember()
{
	string memberName, statusText, path = "";
	int statusType;
	// ask for member
	askForFriendList();
	cout << "Please type the name of a member to create status: " << endl;
	getString(memberName);
	while (facebook.memberNameCheck(memberName) == false)
	{
		cout << "This member doesn't exist, Please try again." << endl << "Please type the name of a member to create status: ";
		getString(memberName);
	}
	cout << "Choose status type,  press 1 for text, press 2 for image, press 3 for video: ";
	cin >> statusType;
	getchar(); // to flush buffer.
	while (statusType != 1 && statusType != 2 && statusType != 3)
	{
		cout << "Invalid choice, try again: ";
		cin >> statusType;
	}
	if (statusType != 1)
	{
		cout << "Please enter Path: ";
		getString(path);
	}
	cout << "Please type the Text and press enter to finish (MAX:"<< MAX_STATUS_LEN-1 << " Chars): " << endl;
	getString(statusText);
	putEntersInString(statusText); // put \n in the string every fixed chars that defined
	try
	{
		facebook.getMember(memberName).addStatus(statusText, statusType, path); // create the status for this member with the text typed in
	}
	catch (StatusException& e)
	{
		cout << e.what() << endl;
		throw e;
	}
	catch (SystemException& e)
	{
		throw e;
	}
	catch (...)
	{
		cout << "Unknown Error";
	}
}

void Utilities::createStatusForPage()
{
	string pageName, statusText;
	// ask for page
	askForPageList();
	cout << "Please type the name of a fan page to create status: " << endl;
	getString(pageName);
	while (facebook.pageNameCheck(pageName) == false)
	{
		cout << "This page doesn't exist, Please try again." << endl << "Please type the name of a fan page to create status: ";
		getString(pageName);
	}
	// ask for text to status
	cout << "Please type the Text and press enter to finish (MAX:" << MAX_STATUS_LEN - 1 << " Chars): " << endl;
	getString(statusText);
	putEntersInString(statusText); // put \n in the string every fixed chars that defined
	try
	{
		facebook.getPage(pageName).addStatus(statusText); // create the status for this page with the text typed in
	}
	catch (StatusException& e)
	{
		cout << e.what() << endl;
		throw e;
	}
	catch (SystemException& e)
	{
		throw e;
	}
	catch (...)
	{
		cout << "Unknown Error";
	}
}




