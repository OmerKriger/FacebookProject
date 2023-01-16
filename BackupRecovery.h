#ifndef __BACKUP_RECOVERY_H
#define __BACKUP_RECOVERY_H

#include "Facebook.h"
#include <fstream>
#include <string>

class ImageStatus;
class VideoStatus;
enum Owner { MEMBER, PAGE };
enum Path { MEMBER, PAGE, CONNECTION, STATUS };
const char* strPath[] = { "Member.bin", "FanPage.bin", "Connection.bin", "Status.bin" };

class BackupRecovery
{
	Facebook& facebook;
	std::string errors;
	std::ifstream* inFileMember;
	std::ifstream* inFilePage;
	std::ifstream* inFileStatus;
	std::ifstream* inFileConnection;
	BackupRecovery(const BackupRecovery&);
public:
	BackupRecovery(Facebook& facebook);
	~BackupRecovery();
	// Start program recovery functions
	void loadMembers()		noexcept(false); // TODO: check if maybe will be better todo template
	void loadFanPages()		noexcept(false); // ...
	void loadConnections()	noexcept(false); // ...
	void loadStatuses()		noexcept(false); // TODO: check if maybe will be better todo template
	// service functions - things no const because there are flags to change
	static void saveStatus(std::ofstream& outFile, Status* status, int OwnerClassType) noexcept(false);
	static void saveMember(std::ofstream& outFile, Member& Member) noexcept(false);
	static void saveFanPage(std::ofstream& outFile, Page& FanPage) noexcept(false);
	static void saveConnection(std::ofstream& outFile, const Member& Member1, const Member& Member2) noexcept(false);
	static void saveConnection(std::ofstream& outFilem, Member& Member, Page& Page) noexcept(false);
	static void saveString(std::ofstream& outFile, const std::string& str) noexcept(false);
	static void loadString(std::ifstream& inFile, std::string& str) noexcept(false);
private:
	static void deleteFilesContent();
	friend class Facebook;
};


#endif // __BACKUP_RECOVERY_H
