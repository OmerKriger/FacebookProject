#ifndef __PAGES_H
#define __PAGES_H
#include "Member.h"
#include "Date.h"
#include "Status.h"
#include "supportFunctions.h"
#include <list>
#include <algorithm>
class Member;
class Status;

class Page
{
	char* name;
	list<Member*> fans;
	list<Status*> wall;
	bool setName(const char* str);
	Page(const Page&);

public:
	Page(const char* name);
	~Page();
	bool addFan(Member* member);
	bool removeFan(Member* member);
	void showFans() const;
	bool addStatus(const char* str);
	void showPageStatus() const;
	const char* getName() const;
};



#endif