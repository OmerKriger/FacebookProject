#ifndef __BACKUP_RECOVERY_H
#define __BACKUP_RECOVERY_H
#include <fstream>
#include <string>
#include "Exceptions.h"
#include "Page.h"
#include "Member.h"
#include "ImageStatus.h"
#include "VideoStatus.h"

class Facebook;
enum class Owner{ MEMBER, PAGE };
enum class Path { MEMBER, PAGE, CONNECTION, STATUS };

class BackupRecovery
{
	static std::string pathMembers;
	static std::string pathFanPages;
	static std::string pathConnections;
	static std::string pathStatus;
	static const int TYPE_LEN = 3;
	static bool loaded;
	Facebook& facebook;
	std::string errors;
	std::ifstream* inFileMember;
	std::ifstream* inFilePage;
	std::ifstream* inFileStatus;
	std::ifstream* inFileConnection;
public:
	BackupRecovery(BackupRecovery&) = delete;
	BackupRecovery(Facebook& facebook)	noexcept(false);
	~BackupRecovery();
	// Start program recovery functions
	void loadMembers()					noexcept(false);
	void loadFanPages()					noexcept(false);
	void loadConnections()				noexcept(false); 
	void loadStatuses()					noexcept(false); 
	// service functions - things no const because there are flags to change
	static void saveStatus(std::ofstream& outFile, Status* status, int OwnerClassType)					noexcept(false);
	static void saveMember(std::ofstream& outFile,const Member& Member)									noexcept(false);
	static void saveFanPage(std::ofstream& outFile,const Page& FanPage)									noexcept(false);
	static void saveConnection(std::ofstream& outFile, const Member& Member1, const Member& Member2)	noexcept(false);
	static void saveConnection(std::ofstream& outFilem,const Member& Member,const Page& Page)			noexcept(false);
	static void saveString(std::ofstream& outFile, const std::string& str)								noexcept(false);
	static void loadString(std::ifstream& inFile, std::string& str)										noexcept(false);
	const char* getErrorList()																			const;
	static const char* getPath(int pathID);
	static bool isEmptyFile(std::fstream& file);
private:
	static void deleteFilesContent();
	friend class Facebook;
};

#endif // !__BACKUP_RECOVERY_H

