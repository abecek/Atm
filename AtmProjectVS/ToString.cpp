#include "stdafx.h"
#include "ToString.h"

#include <sstream>


std::string ToString<int>::SSTR(int x)
{
	return static_cast<std::ostringstream &>((std::ostringstream() << std::dec << x)).str();
}

std::string ToString<float>::SSTR(float x)
{
	return static_cast<std::ostringstream &>((std::ostringstream() << std::dec << x)).str();
}

std::string ToString<std::string>::SSTR(std::string x)
{
	return static_cast<std::ostringstream &>((std::ostringstream() << std::dec << x)).str();
}

std::string ToString<std::map<unsigned int, unsigned int>>::SSTR(std::map<unsigned int, unsigned int> x)
{
	std::string str = "";
	for (auto it = x.begin(); it != x.end(); it++) {
		str += it->first + " ";
		str += it->second + "\n";
	}
	return str;
	//return static_cast<std::ostringstream &>((std::ostringstream() << std::dec << x)).str();
}
