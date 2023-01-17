#include "BackupRecovery.h"
using namespace std;

BackupRecovery::BackupRecovery(Facebook& facebook) : facebook(facebook) // TODO:: run once in project
{
	inFileMember = new ifstream(strPath[Path::MEMBER], ios::binary);
	inFilePage = new ifstream(strPath[Path::PAGE], ios::binary);;
	inFileStatus = new ifstream(strPath[Path::STATUS], ios::binary);;
	inFileConnection = new ifstream(strPath[Path::CONNECTION], ios::binary);
	loadFanPages();
	loadMembers();
	loadConnections();
	loadStatuses();
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

void BackupRecovery::loadMembers() noexcept(false)
{
	bool isEOF = false;
	Member* pMember;
	while (!isEOF)
	{
		pMember = new Member(*inFileMember);
		// TODO: need to check if maybe nullptr could back and where we check EOF for wont be errors
		try
		{
			facebook.addMember(pMember);
		}
		catch (FacebookException& e)
		{
			this->errors += e.what();
		}
		catch (...)
		{
			this->errors += "Unknown error while loading member.";
		}
	}
}

void BackupRecovery::loadFanPages() noexcept(false)
{
	bool isEOF = false;
	Page* pFanPage;
	while (!isEOF)
	{
		pFanPage = new Page(*inFilePage);
		// TODO: need to check if maybe nullptr could back and where we check EOF for wont be errors
		try
		{
			facebook.addPage(pFanPage);
		}
		catch (FacebookException& e)
		{
			this->errors += e.what();
		}
		catch (...)
		{
			this->errors += "Unknown error while loading Page.";
		}
	}
}

void BackupRecovery::loadConnections() noexcept(false) // TODO: finish while loop
{
	bool isEOF = false;
	int typeConnection; // Member-Page Connection
	string name1;
	string name2;
	while (!isEOF)
	{
		inFileConnection->read((char*)typeConnection, sizeof(typeConnection));
		loadString(*inFileConnection, name1);
		loadString(*inFileConnection, name2);
		// TODO: Check if connection is already exist ?? maybe fix in different place
		//  and where we check EOF for wont be errors
		try
		{
			switch (typeConnection)
			{
			case Owner::MEMBER:
				facebook.getMember(name1).addFriend(&facebook.getMember(name2));
			case Owner::PAGE:
				facebook.getMember(name1).addPage(facebook.getPage(name2));
			}
		}
		catch (FacebookException& e)
		{
			this->errors += e.what();
		}
		catch (...)
		{
			this->errors += "Unknown error while loading connections.";
		}
	}
}

void BackupRecovery::loadStatuses() noexcept(false) // TODO: finish while loop
{
	bool isEOF = false;
	while (!isEOF)
	{
		int OwnerClassType;
		inFileStatus->read((char*)OwnerClassType, sizeof(OwnerClassType));
		// read Status
		Status* status = new Status(*inFileStatus); // TODO: Check if work with ImageStatus And VideoStatus
		// push status to his owner
		try
		{
			switch (OwnerClassType)
			{
			case Owner::MEMBER:
				facebook.getMember(status->getCreator()).addStatus(status);
			case Owner::PAGE:
				facebook.getPage(status->getCreator()).addStatus(status);
			}
		}
		catch (FacebookException& e)
		{
			this->errors += e.what();
		}
		catch (StatusException& e)
		{
			this->errors += e.what();
		}
		catch (...)
		{
			this->errors += "Unknown error while loading statuses.";
		}
	}
}

void BackupRecovery::saveStatus(std::ofstream& outFile, Status* status, int OwnerClassType)
{
	if (OwnerClassType != Owner::MEMBER && OwnerClassType != Owner::PAGE)
		throw FacebookException("Status can't be saved because he has no member/page attached.", FacebookException::facebookErrorList::UNDEFINED);

	outFile.write((const char*)OwnerClassType, sizeof(OwnerClassType));
	status->save(outFile);
}

void BackupRecovery::saveMember(std::ofstream& outFile, Member& Member)
{
	Member.save(outFile);
}

void BackupRecovery::saveFanPage(std::ofstream& outFile, Page& FanPage)
{
	FanPage.save(outFile);
}

void BackupRecovery::saveConnection(std::ofstream& outFile, const Member& Member1, const Member& Member2)
{
	int typeConnection = Owner::MEMBER; // Member-Member Connection
	outFile.write((const char*)typeConnection, sizeof(typeConnection));
	saveString(outFile, Member1.getName());
	saveString(outFile, Member2.getName());
}

void BackupRecovery::saveConnection(std::ofstream& outFile, Member& Member, Page& Page)
{
	int typeConnection = Owner::PAGE; // Member-Page Connection
	outFile.write((const char*)typeConnection, sizeof(typeConnection));
	saveString(outFile, Member.getName()); // save member name
	saveString(outFile, Page.getName()); // save page name
}

void BackupRecovery::saveString(std::ofstream& outFile, const std::string& str)
{
	int size = str.size();
	outFile.write((const char*)size, sizeof(size));
	outFile.write(str.c_str(), size);
}
void BackupRecovery::loadString(std::ifstream& inFile, std::string& str)
{
	int size;
	inFile.read((char*)&size, sizeof(size));
	str.resize(size);
	inFile.read(&str[0], size);
}

void BackupRecovery::deleteFilesContent()
{
	ofstream outFileStatus(strPath[Path::STATUS], ios::binary | ios::trunc);
	ofstream outFileConnection(strPath[Path::CONNECTION], ios::binary | ios::trunc);
	ofstream outFileMember(strPath[Path::MEMBER], ios::binary | ios::trunc);
	ofstream outFilePage(strPath[Path::PAGE], ios::binary | ios::trunc);
	outFileStatus.close();
	outFileConnection.close();
	outFileMember.close();
	outFilePage.close();
}
