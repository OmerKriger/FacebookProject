#ifndef __FACEBOOK_H
#define __FACEBOOK_H
#include "Member.h"
#include "Page.h"
#include "supportFunctions.h"
#include "Date.h"
#include <list>

#define TEST 1 // TEST == 0 is no test setup
#define MATCH 0


class Member;
class Page;

class Facebook 
{
	std::list<Member*> members;
	std::list<Page*> fanPages;
	Facebook(const Facebook&);
public:
	Facebook();
	~Facebook();
	void __Init__();
	bool createMember(const char* name, Date bDay);
	bool createFanPage(const char* name);
	void showAllMembers() const;
	void showAllPages() const;
	bool memberNameCheck(const char* name) const;
	bool pageNameCheck(const char* name) const;
	const Member& getMember(const char* name) const;
	Member& getMember(const char* name);
	const Page& getPage(const char* name) const;
	Page& getPage(const char* name);
};

#endif
