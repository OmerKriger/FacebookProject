#ifndef __ENTITY_H
#define __ENTITY_H

#include <string>
#include "Status.h"
#include <list>

class page;

class Entity // abstract class
{
private:
	//c'tors
	Entity(const Entity&);
protected:
	// Data
	std::string name;
	std::list <Entity*> connections;
	std::list<Status*> wall;
	//setters
	virtual void setName(const std::string& str) noexcept(false);
public:
	//c'tors
	Entity(const std::string& name);
	virtual ~Entity();
	//Add/remove
	virtual void addConnection(Entity* member) = 0;
	virtual void removeConnection(Entity* member) = 0;
	//prints
	virtual void showConnections() const = 0;
	virtual void showEntityStatus() const = 0;
	// Getters
	virtual const std::string& getName() const = 0;
	virtual int getSizeOfConnections() const = 0;
};
#endif

