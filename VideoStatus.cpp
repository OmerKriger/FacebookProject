#include <iostream>
using namespace std;
#include "VideoStatus.h"

VideoStatus::VideoStatus(std::string text, std::string name, std::string video) : Status(text, name)
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