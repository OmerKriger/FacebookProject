#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H
#include <string>

class SystemException : public std::exception
{
private:
	std::string message = "General ERROR";
public:
	const char* what() { return (this->message).c_str(); }
};

class MemberException : public SystemException
{
	std::string message = "Action on Member failed: ";
	int errorCode;
public:
	const enum memberErrorList { UNDEFINED = 0, ALREADY_FRIENDS, ALREADY_FOLLOW, FRIEND_HIMSELF, NOT_FRIENDS, NOT_FOLLOW, NAME_SETTED, ILLEGAL_NAME };
	MemberException(const std::string& msg = "undefined", int errorCode = 0) : errorCode(errorCode) { this->message += msg; }
	int getErrorCode() const { return errorCode; }
};

class PageException : public SystemException
{
	std::string message = "Action on Page failed: ";
	int errorCode;
public:
	const enum pageErrorList { UNDEFINED = 0, ALREADY_FOLLOWED, NOT_FOLLOW, NAME_SETTED, ILLEGAL_NAME };
	PageException(const std::string& msg = "undefined", int errorCode = 0) : errorCode(errorCode) { this->message += msg; }

};

class StatusException : public SystemException
{
	std::string message = "Action on Status failed: ";
public:
	StatusException(const std::string& msg = "undefined") { this->message += msg; }
};

class DateException : public SystemException
{
	std::string message = "";
public:
	DateException(const std::string& msg = "undefined date error") { this->message += msg; }
};

class UtilitiesException : public SystemException
{
	std::string message = "Page action was failed: ";
public:
	UtilitiesException(const std::string& msg = "undefined") { this->message += msg; }
};

class FacebookException : public SystemException
{
	std::string message = "Facebook action failed: ";
	int errorCode;
public:
	const enum facebookErrorList { UNDEFINED = 0, INIT_FAILED, MEMBER_NOT_FOUND, PAGE_NOT_FOUND, MEMBER_EXIST, PAGE_EXIST };
	FacebookException(const std::string& msg = "undefined", int errorCode=0 ) : errorCode(errorCode) { this->message += msg; }
};

#endif // !__EXCEPTIONS_H
