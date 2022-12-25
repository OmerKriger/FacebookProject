#ifndef __UTILITIES_H
#define __UTILITIES_H
#include <string>
#include "Facebook.h"
using namespace std;

// enum declerations
enum Menu // Menu Defines
{  
	CREATE_MEMBER = 1, // equal 1 for start counting from 1 and not zero 
	CREATE_PAGE,
	CREATE_STATUS_FOR_FRIEND, 
	CREATE_STATUS_FOR_PAGE, 
	SHOW_FRIEND_STATUS, 
	SHOW_PAGE_STATUS, 
	SHOW_LATEST10_OF_FRIEND, 
	MAKE_FRIENDSHIP,
	CANCEL_FRIENDSHIP,
	FOLLOW_PAGE,
	UNFOLLOW_PAGE,
	SHOW_ALL_MEMBERS,
	SHOW_ALL_FANS_OF_PAGE,
	SHOW_ALL_MEMBERS_FOLLOW_PAGE,
	SHOW_FRIENDS_OF_FRIEND,
	EXIT
};
enum DefinesNum
{
	NOT_FOUND = -1,
	MATCH = 0,
	DAY = 1,
	MONTH = 2,
	YEAR = 3,
	MINIMUM_STRING = 3,
	AMOUNT_SHOW_FRIENDS_STATUSES = 10,
	MAX_BIRTHDAY_STR = 11,
	MAX_NAME_LEN = 32,
	MAX_PAGE_NAME_LEN = 32,
	ENTERS_FREQ = 60,
	MAX_STATUS_LEN = 501,
};
enum DefinesChars
{

	YES_ANSWER_UPPER = 'Y',
	YES_ANSWER_LOWER = 'y',
	NO_ANSWER_UPPER = 'N',
	NO_ANSWER_LOWER = 'n',
};

class Utilities 
{
private:
	Facebook facebook;
public:
	// function declerations
	bool checkAllocate(void* ptr) const;
	void printMenu() const;
	void actionsForMenu(char selection);
	bool getString(std::string& str) const;
	bool convertStrToIntDate(string birthday, int* day, int* month, int* year);
	void askForFriendList() const;
	void askForPageList() const;
	bool putEntersInString(string& text);
	
	// Controlling function
	bool createMember();
	bool createPage();
	void showFriendsOfMember() const;
	void showFanPagesOfMember() const;
	void showStatusOfMember() const;
	void showStatusOfPage() const;
	void showLastStatusOfFriends() const;
	void showAllFansOfPage() const;
	bool followMemberToPage();
	bool unfollowMemberToPage();
	bool createStatusForMember();
	bool createStatusForPage();
	bool setFriendship();
	bool deleteFriendship();

};
#endif
