#ifndef __FACEBOOK_H
#define __FACEBOOK_H
#include "Member.h"
#include "Page.h"
#include "supportFunctions.h"
#include "Date.h"
#include <vector>

#define MATCH 0


class Member;
class Page;

class Facebook 
{
	std::vector<Member*> members;
	std::vector<Page*> fanPages;
	Facebook(Facebook&);
public:
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
