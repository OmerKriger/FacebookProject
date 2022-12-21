#ifndef __FACEBOOK_H
#define __FACEBOOK_H
#include "Member.h"
#include "Page.h"
#include "supportFunctions.h"
#include "Date.h"

#define MATCH 0


class Member;
class Page;

class Facebook 
{
	Member** members;
	Page** fanPages;
	int phySizeMembers, logSizeMembers;
	int phySizeFanPages, logSizeFanPages;
	bool addSpaceForMembers();
	bool addSpaceForFanPages();
	Facebook(Facebook&);
public:
	Facebook();
	~Facebook();
	void __Init__();
	bool createMember(const std::string& name, Date bDay);
	bool createFanPage(const std::string& name);
	void showAllMembers() const;
	void showAllPages() const;
	bool memberNameCheck(const std::string& name);
	bool pageNameCheck(const std::string& name);
	const Member& getMember(const std::string& name) const;
	Member& getMember(const std::string& name);
	const Page& getPage(const std::string& name) const;
	Page& getPage(const std::string& name);
};

#endif
