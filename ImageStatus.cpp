#include <iostream>
using namespace std;
#include "ImageStatus.h"

ImageStatus::ImageStatus(string text, string name, string image) : Status(text, name)
{
	this->image = image;
}

void ImageStatus::showStatus() const
{
	Status::showStatus(); // doesnt get the creator string corrcetly for some reason
	showImage();
}

void ImageStatus::showImage() const
{
	string path = "start ";
	path += this->image;
	system(path.c_str());
}