#ifndef __FACEBOOK_H
#define __FACEBOOK_H
#include "Member.h"
#include "Page.h"
#include "supportFunctions.h"
#include "Date.h"
class Member;
class Page;

class Facebook 
{
	Member** members;
	Page** fanPages;
	int pSizeMembers, lSizeMembers;
	int pSizeFanPages, lSizeFanPages;
	bool addSpaceForMembers();
	bool addSpaceForFanPages();
	Facebook(Facebook&);
public:
	Facebook();
	~Facebook();
	void __Init__();
	bool createMember(const char* name, int day, int month, int year);
	bool createFanPage(const char* name);
	void showAllMembers() const;
	void showAllPages() const;
	bool memberNameCheck(const char* name);
	bool pageNameCheck(const char* name);
	const Member& getMember(const char* name) const;
	Member& getMember(const char* name);
	const Page& getPage(const char* name) const;
	Page& getPage(const char* name);
};

#endif
