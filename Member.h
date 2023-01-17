#ifndef __Member_H
#define __Member_H
#include "Date.h"
#include "Exceptions.h"
#include "BackupRecovery.h"
#include <string>
#include <list>
#include <fstream>

enum statusType
{
	TEXT = 1, // equal 1 for start counting from 1 and not zero 
	IMAGE,
	VIDEO
};

class Status;
class Page; 

class Member
{ 
public:
	// C'tors
	Member(const std::string& name, Date bDay) noexcept(false);
	Member(std::ifstream& inFile) noexcept(false);
	~Member();
	// Add/Remove functions
	void addFriend(Member* newFriend) noexcept(false);
	void removeFriend(Member* dFriend) noexcept(false);
	void addPage(Page& newPage) noexcept(false);
	void removePage(const Page& dPage) noexcept(false);
	//Save
	virtual void save(std::ofstream& outFile); // Can't be const - change flag inside
	// Prints
	void showMyStatus() const;
	void showMyFriends() const;
	void showMyInterestPages() const;
	void showLastFriendsStatus() const;
	void showMyLastStatuses() const;
	// Statuses
	void addStatus(const std::string& text, int statusType, std::string& path) noexcept(false);
	void addStatus(Status* status) noexcept(false);

	// Getters
	const std::string& getName() const { return name; }
	const int getAmountOfStatus() const { return (int)myStatus.size(); }
	const int getAmountOfFriends() const { return (int)friends.size(); }
	// Operators
	bool operator<(const Member& other) const;
	bool operator>(const Member& other) const;
	bool operator<(const Page& other) const;
	bool operator>(const Page& other) const;
	Member& operator+=(Member & other);
	Member& operator+=(Page& page);
private:
	std::string name;
	Date birthDay;
	bool isSaved;
	std::list <Status*> myStatus;
	std::list <Page*> InterestPages;
	std::list <Member*> friends;
	Member(const Member&); // here to cancel use
	void setName(const std::string& str) noexcept(false);
};

#endif