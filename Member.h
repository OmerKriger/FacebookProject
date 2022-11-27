#ifndef __Member_H
#define __Member_H
#define DAY_SHIFT 1000000
#define MONTH_SHIFT 10000
#define YEAR_SHIFT 1
#define MAX_FRIEND_LATEST_STATUS 10

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
class Date;

class Member
{ 
public:
	Member() = delete;
	Member(const char* name, Date bDay);
	//~Member(); need to add that.

	bool addFriend(Member* newFriend); // we can update the to objects with a pointer to the friend
	bool removeFriend(Member* dFriend);
	bool addPage(Page* newPage);
	void showMyStatus();
	bool addStatus(const char* text, sType type); // i think we should send from inside this function to outter function that will deal with types and in this function we will handle only with the types and change calls
	const char* getName() const;
private:
	char* name;
	Date birthDay; // changed it to DATE type
	Status** myStatus;// =nullptr to set in c'tor
	Status* FriendsStatus[MAX_FRIEND_LATEST_STATUS] = { nullptr };; // temp 
	unsigned char F_S_newestStatusIndex; // set to zero (this index will show us where is the newest status without overwrite the order of array
	Page** InterestPages; //= nullptr to set in c'tor
	Member** friends; // arr of pointers to Members friends, set to nullptr
	unsigned int logSizeFriends , logSizeMyStatus, logSizeFriendsStatus, logSizeInterestPages; // set to zero
	unsigned int phySizeFriends , phySizeMyStatus, phySizeInterestPages; // set to zero
	bool postStatus();
	bool addSpaceFriendList();
	bool addSpaceMyStatusList();
	bool addSpaceInterestPagesList();
	int searchFriend(char* fName);
	int searchPage(const char* pName);
	bool setName(const char* str);
};



#endif