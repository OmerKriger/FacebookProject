#ifndef __STATUS_H
#define __STATUS_H
#pragma warning(disable : 4996)
#include "Date.h"
#include "Exceptions.h"
#include <string>

class Status
{
	Status(Status&);
protected:
	Date date; 
	std::string text;
	const std::string& creator;
	void setText(const std::string& str) noexcept(false);
public:
	Status(const std::string& text, const std::string& name) noexcept(false);
	virtual ~Status() {};
	const Date& getDate() const;
	const std::string getText() const;
	virtual void showStatus() const;
	const std::string& getCreator() const;
	// Operators
	bool operator==(const Status& status) const;
	bool operator!=(const Status& status) const;
};
#endif