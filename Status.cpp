#include "Status.h"
#include "ImageStatus.h"
#include "VideoStatus.h"
using namespace std;


// C'tors
Status::Status(const string& text, const string& name) : creator(name), isSaved(false)
{
	setText(text);
}

Status::Status(ifstream& inFile) : date(inFile), isSaved(false)
{
	BackupRecovery::loadString(inFile, this->text);
	BackupRecovery::loadString(inFile, this->creator);	
}
// save class
void Status::save(std::ofstream& outFile)
{
	if (isSaved)
		return;
	isSaved = true; // flag for no double save
	this->date.save(outFile);
	BackupRecovery::saveString(outFile, this->text);
	BackupRecovery::saveString(outFile, this->creator);

}
// setters
void Status::setText(const string& str) 
{
	if (text.empty() == false)
		throw StatusException("Status cannot be changed once created ");
	if (str.size() <= 1)
		throw StatusException("Status can't be empty ");
	text = str;
}
// Getters
const string Status::getText() const 
{
	return text;
}
const Date& Status::getDate() const
{
	return date;
}
const string& Status::getCreator() const
{
	return creator;
}
// prints
void Status::showStatus() const
{
	/// <summary>
	/// The function show individual status and print the time and date created
	/// and the text of this status
	/// </summary>
	size_t len = this->text.size();
	cout << "--------- " << this->getCreator() << "'s Status ------------------" << endl; // header
	cout << "| Date: " << date.getDay() << "." << date.getMonth() << "." << date.getYear() << endl; // print the date and time
	cout << "| Time: " << date.getHours() << ":";
	int min = date.getMin();
	if (min < 10)
		cout << "0";
	cout << "" << min << endl;
	cout << "| Text: "; // here starting print the text of status
	for (int i = 0; i < len; i++) // for loop run on the text and when print \n after it print "| " for the design
		if (text[i] == '\n')
			cout << text[i] << "| ";
		else
			cout << text[i];
	cout << endl << "--------------------------------------------------" << endl << endl; // bottom of status
}
// Operators
bool Status::operator==(const Status& status) const
{
	if (typeid(*this) != typeid(status) || this->getText() != status.getText())
		return false;
	if (typeid(*this) == typeid(ImageStatus))
		if (((ImageStatus*)this)->getPath() != ((ImageStatus*)(&status))->getPath())
			return false;
	if (typeid(*this) == typeid(VideoStatus))
		if (((VideoStatus*)this)->getPath() != ((VideoStatus*)(&status))->getPath())
			return false;
	return true;
}
bool Status::operator!=(const Status& status) const
{
	return !(*this == status);
}