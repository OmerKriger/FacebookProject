#ifndef __VIDEOSTATUS_H
#define __VIDEOSTATUS_H
#include <string>
#include <iostream>
#include "Status.h"

class VideoStatus : public Status
{
	std::string video;
	VideoStatus(VideoStatus&);
public:
	VideoStatus(const std::string& text, const std::string& name, const std::string& video);
	virtual void showStatus() const override;
	void showVideo() const;
};
#endif
