#pragma once
#include <string>

class OutOfRangeException
{
public:
	OutOfRangeException(std::string message) : message{ message } {}
	std::string getMessage() const { return message; }
private:
	std::string message;
};