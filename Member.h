#ifndef __Member_H
#define __Member_H
#include "Date.h"
#include <list>

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
	const int& getAmountOfStatus() const { return (int)myStatus.size(); }
	const char* getName() const { return name; }

private:
	char* name;
	Date birthDay;
	std::list <Status*> myStatus;
	std::list <Page*> InterestPages;
	std::list <Member*> friends;
	Member(const Member&);
	bool setName(const char* str);
};




#endif