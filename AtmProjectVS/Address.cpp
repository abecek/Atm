#include "stdafx.h"
#include "Address.h"


Address::Address()
{
	//ctor
}

Address::Address(std::string country, std::string city, std::string street, std::string number, PostCode *pc) :
	country(country),
	city(city),
	street(street),
	number(number),
	postCode(pc)
{
	//ctor
}


void Address::setPostCode(std::string content)
{
	PostCode *ps = new PostCode();
	ps->setPostCodeFromString(content);
	this->postCode = ps;
}

PostCode* Address::getPostCode() 
{
	return this->postCode;
}

std::string Address::getPostCodeAsString()
{
	return postCode->getPostCodeAsString();
}

std::string Address::toString()
{
	std::string output = "";
	if (this->postCode == nullptr) {
		output += " Address - Country: " + this->country;
		output += ", town: " + this->city;
		output += ", street: " + this->street + ", number: " + this->number;
	}
	else {
		output += " Address - Country: " + country + ", post-code: ";
		output += this->postCode->getPostCodeAsString() + ", town: ";
		output += city + ", street: " + street + ", number: " + number;
	}

	return output;
}

Address::~Address()
{
	//dtor
}
