#ifndef __STATUS_H
#define __STATUS_H

#include <iostream>
using namespace std;
#include "Date.h"

/*
Notes:
Everything in note is need to set/finish
things only for first setup right now
TODO List:
1. add setters/getters
2. writing methods functions
3. Constructors
*/
class Status
{
public:
	enum sType { tText, tPhoto, tVideo };
private:
	time_t time;
	Date date;
	char* text; // status text
	sType statusType; // default value will be text for text status
	bool setTime(); // set the currect time
	bool setText(char* str, sType type);
	Status(Status&);
public:
	Status() = delete;
	Status(const char* text, Date date); // ---
	~Status(); // ---
	const time_t& getTime() const;
	const Date& getDate() const; // ---
	const char* getText() const;


};



#endif