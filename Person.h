#ifndef __PERSON_H
#define __PERSON_H

/*
Notes: 
Everything in note is need to set/finish 
things only for first setup right now
TODO:
0. forward declartion and complete signatures of method inside || (Done) || for Nir double check it that everything is really done
1. add setters/getters
2. writing methods functions
3. Constructors
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
	void showMyStatus();
	bool addStatus(); // i think we should send from inside this function to outter function that will deal with types and in this function we will handle only with the types and change calls
	const char* getName();
private:
	char* name;
	int birthDay; // maybe we will change use for time_t type later
	Status** myStatus;// =nullptr to set in c'tor
	Status** FriendsStatus;// = nullptr to set in c'tor
	unsigned char F_S_newestStatusIndex; // set to zero (this index will show us where is the newest status without overwrite the order of array
	Page** InterestPages; //= nullptr to set in c'tor
	Person** friends; // arr of pointers to persons friends, set to nullptr
	unsigned int logSizeFriends; // set to zero
	unsigned int logSizeMyStatus; // set to zero
	unsigned int logSizeFriendsStatus; // set to zero
	unsigned int logSizeInterestPages; // set to zero
	unsigned int phySizeFriends; // set to zero
	unsigned int phySizeMyStatus; // set to zero
	unsigned int phySizeFriendsStatus; // set to zero
	unsigned int phySizeInterestPages; // set to zero
	bool postStatus();
	bool addSpaceFriendList();
	bool addSpaceFriendsStatusList();
	bool addSpaceMyStatusList();
	bool addSpaceInterestPagesList();

	bool setName(char* str);
	bool setBirthDay(int day, int month, int year);
};



#endif