#ifndef __STATUS_H
#define __STATUS_H
#pragma warning(disable : 4996)
#include "Date.h"
#include "Exceptions.h"
#include "BackupRecovery.h"
#include <iostream>
#include <fstream>
#include <string>

class Status
{
protected:
	Date date; 
	std::string text;
	std::string creator;
	void setText(const std::string& str) noexcept(false);
public:
	Status(Status&) = default;
	Status(std::ifstream& inFile);
	Status(const std::string& text, const std::string& name) noexcept(false);
	virtual ~Status() {};
	virtual void save(std::ofstream& outFile) const;
	const Date& getDate() const;
	const std::string getText() const;
	virtual void showStatus() const;
	const std::string& getCreator() const;
	// Operators
	bool operator==(const Status& status) const; // need to fit for Image and video
	bool operator!=(const Status& status) const;
};
#endif