#ifndef __FACEBOOK_H
#define __FACEBOOK_H
#include "Member.h"
#include "Page.h"
#include "Date.h"
#include "Exceptions.h"
#include <list>

#define TEST 1 // TEST == 0 is no test setup
#define COMPARE_TEST 0

class Member;
class Page;

class Facebook 
{
	std::list<Member*> members;
	std::list<Page*> fanPages;
	Facebook(const Facebook&);
	void testCompareOperators()								const;
public:
	~Facebook();
	Facebook()												noexcept(false);
	void __Init__()											noexcept(false);
	void createMember(const std::string& name, Date bDay)	noexcept(false);
	void createFanPage(const std::string& name)				noexcept(false);
	void showAllMembers()									const;
	void showAllPages()										const;
	bool memberNameCheck(const std::string& name)			const;
	bool pageNameCheck(const std::string& name)				const;
	const Member& getMember(const std::string& name)		const noexcept(false);
	Member& getMember(const std::string& name)				noexcept(false);
	const Page& getPage(const std::string& name)			const noexcept(false);
	Page& getPage(const std::string& name)					noexcept(false);
};

#endif
