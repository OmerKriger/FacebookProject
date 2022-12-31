#ifndef __Member_H
#define __Member_H
#include "Date.h"
#include "Exceptions.h"
#include <string>
#include <list>

class Status;
class Page; 

class Member
{ 
public:
	// C'tors
	Member(const std::string& name, Date bDay) noexcept(false);
	~Member();
	// Add/Remove functions
	void addFriend(Member* newFriend) noexcept(false);
	void removeFriend(Member* dFriend) noexcept(false);
	void addPage(Page& newPage) noexcept(false);
	void removePage(const Page& dPage) noexcept(false);
	// Prints
	void showMyStatus() const;
	void showMyFriends() const;
	void showMyInterestPages() const;
	void showLastFriendsStatus() const;
	void showMyLastStatuses() const;
	// Statuses
	void addStatus(const std::string& text) noexcept(false);
	// Getters
	const std::string& getName() const { return name; }
	const int getAmountOfStatus() const { return (int)myStatus.size(); }
	const int getAmountOfFriends() const { return (int)friends.size(); }
	// Operators
	bool operator<(const Member& other) const;
	bool operator>(const Member& other) const;
	bool operator<(const Page& other) const;
	bool operator>(const Page& other) const;
	const Member& operator+=(Member & other);
	const Member& operator+=(Page& page);
private:
	std::string name;
	Date birthDay;
	std::list <Status*> myStatus;
	std::list <Page*> InterestPages;
	std::list <Member*> friends;
	Member(const Member&); // here to cancel use
	void setName(const std::string& str) noexcept(false);
};

#endif