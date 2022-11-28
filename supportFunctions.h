#ifndef __SUPPORT_FUNCTIONS_H
#define __SUPPORT_FUNCTIONS_H
// Menu Defines
#define CREATE_MEMBER 1
#define CREATE_PAGE 2
#define CREATE_STATUS_FOR_FRIEND 3
#define CREATE_STATUS_FOR_PAGE 4
#define SHOW_FRIEND_STATUS 5
#define SHOW_PAGE_STATUS 6
#define SHOW_LATEST10_OF_FRIEND 7
#define MAKE_FRIENDSHIP 8
#define CANCEL_FRIENDSHIP 9
#define FOLLOW_PAGE 10
#define UNFOLLOW_PAGE 11
#define SHOW_ALL_MEMBERS 12
#define SHOW_ALL_FANS_OF_PAGE 13
#define SHOW_ALL_MEMBERS_FOLLOW_PAGE 14
#define SHOW_FRIENDS_OF_FRIEND 15
#define EXIT 16
// Some Defines
#define MAX_NAME_LEN 32
#define MAX_PAGE_NAME_LEN 32
#define MAX_BIRTHDAY_STR 11
#define MINIMUM_STRING 3
#define DAY 0
#define MONTH 1
#define YEAR 2
// class forward decleration
class Facebook;
// function declerations
bool checkAllocate(void* ptr);
void printMenu();
void actionsForMenu(char selection, Facebook& facebook);
void* mRealloc(void* ptr, int newSize, int oldSize);
bool getString(char* str, int maxLen);
bool convertStrToIntDate(char* birthday, int* day, int* month, int* year);
void askForFriendList(Facebook& facebook);
void askForPageList(Facebook& facebook);
// Controlling function

bool createMember(Facebook& facebook);
bool createPage(Facebook& facebook);
void showFriendsOfMember(Facebook& facebook);
void showFanPagesOfMember(Facebook& facebook);
bool followMemberToPage(Facebook& facebook);
bool unfollowMemberToPage(Facebook& facebook);

#endif