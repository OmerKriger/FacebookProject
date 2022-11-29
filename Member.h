#ifndef __Member_H
#define __Member_H
#define DAY_SHIFT 1000000
#define MONTH_SHIFT 10000
#define YEAR_SHIFT 1
#define MAX_FRIEND_LATEST_STATUS 10

#include "Date.h"
enum class sType;
class Status;
class Page; 

class Member
{ 
public:
	Member() = delete;
	Member(const char* name, Date bDay);
	~Member();
	bool addFriend(Member* newFriend);
	bool removeFriend(Member* dFriend);
	bool addPage(Page& newPage);
	bool removePage(const Page& dPage);
	void showMyStatus() const;
	void showMyFriends() const;
	void showMyInterestPages() const;
	void showLastFriendsStatus() const;
	void showMyLastStatuses() const;
	bool addStatus(const char* text, sType type);
	bool addStatus(const char* text);
	int getAmountOfStatus() const { return logSizeMyStatus; }
	const char* getName() const { return name; }
private:
	char* name;
	Date birthDay;
	Status** myStatus;
	Page** InterestPages;
	Member** friends;
	int logSizeFriends, logSizeMyStatus, logSizeInterestPages;
	int phySizeFriends , phySizeMyStatus, phySizeInterestPages;
	bool addSpaceFriendList();
	bool addSpaceMyStatusList();
	bool addSpaceInterestPagesList();
	int searchFriend(char* fName);
	int searchPage(const char* pName);
	bool setName(const char* str);
	//Status* FriendsStatus[MAX_FRIEND_LATEST_STATUS] = { nullptr };; // temp 
	//unsigned char F_S_newestStatusIndex; // set to zero (this index will show us where is the newest status without overwrite the order of array
	//bool postStatus();
};




#endif