#ifndef __Member_H
#define __Member_H
#include "Date.h"
#include <string>


enum class sType;
class Status;
class Page; 

class Member
{ 
public:
	Member(const std::string& name, Date bDay);
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
	bool addStatus(const std::string& text, sType type);
	bool addStatus(const std::string& text);
	const int& getAmountOfStatus() const { return logSizeMyStatus; }
	const std::string& getName() const { return name; }

private:
	std::string name;
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
	int searchFriend(const std::string& fName); //need to check if can add const // change after merge with vectors
	int searchPage(const std::string& pName); // change after merge with vectors
	bool setName(const std::string& str);
};




#endif