//Code written for an assingment in CS 341 at Butler University

#include "HashEntry.h"


//constructors destructors
HashEntry::HashEntry()
{
	status_.setString("EMPTY");
}
HashEntry::HashEntry(int key, int value)
{
	key_ = key;
	value_ = value;
	status_.setString("OCCUPIED");
}
HashEntry::~HashEntry()
{
	
}

//getters
int HashEntry::getKey()
{
	return key_;
}
int HashEntry::getValue()
{
	return value_;
}
Status HashEntry::getStatus()
{
	return status_;
}

//setters
void HashEntry::setKey(int key)
{
	key_ = key;
}
void HashEntry::setValue(int value)
{
	value_ = value;
}
void HashEntry::setStatus(std::string status)
{
	status_.setString(status);
}
