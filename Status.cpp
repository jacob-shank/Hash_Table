//Code written for an assingment in CS 341 at Butler University

#include "Status.h"

Status::Status()
{
	statusInt_ = 0;
}
std::string Status::getString()
{
	return statusString_;
}
int Status::getInt()
{
	return statusInt_;
}
void Status::setString(std::string status)
{
	if(status == "EMPTY")
	{
		statusString_ = "EMPTY";
		statusInt_ = 0;
	}
	if(status == "OCCUPIED")
	{
		statusString_ = "OCCUPIED";
		statusInt_ = 1;
	}
	if(status == "REMOVED")
	{
		statusString_ = "REMOVED";
		statusInt_ = 2;
	}
}
void Status::setInt(int status)
{
	if(status == 0)
	{
		statusInt_ = 0;
		statusString_ = "EMPTY";
	}
	if(status == 1)
	{
		statusInt_ = 1;
		statusString_ = "OCCUPIED";
	}
	if(status == 2)
	{
		statusInt_ = 2;
		statusString_ = "REMOVED";
	}
}