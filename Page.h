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
	char* name;
	Member** fans;
	Status** wall;
	int logSizeFans, phySizeFans;
	int logSizeWall, phySizeWall;
	bool setName(const char* str);
	int searchFan(const char* name);
	bool addSpaceInFans();
	bool addSpaceInWall();
	Page(const Page&);

public:
	Page(const char* name);
	~Page();
	bool addFan(Member* member);
	bool removeFan(const char* name);
	void showFans() const;
	bool addStatus(const char* str);
	void showPageStatus() const;
	const char* getName() const;
};



#endif