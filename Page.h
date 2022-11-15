#ifndef __PAGES_H
#define __PAGES_H

/*
Notes:
Everything in note is need to set/finish
things only for first setup right now
TODO List:
0. forward declartion and complete signatures of method inside () || (Done) || for Nir double check it that everything is really done
1. add setters/getters
2. writing methods functions
3. Constructors
*/

class Person;
class Status;

class Page
{
public:
	/*
	Constructors
	*/
	bool addFan(Person* Friend);
	bool searchFriend(char* fName);
	bool removeFan(char* fName);
	bool showFans();
	bool addStatus();
	const char* getName();

private:
	char* name;
	Person** Fans;
	unsigned int logSizeFans;
	unsigned int phySizeFans;
	Status** wall;
	unsigned int logSizeWall;
	unsigned int phySizeWall;
	bool setName(char* str); // will be use inside constructors  (why private) 
};



#endif