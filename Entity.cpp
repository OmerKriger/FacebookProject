#include "Entity.h"
using namespace std;

Entity::Entity(const string& name)
{
	try 
	{
		setName(name);
	}
	catch (EntityException& e)
	{
		throw e;
	}
}

void Entity::setName(const string& str)
{
	if (name.empty() == false)
		throw EntityException("Name can't be changed after has been setted ! ", EntityException::EntityErrorList::NAME_SETTED);
	if (str.size() <= 1)
		throw EntityException("Name is too short ! ", EntityException::EntityErrorList::ILLEGAL_NAME);
	name = str;
}

const string& Entity::getName() const
{
	 return name; 
}

int Entity::getSizeOfConnections() const
{
	return connections.size();
}

