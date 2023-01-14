#include "ImageStatus.h"
using namespace std;

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