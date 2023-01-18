#include "BackupRecovery.h"
#include "Facebook.h"
using namespace std;

// set Files Paths
string BackupRecovery::pathMembers = "Member.bin";
string BackupRecovery::pathFanPages = "FanPage.bin";
string BackupRecovery::pathConnections = "Connection.bin";
string BackupRecovery::pathStatus = "Status.bin";
bool BackupRecovery::loaded = false; // flag for one load per program

BackupRecovery::BackupRecovery(Facebook& facebook) : facebook(facebook)
{
	if (loaded == true) // check loaded once
		throw BackupRecoveryException("You can load program only once for each run.\n");
	// allocate files obj for loading program
	inFileMember = new ifstream(getPath((int)Path::MEMBER), ios::binary);
	inFilePage = new ifstream(getPath((int)Path::PAGE), ios::binary);;
	inFileStatus = new ifstream(getPath((int)Path::STATUS), ios::binary);;
	inFileConnection = new ifstream(getPath((int)Path::CONNECTION), ios::binary);
	// check everything is Ok for loading
	if (inFileMember == nullptr || inFilePage == nullptr || inFileStatus == nullptr || inFileConnection == nullptr)
		throw BackupRecoveryException("One of the files isn't opened correct (allocation failed).\n");
	if (!inFileMember->is_open() || !inFilePage->is_open() || !inFileStatus->is_open() || !inFileConnection->is_open())
		throw BackupRecoveryException("One of the files isn't opened.\n");

	// Start loading
	loadFanPages();
	loadMembers();
	loadStatuses();
	loadConnections();
	// change flag for no loading again
	loaded = true;
}

BackupRecovery::~BackupRecovery()
{
	// Close files
	inFileMember->close();
	inFilePage->close();
	inFileStatus->close();
	inFileConnection->close();
	// delete allocations of files obj
	delete inFileMember;
	delete inFilePage;
	delete inFileStatus;
	delete inFileConnection;
}


void BackupRecovery::loadMembers()
{
	if (BackupRecovery::isEmptyFile(*(fstream*)inFileMember))
		return;
	bool isEOF = false;
	Member* pMember = nullptr;
	while (!inFileMember->eof())
	{
		try
		{
			pMember = new Member(*inFileMember);
		}
		catch (BackupRecoveryException& e)
		{
			if (e.getErrorCode() == BackupRecoveryException::backupRecoveryErrorList::END_OF_FILE)
				break;
			if (e.getErrorCode() == BackupRecoveryException::backupRecoveryErrorList::FILE_BAD)
				break;
			if (e.getErrorCode() == BackupRecoveryException::backupRecoveryErrorList::FILE_CLOSED)
				break;
			else
			{
				this->errors += e.what();
				this->errors += "\n"; // new line to error list
			}
		}
		if (pMember == nullptr)
			continue;
		try
		{
			facebook.addMember(pMember);
		}
		catch (SystemException& e)
		{
			this->errors += e.what();
			this->errors += "\n"; // new line to error list
		}
		catch (...)
		{
			this->errors += "Unknown error while loading member.\n";
		}
	}
}

void BackupRecovery::loadFanPages()
{
	if (isEmptyFile(*(fstream*)inFilePage))
		return;
	Page* pFanPage = nullptr;
	while (!inFileStatus->eof())
	{
		try 
		{
			pFanPage = new Page(*inFilePage);
		}
		catch (BackupRecoveryException& e)
		{
			if (e.getErrorCode() == BackupRecoveryException::backupRecoveryErrorList::END_OF_FILE)
				break;
			if (e.getErrorCode() == BackupRecoveryException::backupRecoveryErrorList::FILE_BAD)
				break;
			if (e.getErrorCode() == BackupRecoveryException::backupRecoveryErrorList::FILE_CLOSED)
				break;
			else
			{
				this->errors += e.what();
				this->errors += "\n"; // new line to error list
			}
		}
		if (pFanPage == nullptr)
			continue;
		try
		{
			facebook.addPage(pFanPage);
		}
		catch (SystemException& e)
		{
			this->errors += e.what();
			this->errors += "\n"; // new line to error list
		}
		catch (...)
		{
			this->errors += "Unknown error while loading Page.";
		}
	}
}

void BackupRecovery::loadConnections()
{
	if (isEmptyFile(*(fstream*)inFileConnection))
		return;
	bool isEOF = false;
	int typeConnection; // Member-Page Connection
	string name1;
	string name2;
	while (!isEOF)
	{
		inFileConnection->read((char*)&typeConnection, sizeof(typeConnection));
		if (inFileConnection->eof())
		{
			isEOF = true;
			break;
		}
		loadString(*inFileConnection, name1);
		loadString(*inFileConnection, name2);
		try
		{
			switch (typeConnection)
			{
			case (int)Owner::MEMBER:
				facebook.getMember(name1).addFriend(&facebook.getMember(name2)); break;
			case (int)Owner::PAGE:
				facebook.getMember(name1).addPage(facebook.getPage(name2)); break;
			}
		}
		catch (MemberException& e)
		{
			if (e.getErrorCode() == MemberException::ALREADY_FRIENDS) // if they already friend is ok not need write it down
				continue;
			else
			{
				this->errors += e.what();
				this->errors += "\n"; // new line to error list
			}
		}
		catch (SystemException& e)
		{
			this->errors += e.what();
			this->errors += "\n"; // new line to error list
		}
		catch (...)
		{
			this->errors += "Unknown error while loading connections.\n";
		}
	}
}

void BackupRecovery::loadStatuses()
{
	if (isEmptyFile(*(fstream*)inFileStatus))
		return;
	bool isEOF = false;
	int OwnerClassType;
	char statusType[Status::TYPE_LEN + 1];
	while (!isEOF)
	{
		// read Type data of status
		inFileStatus->read((char*)&OwnerClassType, sizeof(OwnerClassType));
		if (!inFileStatus->good())
		{
			isEOF = true;
			break;
		}
		inFileStatus->read((char*)&statusType, TYPE_LEN);
		try
		{
			Status* status = nullptr;
			// Read Status and create.
			if (strncmp(statusType, typeid(Status).name() + 6, Status::TYPE_LEN) == 0)
				status = new Status(*inFileStatus);
			else if (strncmp(statusType, typeid(ImageStatus).name() + 6, Status::TYPE_LEN) == 0)
				status = new ImageStatus(*inFileStatus);
			else if (strncmp(statusType, typeid(VideoStatus).name() + 6, Status::TYPE_LEN) == 0)
				status = new VideoStatus(*inFileStatus);
			
			if (status == nullptr) // protection from add nullptr
				continue;

			// push status to his owner
			switch (OwnerClassType)
			{
			case (int)Owner::MEMBER:
				facebook.getMember(status->getCreator()).addStatus(status); break;
			case (int)Owner::PAGE:
				facebook.getPage(status->getCreator()).addStatus(status); break;
			default:
				throw SystemException("Unknown type of Status Owner");
			}
		}
		catch (StatusException& e)
		{
			this->errors += e.what();
			this->errors += "\n"; // new line to error list

		}
		catch (SystemException& e)
		{
			this->errors += e.what();
			this->errors += "\n"; // new line to error list
		}
		catch (...)
		{
			this->errors += "Unknown error while loading statuses.\n";
		}
	}
}

void BackupRecovery::saveStatus(ofstream& outFile, Status* status, int OwnerClassType)
{
	if (OwnerClassType != (int)Owner::MEMBER && OwnerClassType != (int)Owner::PAGE)
		throw FacebookException("Status can't be saved because he has no member/page attached.", FacebookException::facebookErrorList::UNDEFINED);
	
	outFile.write((const char*)&OwnerClassType, sizeof(OwnerClassType));
	status->save(outFile);
}

void BackupRecovery::saveMember(ofstream& outFile,const Member& Member)
{
	try 
	{
		Member.save(outFile);
	}
	catch (MemberException& e) // catch only MemberExceptions
	{
		if (e.getErrorCode() != MemberException::memberErrorList::ALREADY_FRIENDS) // if they already friends is ok
			throw e; // throw if is different error
	}
}

void BackupRecovery::saveFanPage(ofstream& outFile,const Page& FanPage)
{
	FanPage.save(outFile);
}

void BackupRecovery::saveConnection(ofstream& outFile, const Member& Member1, const Member& Member2)
{
	int typeConnection = (int)Owner::MEMBER; // Member-Member Connection
	outFile.write((const char*)&typeConnection, sizeof(typeConnection));
	saveString(outFile, Member1.getName());
	saveString(outFile, Member2.getName());
}

void BackupRecovery::saveConnection(ofstream& outFile, const Member& Member, const Page& Page)
{
	int typeConnection = (int)Owner::PAGE; // Member-Page Connection
	outFile.write((const char*)&typeConnection, sizeof(typeConnection));
	saveString(outFile, Member.getName()); // save member name
	saveString(outFile, Page.getName()); // save page name
}

void BackupRecovery::saveString(ofstream& outFile, const string& str)
{
	int size = (int)str.size();
	outFile.write((const char*)&size, sizeof(size)); // throw error
	outFile.write(str.c_str(), size);
}
void BackupRecovery::loadString(ifstream& inFile, string& str)
{
	// check if got bad file
	if (!inFile.is_open())
		throw BackupRecoveryException("File isn't open.", BackupRecoveryException::backupRecoveryErrorList::FILE_CLOSED);
	if (!inFile.good())
		throw BackupRecoveryException("File is not good.", BackupRecoveryException::backupRecoveryErrorList::FILE_BAD);
	// check string
	int size;
	inFile.read((char*)&size, sizeof(size));
	if (inFile.eof()) // check eof
		throw BackupRecoveryException("File ended", BackupRecoveryException::backupRecoveryErrorList::END_OF_FILE);
	str.resize(size);
	inFile.read(&str[0], size);
}

const char* BackupRecovery::getPath(int pathID)
{
	switch (pathID)
	{
	case (int)Path::MEMBER: return BackupRecovery::pathMembers.c_str();
	case (int)Path::PAGE: return BackupRecovery::pathFanPages.c_str();
	case (int)Path::CONNECTION: return BackupRecovery::pathConnections.c_str();
	case (int)Path::STATUS: return BackupRecovery::pathStatus.c_str();
	default:
		return nullptr;
	}

}

bool BackupRecovery::isEmptyFile(fstream& file)
{
	return file.peek() == fstream::traits_type::eof();
}

const char* BackupRecovery::getErrorList() const
{
	return errors.c_str();
}

void BackupRecovery::deleteFilesContent()
{
	ofstream outFileStatus(getPath((int)Path::STATUS), ios::binary | ios::trunc);
	ofstream outFileConnection(getPath((int)Path::CONNECTION), ios::binary | ios::trunc);
	ofstream outFileMember(getPath((int)Path::MEMBER), ios::binary | ios::trunc);
	ofstream outFilePage(getPath((int)Path::PAGE), ios::binary | ios::trunc);
	outFileStatus.close();
	outFileConnection.close();
	outFileMember.close();
	outFilePage.close();
}
