#include "stdafx.h"
#include "User.h"


User::User()
{
	//ctor
}

User::User(std::string name1, std::string name2, std::string surname, Address *address) :
	name1(name1),
	surname(surname),
	name2(name2),
	address(address)
{

}

std::string User::toString()
{
	std::string output = "";

	output += " User - name1: " + name1 + ", name2: " + name2;
	if (surname != "") {
		output += ", surname: " + surname;
	}
	if (address != nullptr) {
		output += ", Address: (" + address->toString() + " ) ";
	}

	return output;
}

User::~User()
{
	//dtor
}