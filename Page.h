#ifndef __PAGES_H
#define __PAGES_H

/*
Notes:
Everything in note is need to set/finish
things only for first setup right now
TODO List:
0. forward declartion and complete signatures of method inside ()
1. Constructors
2. add setters/getters
3. writing methods functions
*/

class Page
{
public:
	/*
	Constructors
	*/
	bool addFan;
	bool removeFan;
	bool showFans;
	bool addStatus;

private:
	char* name;
	// Person** Fans;
	// Status** wall;
};



#endif