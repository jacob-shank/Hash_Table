//Code written for an assingment in CS 341 at Butler University

#ifndef HASHENTRY_H
#define HASHENTRY_H


#include "Status.h"

class HashEntry
{	
	public:
		//constructors and destructors
		HashEntry();
		HashEntry(int, int);
		virtual ~HashEntry();
		
		//getters
		int getKey();
		int getValue();
		Status getStatus();
		
		//setters
		void setKey(int key);
		void setValue(int value);
		void setStatus(std::string status);
	
	
	private:
		int key_;
		int value_;
		Status status_;
};

#endif