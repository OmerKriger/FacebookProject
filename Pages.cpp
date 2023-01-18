#include <iostream>
#include "BackupRecovery.h"
#include "Page.h"
#include "Status.h"
using namespace std;
#define MATCH 0
#define NOT_FOUND -1

// C'tors

Page::Page(const string& name)
{
	setName(name);
}

Page::Page(std::ifstream& inFile) noexcept(false)
{
	BackupRecovery::loadString(inFile, this->name);
}

Page::~Page()
{
	// Open Files
	ofstream outFileStatus(BackupRecovery::getPath((int)Path::STATUS), ios::binary | ios::app);
	ofstream outFilePages(BackupRecovery::getPath((int)Path::PAGE), ios::binary | ios::app);
	// Setup iterators for save and delete status
	list<Status*>::iterator itr = wall.begin();
	list<Status*>::iterator itrEnd = wall.end();
	for (; itr != itrEnd; ++itr)
	{
		BackupRecovery::saveStatus(outFileStatus, *itr, (int)Owner::PAGE);
		delete (*itr);
	}
	// Save the fan page
	BackupRecovery::saveFanPage(outFilePages, *this); 
	// Close files
	outFileStatus.close();
	outFilePages.close();
}

void Page::save(ofstream& outFile) const
{
	if (isSaved)
		return;
	isSaved = true; // flag for no double save
	BackupRecovery::saveString(outFile, this->name);
}


// Add / Remove

void Page::addFan(Member* member)
{
	if (member == nullptr)
		throw PageException("This member doesn't exist ", PageException::pageErrorList::NOT_FOLLOW);
	list<Member*>::iterator itrOfFan = find(fans.begin(), fans.end(), member);
	if (itrOfFan != fans.end())
		throw PageException("This member already follows the page. ", PageException::pageErrorList::ALREADY_FOLLOWED);
	fans.push_back(member);
}

void Page::removeFan(Member* member)
{
	list<Member*>::iterator itrOfFan = find(fans.begin(), fans.end(), member);
	if (itrOfFan == fans.end())
		throw PageException("The member is not a fan so we can't remove him. ", PageException::pageErrorList::NOT_FOLLOW);
	fans.erase(itrOfFan);
}

void Page::addStatus(const string& text, int sType, string& path)
{
	Status* status;
	switch (sType)
	{
	case Status::statusType::TEXT:
		status = new Status(text, this->getName());
		wall .push_front(status);
		break;
	case Status::statusType::IMAGE:
		status = new ImageStatus(text, this->getName(), path);
		wall.push_front(status);
		break;
	case Status::statusType::VIDEO:
		status = new VideoStatus(text, this->getName(), path);
		wall.push_front(status);
		break;
	}
}

void Page::addStatus(Status* status) noexcept(false)
{
	wall.push_back(status);
}

// Prints

void Page::showFans() const
{
	list<Member*>::const_iterator itr = fans.begin();
	list<Member*>::const_iterator itrEnd = fans.end();
	cout << "The Fan List of Page " << name << ":" << endl;
	for (int i=0; itr!=itrEnd; ++itr, ++i)
		cout << "Fan #" << i + 1 << ": " << (*itr)->getName() << endl;
	cout << "---- End of Fan List ----" << endl << endl;
}

void Page::showPageStatus() const
{
	if (wall.size() == 0)
	{
		cout << "System: " << this->getName() << " has no Status." << endl << endl;
		return;
	}
	list<Status*>::const_iterator itr = wall.begin();
	list<Status*>::const_iterator itrEnd = wall.end();
	cout << "-------- All Status of Page " << this->getName() << " --------" << endl; // announcement for start print status
	for(int i=0; itr!= itrEnd; ++itr, ++i)
	{ 
		// print all status
		Date date = (*itr)->getDate();
		cout << "Status " << i + 1 << "# : " << (*itr)->getText() << " || ";
		cout << date.getDay() << "." << date.getMonth() << "." << date.getYear() << " ";
		if (date.getHours() < 10)
			cout << "0";
		cout << "" << date.getHours() << ":";
		if (date.getMin() < 10)
			cout << "0";
		cout << "" << date.getMin() << endl;
		if (typeid(*(*itr)) == typeid(ImageStatus))
			((ImageStatus*)(*itr))->showImage();
		if (typeid(*(*itr)) == typeid(VideoStatus))
			((VideoStatus*)(*itr))->showVideo();
	}
	cout << "----------- End of Status List of " << this->getName() << " -----------" << endl << endl; // announcement for end print status
}

// Setters / Getters

void Page::setName(const string& str)
{
	if (name.empty() == false)
		throw PageException("Name can't be changed after has been setted ! ", PageException::pageErrorList::NAME_SETTED);
	if (str.size() <= 1)
		throw PageException("Name is too short ! ", PageException::pageErrorList::ILLEGAL_NAME);
	name = str;
}

const string& Page::getName() const
{
	return name;
}

int Page::getSizeOfFans() const
{
	return fans.size();
}

// Operators

bool Page::operator<(const Page& other) const
{
	return this->fans.size() < other.fans.size();
}

bool Page::operator>(const Page& other) const
{
	return this->fans.size() > other.fans.size();

}

bool Page::operator<(const Member& other) const
{
	return other < (*this); // based on operator< from member
}

bool Page::operator>(const Member& other) const
{
	return other < (*this); // based on operator> from member
}



