#pragma once

#include "Address.h"

class User
{
public:
	User();
	User(std::string name1, std::string surname, std::string name2 = "", Address *address = nullptr);
	std::string toString();
	virtual ~User();
protected:
	std::string name1, name2, surname;
	Address *address;
};

