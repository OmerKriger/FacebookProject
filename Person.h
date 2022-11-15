#ifndef __PERSON_H
#define __PERSON_H

/*
Notes: 
Everything in note is need to set/finish 
things only for first setup right now
TODO:
0. forward declartion and complete signatures of method inside ()    (partly completed)
1. Constructors
2. add setters/getters
3. writing methods functions
*/

class Status;
class Page;


class Person
{ 
public:
	/*
	Constructors (destroy copy make)
	*/
	bool addFriend();
	bool removeFriend();
	bool searchFriend();
	bool addPage();
	bool showMyStatus();
	bool addStatus(); // self status
private:
	char* name;
	int birthDay;
	Status** myStatus;// =nullptr to set in c'tor
	Status** FriendLatestStatus;// = nullptr to set in c'tor
	Page** InterestInPages; //= nullptr to set in c'tor
	unsigned int logSizeMyStatus; // set to zero
	unsigned int logSizeFriendsStatus; // set to zero
	unsigned int logSizeInterestInPages; // set to zero
	unsigned int phySizeMyStatus; // set to zero
	unsigned int phySizeFriendsStatus; // set to zero
	unsigned int phySizeInterestInPages; // set to zero
	bool postStatus;
};



#endif