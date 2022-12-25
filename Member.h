#ifndef __Member_H
#define __Member_H
#include "Date.h"
#include <string>
#include <list>

class Status;
class Page; 

class Member
{ 
public:
	// C'tors
	Member(const std::string& name, Date bDay);
	~Member();
	// Add/Remove functions
	bool addFriend(Member* newFriend);
	bool removeFriend(Member* dFriend);
	bool addPage(Page& newPage);
	bool removePage(const Page& dPage);
	// Prints
	void showMyStatus() const;
	void showMyFriends() const;
	void showMyInterestPages() const;
	void showLastFriendsStatus() const;
	void showMyLastStatuses() const;
	// Statuses
	bool addStatus(const std::string& text);
	// Getters
	const std::string& getName() const { return name; }
	const int getAmountOfStatus() const { return (int)myStatus.size(); }
	// Operators
	bool operator<(const Member& other) const;
	bool operator>(const Member& other) const;
	bool operator<(const Page& other) const;
	bool operator>(const Page& other) const;


private:
	std::string name;
	Date birthDay;
	std::list <Status*> myStatus;
	std::list <Page*> InterestPages;
	std::list <Member*> friends;
	Member(const Member&);
	bool setName(const std::string& str);
};




#endif