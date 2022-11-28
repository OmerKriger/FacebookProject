#ifndef __STATUS_H
#define __STATUS_H
#pragma warning(disable : 4996)
#include "Date.h"
#include "supportFunctions.h"


enum class sType { tText, tPhoto, tVideo };
class Status
{
	Date date; 
	char* text;
	sType statusType; // default value will be text for text status
	bool setDate();
	bool setText(const char* str, sType type);
	Status(Status&);
public:
	Status() = delete;
	Status(const char* text, sType statusType);
	~Status();
	const Date& getDate() const;
	const char* getText() const;
	void showStatus();
};



#endif