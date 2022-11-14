#ifndef __STATUS_H
#define __STATUS_H
#include <iostream>
using namespace std;

/*
Notes:
Everything in note is need to set/finish
things only for first setup right now
TODO List:
0. forward declartion and complete signatures of method inside ()
1. Constructors
2. add setters/getters
3. writing methods functions
4. complete StatusType (maybe in Task2)
*/

class Status
{
public:
	/*
	Constructors
	*/
	// enum StatusType - need to be complete
	bool setTime(time_t time);
	time_t getTime();
	bool setText(char* str);
	const char* getText();
private:
	time_t timestamp;
	char* Text;
};



#endif