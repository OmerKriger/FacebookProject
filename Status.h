#ifndef __STATUS_H
#define __STATUS_H
#pragma warning(disable : 4996)
#include "Date.h"
#include "supportFunctions.h"
#include <string>

enum class sType { tText, tPhoto, tVideo };
class Status
{
	Date date; 
	std::string text;
	const std::string const creator;
	sType statusType; // default value will be text for text status
	bool setText(const std::string& str, sType type);
	Status(Status&);
public:
	Status(const std::string& text, const std::string& name);
	// ~Status(); // deleted because no allocations
	const Date& getDate() const;
	const std::string getText() const;
	void showStatus();
	const std::string& getCreator() const;
};
#endif