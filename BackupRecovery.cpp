#include "BackupRecovery.h"
using namespace std;
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