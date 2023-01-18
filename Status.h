#ifndef __STATUS_H
#define __STATUS_H
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include "Date.h"
#include "Exceptions.h"


class Status
{
protected:
	Date date; 
	std::string text;
	std::string creator;
	mutable bool isSaved; // mutable for change in save method
	void setText(const std::string& str)						noexcept(false);
public:
	static const int TYPE_LEN = 3;
	Status(std::ifstream& inFile);
	Status(const std::string& text, const std::string& name)	noexcept(false);
	virtual ~Status() {}
	virtual void save(std::ofstream& outFile)					const;
	void saveType(std::ofstream& outFile)						const;
	const Date& getDate()										const;
	const std::string getText()									const;
	virtual void showStatus()									const;
	const std::string& getCreator()								const;
	// Operators
	bool operator==(const Status& status)						const; // need to fit for Image and video
	bool operator!=(const Status& status)						const;
	enum statusType
	{
		TEXT = 1, // equal 1 for start counting from 1 and not zero 
		IMAGE,
		VIDEO
	};
};
#endif