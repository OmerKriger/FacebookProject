#ifndef __VIDEOSTATUS_H
#define __VIDEOSTATUS_H
#include "Status.h"

class VideoStatus : public Status
{
	std::string video;
	VideoStatus(VideoStatus&);
public:
	VideoStatus(std::ifstream& inFile);
	VideoStatus(const std::string& text, const std::string& name, const std::string& video);
	const std::string& getPath() { return video; };
	virtual void showStatus() const override;
	virtual void save(std::ofstream& outFile) const override;
	void showVideo() const;
};
#endif
