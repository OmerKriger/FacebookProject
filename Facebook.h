#ifndef __FACEBOOK_H
#define __FACEBOOK_H
#include "Member.h"
#include "Page.h"
#include "Date.h"
#include <list>

#define TEST 1 // TEST == 0 is no test setup

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
	bool createMember(const std::string& name, Date bDay);
	bool createFanPage(const std::string& name);
	void showAllMembers() const;
	void showAllPages() const;
	bool memberNameCheck(const std::string& name) const;
	bool pageNameCheck(const std::string& name) const;
	const Member& getMember(const std::string& name) const;
	Member& getMember(const std::string& name);
	const Page& getPage(const std::string& name) const;
	Page& getPage(const std::string& name);
};

#endif
