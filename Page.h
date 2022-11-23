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

class Member;
class Status;

class Page
{
	char* name;
	Member** fans;
	Status** wall;
	int logSizeFans, phySizeFans;
	int logSizeWall, phySizeWall;
	bool setName(const char* str);
	bool searchFan(char* name);
	Page(const Page&);
public:
	Page() = delete;
	Page(const char* name);
	~Page(); // ---
	bool addFan(Member* Friend);
	bool removeFan(char* name);
	void showFans() const;
	bool addStatus();
	const char* getName() const;



};



#endif