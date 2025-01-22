//Code written for an assingment in CS 341 at Butler University

#ifndef STATUS_H
#define STATUS_H

#include <string>

class Status
{
	public:
		Status();
		~Status() {}
		
		std::string getString();
		int getInt();
		void setString(std::string status);
		void setInt(int status);

	
	private:
		int statusInt_;
		std::string statusString_;
};

#endif