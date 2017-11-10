#include "stdafx.h"
#include "Card.h"
#include "ToString.h"

Card::Card()
{
	//ctor
}
Card::Card(User *cardOwner, unsigned int cardDistId, std::string cardNr, std::string accountNr, cardType type) :
	cardOwner(cardOwner),
	cardDistributorId(cardDistId),
	cardNumber(cardNr),
	accountNumber(accountNr),
	type(type)
{

}

User *Card::getCardOwner()
{
	return cardOwner;
}

unsigned int Card::getCardDistributorId()
{
	return cardDistributorId;
}

std::string Card::getCardNumber()
{
	return cardNumber;
}

std::string Card::getAccountNumber()
{
	return accountNumber;
}

bool Card::getIsAuthenticated()
{
	return isAuthenticated;
}

void Card::setIsBlocked(bool flag)
{

}

bool Card::getIsBlocked()
{
	return isBlocked;
}

void Card::setCardType(cardType type)
{

}

cardType Card::getCardType()
{
	return type;
}

std::string Card::toString()
{
	std::string output = "";
	output += " Card - CardNumber: " + cardNumber + "\n";
	output += "AccountNumber: " + accountNumber + "\n";
	output += ", currentState: \n, isAuthenticated: ";
	output += (isAuthenticated == true) ? "true" : "false";
	output += "\n, isBlocked: ";
	output += (isBlocked == true) ? "true" : "false";

	// todo: have to change switch to if because for example "cardType::credit:" wont be working
	/*switch (this->type) {
		credit:
			output += ", cardType: credit";
			break;
		debit:
			output += ", cardType: debit";
			break;
		payment:
			output += ", cardType: payment";
			break;
	}*/
	if (cardOwner != nullptr) {
		output += "\n User - ( " + cardOwner->toString() + " )";
	}
	//if(cardDistributorId != 0) {
	output += "\n CompanyId - ( " + ToString<int>::SSTR(cardDistributorId) + " )";
	//}

	output += "\n";
	return output;
}

Card::~Card()
{
	//dtor
}