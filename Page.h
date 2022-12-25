#ifndef __PAGES_H
#define __PAGES_H
#include "Member.h"
#include "Status.h"
#include <list>
#include <string>
class Member;
class Status;

class Page
{
	// Data
	std::string name;
	std::list<Member*> fans;
	std::list<Status*> wall;
	// Setters
	bool setName(const std::string& str);
	// C'tors
	Page(const Page&);
public:
	// C'tors
	Page(const std::string& name);
	~Page();
	// Add/Remove
	bool addFan(Member* member);
	bool removeFan(Member* member);
	bool addStatus(const std::string& str);
	// Prints
	void showFans() const;
	void showPageStatus() const;
	// Getters
	const std::string& getName() const;
	int getSizeOfFans() const;
	// Operators
	bool operator<(const Page& other) const;
	bool operator>(const Page& other) const;
	bool operator<(const Member& other) const;
	bool operator>(const Member& other) const;

};



#endif