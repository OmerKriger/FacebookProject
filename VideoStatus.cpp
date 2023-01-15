#include "VideoStatus.h"
using namespace std;


VideoStatus::VideoStatus(std::ifstream& inFile) : Status(inFile)
{
	BackupRecovery::loadString(inFile, this->video);
}

VideoStatus::VideoStatus(const std::string& text, const std::string& name, const std::string& video) : Status(text, name)
{
	this->video = video;
}

void VideoStatus::showStatus() const
{
	Status::showStatus(); // doesnt get the creator string corrcetly for some reason
	showVideo();
}

void VideoStatus::save(std::ofstream& outFile) const
{
	Status::save(outFile);
	BackupRecovery::saveString(outFile, this->video);
}

void VideoStatus::showVideo() const
{
	string path = "start ";
	path += this->video;
	system(path.c_str());
}