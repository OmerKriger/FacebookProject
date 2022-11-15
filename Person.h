#ifndef __PERSON_H
#define __PERSON_H

/*
Notes: 
Everything in note is need to set/finish 
things only for first setup right now
TODO:
0. forward declartion and complete signatures of method inside ()    (partly completed, need to figure out addStatus)
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
	bool addFriend(Person* newFriend); // we can update the to objects with a pointer to the friend
	bool removeFriend(Person* dFriend);
	bool searchFriend(char* fName);
	bool addPage(Page* newPage);
	bool showMyStatus(const Status& myStatus); // const by ref so we could not change the status and save space. 
	bool addStatus(); // self status, we need to think about how to hande it with different status types.
private:
	char* name;
	int birthDay;
	Status** myStatus;// =nullptr to set in c'tor
	Status** FriendLatestStatus;// = nullptr to set in c'tor
	Page** InterestInPages; //= nullptr to set in c'tor
	Person** friends; // arr of pointers to persons friends, set to nullptr
	unsigned int logSizeFriends; // set to zero
	unsigned int logSizeMyStatus; // set to zero
	unsigned int logSizeFriendsStatus; // set to zero
	unsigned int logSizeInterestInPages; // set to zero
	unsigned int phySizeFriends; // set to zero
	unsigned int phySizeMyStatus; // set to zero
	unsigned int phySizeFriendsStatus; // set to zero
	unsigned int phySizeInterestInPages; // set to zero
	bool postStatus;
};



#endif