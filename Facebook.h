#ifndef __FACEBOOK_H
#define __FACEBOOK_H
#include "Date.h"
#include "Exceptions.h"
#include "BackupRecovery.h"
#include <list>

#define TEST 0 // TEST == 0 is no test setup
#define COMPARE_TEST 0

class Facebook 
{
	std::list<Member*> members;
	std::list<Page*> fanPages;
	Facebook(const Facebook&);
	void testCompareOperators()								const;
	void __Init__()											noexcept(false);
public:
	~Facebook();
	Facebook()												noexcept(false);
	void saveFacebookConnections()							const noexcept(false);
	void createMember(const std::string& name, Date bDay)	noexcept(false);
	void createFanPage(const std::string& name)				noexcept(false);
	void showAllMembers()									const;
	void showAllPages()										const;
	bool isEmpty()											const;
	bool memberNameCheck(const std::string& name)			const;
	bool pageNameCheck(const std::string& name)				const;
	const Member& getMember(const std::string& name)		const noexcept(false);
	Member& getMember(const std::string& name)				noexcept(false);
	const Page& getPage(const std::string& name)			const noexcept(false);
	Page& getPage(const std::string& name)					noexcept(false);
private: // private methods with friend access
	void addMember(Member* newMember);
	void addPage(Page* newPage);
	friend class BackupRecovery;
};

#endif
