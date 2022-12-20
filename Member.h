#ifndef __Member_H
#define __Member_H
#include "Date.h"

enum class sType;
class Status;
class Page; 

class Member
{ 
public:
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
	const int& getAmountOfStatus() const { return logSizeMyStatus; }
	const char* getName() const { return name; }

private:
	char* name;
	Date birthDay;
	Status** myStatus;
	Page** InterestPages;
	Member** friends;
	Member(const Member&);
	int logSizeFriends, logSizeMyStatus, logSizeInterestPages;
	int phySizeFriends , phySizeMyStatus, phySizeInterestPages;
	bool addSpaceFriendList();
	bool addSpaceMyStatusList();
	bool addSpaceInterestPagesList();
	int searchFriend(char* fName);
	int searchPage(const char* pName);
	bool setName(const char* str);
};




#endif