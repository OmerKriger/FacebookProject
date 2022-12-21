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
	std::string name;
  list<Member*> fans;
	list<Status*> wall;
	bool setName(const std::string& str);
	int searchFan(const std::string& name); // change after merge with vector.
	Page(const Page&);
public:
	Page(const std::string& name);
	~Page();
	bool addFan(Member* member);
	bool removeFan(Member* member);
	void showFans() const;
	bool addStatus(const std::string& str); // change after merge with vector.
	void showPageStatus() const;
	const std::string& getName() const;
};



#endif