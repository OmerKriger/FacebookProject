#ifndef __IMAGESTATUS_H
#define __IMAGESTATUS_H

#include "Status.h"
#include <iostream>

class ImageStatus : public Status
{
	std::string image;
	ImageStatus(ImageStatus&);
public:
	ImageStatus(std::string text, std::string name, std::string image);
	virtual void showStatus() const override;
	void showImage() const;
};
#endif
