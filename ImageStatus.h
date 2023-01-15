#ifndef __IMAGESTATUS_H
#define __IMAGESTATUS_H
#include <iostream>
#include <fstream>
#include <string>
#include "Status.h"
#include "BackupRecovery.h"

class ImageStatus : public Status
{
	std::string image;
	ImageStatus(ImageStatus&);
public:
	ImageStatus(std::ifstream& inFile);
	ImageStatus(const std::string& text, const std::string& name,const std::string& image) : Status(text,name), image(image) {}
	virtual void showStatus() const override;
	void showImage() const;
	virtual void save(std::ofstream& outFile) const override;
};

#endif
