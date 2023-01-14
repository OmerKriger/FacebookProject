#include "VideoStatus.h"
using namespace std;


VideoStatus::VideoStatus(const std::string& text, const std::string& name, const std::string& video) : Status(text, name)
{
	this->video = video;
}

void VideoStatus::showStatus() const
{
	Status::showStatus(); // doesnt get the creator string corrcetly for some reason
	showVideo();
}

void VideoStatus::showVideo() const
{
	string path = "start ";
	path += this->video;
	system(path.c_str());
}