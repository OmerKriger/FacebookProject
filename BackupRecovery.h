#ifndef __BACKUP_RECOVERY_H
#define __BACKUP_RECOVERY_H

#include "Facebook.h"
#include <fstream>
#include <string>

class BackupRecovery
{
public:
	static void saveString(std::ofstream& outFile, const std::string& str);
	static void loadString(std::ifstream& inFile, std::string& str);
};


#endif // __BACKUP_RECOVERY_H
