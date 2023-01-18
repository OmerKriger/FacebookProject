#include <iostream>
using namespace std;
#include "BackupRecovery.h"
#include "Utilities.h"
// C'tors in Members
Member::Member(const string& name, const Date& bDay)
{
	this->isSavedMember = this->isSavedInterestPages = this->isSavedFriends = false;
	this->setName(name);
	this->birthDay = bDay;
}

Member::Member(std::ifstream& inFile) : birthDay(inFile)
{
	this->isSavedMember = this->isSavedInterestPages = this->isSavedFriends = false;
	BackupRecovery::loadString(inFile, this->name);
}
Member::~Member()
{
	// Open files for saving before delete
	ofstream outFileStatus(BackupRecovery::getPath((int)Path::STATUS), ios::binary | ios::app);
	ofstream outFileMember(BackupRecovery::getPath((int)Path::MEMBER), ios::binary | ios::app);
	// Setup iterators for save and delete status
	list<Status*>::iterator itr = this->myStatus.begin();
	list<Status*>::iterator itrEnd = this->myStatus.end();
	for (; itr != itrEnd; ++itr)
	{
		BackupRecovery::saveStatus(outFileStatus, *itr, (int)Owner::MEMBER); // save status in storage for next run
		delete (*itr);
	}
	// Save Member
	BackupRecovery::saveMember(outFileMember, *this);
	// Close Files
	outFileStatus.close();
	outFileMember.close();
}

void Member::save(std::ofstream& outFile) const
{
	if (isSavedMember)
		return;
	isSavedMember = true; // flag for no double save
	this->birthDay.save(outFile);
	BackupRecovery::saveString(outFile, this->name);
}

void Member::saveFriends(std::ofstream& outFile) const
{
	if (isSavedFriends)
		return;
	isSavedFriends = true;
	list<Member*>::const_iterator pItr = friends.begin();
	list<Member*>::const_iterator pItrEnd = friends.end();
	for (; pItr != pItrEnd; ++pItr)
		BackupRecovery::saveConnection(outFile, *this, *(*pItr));
}

void Member::saveInterestPages(std::ofstream& outFile) const
{
	if (isSavedInterestPages)
		return;
	isSavedInterestPages = true;
	list<Page*>::const_iterator pItr = InterestPages.begin();
	list<Page*>::const_iterator pItrEnd = InterestPages.end();
	for (; pItr != pItrEnd; ++pItr)
		BackupRecovery::saveConnection(outFile, *this, *(*pItr));
}

// Friends functions in Member
void Member::addFriend(Member* newFriend)
{
	if (newFriend == this) // friend cannot add him self
		throw MemberException("Friend cannot create friendships with himself. ", MemberException::memberErrorList::FRIEND_HIMSELF);
	list<Member*>::iterator itrOfFriend = find(friends.begin(), friends.end(), newFriend); // search for newFriend in friends
	if (itrOfFriend != friends.end()) // if friend is found return false
		throw MemberException("This Members are already friends. ", MemberException::memberErrorList::ALREADY_FRIENDS);
	friends.push_back(newFriend);
	try
	{
		newFriend->addFriend(this);
	}
	catch (MemberException& e)
	{
		if (e.getErrorCode() != MemberException::memberErrorList::ALREADY_FRIENDS)
			throw e;
	}
}
void Member::removeFriend(Member* dFriend)
{
	list<Member*>::iterator itrOfFriend = find(friends.begin(),friends.end(), dFriend);
	if (itrOfFriend == friends.end()) // we can't remove friend who is not in friends
		throw MemberException("This two Members aren't friends",MemberException::memberErrorList::NOT_FRIENDS);
	friends.erase(itrOfFriend);
	try
	{
		dFriend->removeFriend(this);
	}
	catch (MemberException& e)
	{
		if (e.getErrorCode() != MemberException::memberErrorList::NOT_FRIENDS)
			throw e;
	}
}

// Pages functions in Member
void Member::addPage(Page& newPage)
{
	list<Page*>::iterator itrOfPage = find(InterestPages.begin(), InterestPages.end(), &newPage); // search for newFriend in friends
	if (itrOfPage != InterestPages.end()) // if friend is found return false
		throw MemberException("This Member already follows this Page !", MemberException::memberErrorList::ALREADY_FOLLOW);
	InterestPages.push_back(&newPage);
	// say to page add this friend to his list
	newPage.addFan(this);
}
void Member::removePage(const Page& dPage)
{
	list<Page*>::iterator itrPage = find(InterestPages.begin(), InterestPages.end(), &dPage);
	if (itrPage == InterestPages.end()) // we can't remove page who is not in followed
		throw MemberException("This member does'nt follow this page !", MemberException::memberErrorList::NOT_FOLLOW);

	(*itrPage)->removeFan(this);
	InterestPages.erase(itrPage);
}
void Member::showMyInterestPages() const
{
	if (InterestPages.size() == 0)
	{
		cout << "System: " << this->getName() << " has no page followed." << endl << endl;
		return;
	}
	cout << "-------- All Followed Pages by " << this->getName() << " --------" << endl;
	list<Page*>::const_iterator itr = this->InterestPages.begin();
	list<Page*>::const_iterator itrEnd = this->InterestPages.end();
	for(int i = 0;itr!=itrEnd;++itr, ++i)
		cout << "Fan Page #" << i << " Name: " << (*itr)->getName() << endl;
	cout << "----------- End of Followed Pages List -----------" << endl << endl;
}

// Status Functions in Members

void Member::showMyStatus() const
{
	if (myStatus.size() == 0)
	{
		cout << "System: " << this->getName() << " has no Status." << endl << endl;
		return;
	}
	cout << "-------- All Status of " << this->getName() << " --------" << endl;
	list<Status*>::const_iterator itr = this->myStatus.begin();
	list<Status*>::const_iterator itrEnd = this->myStatus.end();
	for (int i = 0; itr != itrEnd; ++itr, ++i)
	{
		const Date& date = (*itr)->getDate();
		cout << "Status " << i + 1 << "# : " << (*itr)->getText() << " || ";
		cout << date.getDay() << "." << date.getMonth() << "." << date.getYear() << " ";
		if (date.getHours() < 10)
			cout << "0";
		cout << date.getHours() << ":";
		if (date.getMin() < 10)
			cout << "0";
		cout << "" << date.getMin() << endl;
		if (typeid(*(*itr)) == typeid(ImageStatus))
			((ImageStatus*)(*itr))->showImage();
		if (typeid(*(*itr)) == typeid(VideoStatus))
			((VideoStatus*)(*itr))->showVideo();
	}
	cout << "----------- End of Status List of "<< this->getName() << " -----------" << endl << endl;

} 
void Member::addStatus(Status* status) 
{
	// overloading for add status from storage
	myStatus.push_front(status);
}
void Member::addStatus(const string& text, int sType, string& path)
{
	Status* status;
	switch (sType)
	{
	case Status::statusType::TEXT:
		status = new Status(text, this->getName());
		myStatus.push_front(status);
		break;
	case Status::statusType::IMAGE:
		status = new ImageStatus(text, this->getName(), path);
		myStatus.push_front(status);
		break;
	case Status::statusType::VIDEO:
		status = new VideoStatus(text, this->getName(), path);
		myStatus.push_front(status);
		break;
	}
}
void Member::showLastFriendsStatus() const
{
	bool somethingPrinted = false;
	if (friends.size() == 0)
	{
		cout << "System: This Member has no friends." << endl << endl;
		return;
	}
	else
	{
		list<Member*>::const_iterator itr = this->friends.begin();
		list<Member*>::const_iterator itrEnd = this->friends.end();
		for (int i = 0; itr != itrEnd; ++itr, ++i)
		{
			if ((*itr)->getAmountOfStatus() > 0 && somethingPrinted == false) // change flag for status printed
				somethingPrinted = true;
			(*itr)->showMyLastStatuses(); // print statuses of friends
		}
	}
	if (somethingPrinted == false) // if no status printed
		cout << "System: This Member's friends has no statuses." << endl << endl;
}
void Member::showMyLastStatuses() const 
{
	/// <summary>
	/// This function member show his statuses from the list of statuses
	/// </summary>
	list<Status*>::const_iterator itr = myStatus.begin();
	list<Status*>::const_iterator itrEnd = myStatus.end();
	for (int i = 0; itr != itrEnd && i <= AMOUNT_SHOW_FRIENDS_STATUSES; ++itr, ++i)
		(*itr)->showStatus();
}

// setters/getters/voids
void Member::setName(const string& str)
{
	if (name.empty() == false)
		throw MemberException("Name can't be changed after has been setted ! ", MemberException::memberErrorList::NAME_SETTED);
	if (str.size() <= 1)
		throw MemberException("Name is too short ! ", MemberException::memberErrorList::ILLEGAL_NAME);
	name = str;
}
void Member::showMyFriends() const
{
	if (friends.size() == 0)
	{
		cout << "System: " << this->getName() << " has no friends." << endl << endl;
		return;
	}
	cout << "-------- All Friends of " << this->getName() << " --------" << endl;
	list<Member*>::const_iterator itr = this->friends.begin();
	list<Member*>::const_iterator itrEnd = this->friends.end();
	for (int i = 0; itr != itrEnd; ++itr, ++i)
		cout << "Friend #" << i + 1 << " Name: " << (*itr)->getName() << endl;
	cout << "----------- End of Friends List -----------" << endl << endl;
}

// Operators
bool Member::operator<(const Member& other) const
{
	return this->friends.size() < other.friends.size();
}
bool Member::operator>(const Member& other) const
{
	return this->friends.size() > other.friends.size();
}
bool Member::operator<(const Page& other) const
{
	return this->friends.size() < other.getSizeOfFans();
}
bool Member::operator>(const Page& other) const
{
	return this->friends.size() > other.getSizeOfFans();
}

Member& Member::operator+=(Member& other)
{
	this->addFriend(&other);
	return *this;
}

Member& Member::operator+=(Page& page)
{
	this->addPage(page);
	return *this;
}

