#include "ImageStatus.h"
#include "BackupRecovery.h"

using namespace std;

ImageStatus::ImageStatus(ifstream& inFile) : Status(inFile)
{
	BackupRecovery::loadString(inFile, this->image);
}

ImageStatus::ImageStatus(const string& text, const string& name, const string& image) : Status(text, name)
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

void ImageStatus::save(std::ofstream& outFile) const
{
	if (isSaved)
		return;
	Status::save(outFile);
	BackupRecovery::saveString(outFile, this->image);
}
