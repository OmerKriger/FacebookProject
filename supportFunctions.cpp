#include <iostream>
using namespace std;
#include "supportFunctions.h"
#include "Facebook.h"
#include <string.h>

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
	cout << "10 - register member to Fan Page" << endl;
	cout << "11 - unregister member from Fan Page:" << endl;
	cout << "12 - show all members" << endl;
	cout << "13 - show all registers to Fan Page" << endl;
	cout << "14 - show friends of friend" << endl;
	cout << "15 - exit" << endl;
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
	case ADD_MEMBER:

		break;
	case ADD_PAGE:

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
	case REGISTER_FOR_PAGE:

		break;
	case UNREGISTER_FROM_PAGE:

		break;
	case SHOW_ALL_MEMBERS:
		facebook.showAllMembers();
		break;
	case SHOW_ALL_FANS_OF_PAGE:
		facebook.showAllPages();
		break;
	case SHOW_FRIENDS_OF_FRIEND:

		break;
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