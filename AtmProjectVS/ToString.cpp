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
