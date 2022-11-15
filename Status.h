#ifndef __STATUS_H
#define __STATUS_H

#include <iostream>
using namespace std;

/*
Notes:
Everything in note is need to set/finish
things only for first setup right now
TODO List:
0. forward declartion and complete signatures of method inside () || (Done) - for Nir double check it done
1. add setters/getters
2. writing methods functions
3. Constructors
4. complete StatusType (maybe in Task2)
*/

class Status
{
public:
	enum sType { text,photo,video };
	/*
	Constructors
	*/
	bool setTime(time_t time);
	time_t getTime();
	bool setText(char* str, sType statusType = text);
	const char* getText();
private:
	time_t timestamp;
	char* Text;
	unsigned char statusType; // default value will be text for text status
};



#endif