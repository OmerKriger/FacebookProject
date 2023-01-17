#ifndef __PAGES_H
#define __PAGES_H
#include <list>
#include <string>
#include "Member.h"

class Date;
class Status;

class Page
{
	// Data
	std::string name;
	mutable bool isSaved;
	std::list<Member*> fans;
	std::list<Status*> wall;
	// Setters
	void setName(const std::string& str) noexcept(false);
	// C'tors
	Page(const Page&);
public:
	// C'tors
	Page(const std::string& name) noexcept(false);
	Page(std::ifstream& inFile) noexcept(false);
	~Page();
	//Save
	void save(std::ofstream& outFile) const;
	// Add/Remove
	void addFan(Member* member) noexcept(false);
	void removeFan(Member* member) noexcept(false);
	void addStatus(const std::string& str) noexcept(false);
	void addStatus(Status* status) noexcept(false);
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