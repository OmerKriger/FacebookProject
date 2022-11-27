#ifndef __SUPPORT_FUNCTIONS_H
#define __SUPPORT_FUNCTIONS_H
// defines for functions uses
#define ADD_MEMBER 1
#define ADD_PAGE 2
#define CREATE_STATUS_FOR_FRIEND 3
#define CREATE_STATUS_FOR_PAGE 4
#define SHOW_FRIEND_STATUS 5
#define SHOW_PAGE_STATUS 6
#define SHOW_LATEST10_OF_FRIEND 7
#define MAKE_FRIENDSHIP 8
#define CANCEL_FRIENDSHIP 9
#define REGISTER_FOR_PAGE 10
#define UNREGISTER_FROM_PAGE 11
#define SHOW_ALL_MEMBERS 12
#define SHOW_ALL_FANS_OF_PAGE 13
#define SHOW_FRIENDS_OF_FRIEND 14
#define EXIT 15
// class forward decleration
class Facebook;
// function declerations
bool checkAllocate(void* ptr);
void printMenu();
void actionsForMenu(char selection, Facebook& facebook);
void* mRealloc(void* ptr, int newSize, int oldSize);
#endif