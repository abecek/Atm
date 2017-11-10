#pragma once

#include "User.h"

enum cardType {
	credit,
	debit,
	payment,
};

class Card
{
public:
	Card();
	Card(User *cardOwner, unsigned int cardDistId, std::string cardNr, std::string accountNr, cardType type);

	User *getCardOwner();
	unsigned int getCardDistributorId();
	std::string getCardNumber();
	std::string getAccountNumber();

	//void setIsAuthenticated(bool flag);
	bool getIsAuthenticated();
	void setIsBlocked(bool flag);
	bool getIsBlocked();
	void setCardType(cardType type);
	cardType getCardType();

	std::string toString();
	virtual ~Card();
private:
	User *cardOwner;
	unsigned int cardDistributorId;
	std::string cardNumber;
	std::string accountNumber;

	bool isAuthenticated = false;
	bool isBlocked = false;;
	cardType type;

};