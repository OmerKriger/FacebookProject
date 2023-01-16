#ifndef __VIDEOSTATUS_H
#define __VIDEOSTATUS_H
#include <string>
#include <iostream>
#include <fstream>
#include "Status.h"
#include "BackupRecovery.h"


class VideoStatus : public Status
{
	std::string video;
	VideoStatus(VideoStatus&);
public:
	VideoStatus(std::ifstream& inFile);
	VideoStatus(const std::string& text, const std::string& name, const std::string& video);
	virtual void showStatus() const override;
	virtual void save(std::ofstream& outFile) override;
	void showVideo() const;
};
#endif
