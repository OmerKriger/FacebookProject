#ifndef __PAGES_H
#define __PAGES_H
#include "Member.h"
#include "Date.h"
#include "Status.h"
#include "supportFunctions.h"
class Member;
class Status;

class Page
{
	std::string name;
	Member** fans;
	Status** wall;
	int logSizeFans, phySizeFans;
	int logSizeWall, phySizeWall;
	bool setName(const std::string& str);
	int searchFan(const std::string& name); // change after merge with vector.
	bool addSpaceInFans();
	bool addSpaceInWall();
	Page(const Page&);

public:
	Page(const std::string& name);
	~Page();
	bool addFan(Member* member);
	bool removeFan(const std::string& name);
	void showFans() const;
	bool addStatus(const std::string& str); // change after merge with vector.
	void showPageStatus() const;
	const std::string& getName() const;
};



#endif