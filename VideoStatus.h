#ifndef __VIDEOSTATUS_H
#define __VIDEOSTATUS_H

#include "Status.h"
#include <iostream>

class VideoStatus : public Status
{
	std::string video;
	VideoStatus(VideoStatus&);
public:
	VideoStatus(std::string text, std::string name, std::string video);
	virtual void showStatus() const override;
	void showVideo() const;
};
#endif
