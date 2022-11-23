#ifndef __STATUS_H
#define __STATUS_H

#include <iostream>
using namespace std;
#include "Date.h"

enum class sType { tText, tPhoto, tVideo };
class Status
{
	time_t time;
	Date date;
	char* text;
	sType statusType; // default value will be text for text status
	bool setTime(); // set the currect time
	bool setText(const char* str, sType type);
	Status(Status&);
public:
	Status() = delete;
	~Status();
	Status(const char* text, sType statusType);
	const time_t& getTime() const;
	const Date& getDate() const;
	const char* getText() const;
};



#endif