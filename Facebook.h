#ifndef __FACEBOOK_H
#define __FACEBOOK_H
class Page;
class Member;

class Facebook 
{
	Member** members;
	Page** fanPages;
	int pSizeMembers, lSizeMembers;
	int pSizeFanPages, lSizeFanPages;
	bool addSpaceForMembers();
	bool addSpaceForFanPages();
	bool memberNameCheck(const char* name);
	bool pageNameCheck(const char* name);
	Facebook(Facebook&);
public:
	Facebook();
	void __Init__();
	bool createMember(const char* name, int day, int month, int year);
	bool createFanPage(const char* name);
	void showAllFriends() const;
	void showAllPages() const;
	bool menu(char selection);
	void printMenu() const;
};

#endif
