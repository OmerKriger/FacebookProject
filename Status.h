#ifndef __STATUS_H
#define __STATUS_H
#pragma warning(disable : 4996)
#include "Date.h"
#include <string>

class Status
{
	Date date; 
	std::string text;
	const std::string& creator;
	bool setText(const std::string& str);
	Status(Status&);
public:
	Status(const std::string& text, const std::string& name);
	const Date& getDate() const;
	const std::string getText() const;
	void showStatus() const;
	const std::string& getCreator() const;
	// Operators
	bool operator==(const Status& status) const;
	bool operator!=(const Status& status) const;
};
#endif