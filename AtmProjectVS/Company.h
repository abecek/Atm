#pragma once

#include "Address.h"
#include "Card.h"


class Account {
public:
	Account();
	Account(unsigned int id, std::string pin = "");
	static unsigned int pinLength;

	std::string getAccountNumber();
	Account setAccountNumber(std::string number);
	float getMoneyAmount();
	void setMoneyAmount(float amount);
	unsigned int getAccountId();

	std::string getCardPIN();
	Card *getCard();
	void setCard(Card *card);

private:
	unsigned int accountId;
	std::string accountNumber;
	std::string cardPIN;
	float moneyAmount = 0;
	Card *card;
};

class Company
{
private:
	unsigned int accountsCount = 0;
	unsigned int companyId;

	static unsigned int banksCount;

	std::string IBAN = "PL";
	std::string name;
	Address address;
	bool isBank = true;
	std::map<std::string, Account> accountsList;

	Account* getAccount(std::string accountNumber);
	std::map<std::string, Account> getAccountsList();
public:
	static std::string generateRandomPIN(unsigned int length);
	Company();
	Company(std::string name, Address address);
	std::string toString();
	unsigned int getCompanyId();

	std::string createNewAccount(float moneyAmount = 0);
	void addAccount(Account *account);
	Card *generateCardForAccount(User *cardOwner, std::string cardNr, std::string accountNr, cardType type);

	bool checkPIN(Card *card, std::string plainPIN);
	float getFundsOnAccount(std::string accountNumber);
	void getMoneyFromAccount(std::string accountNumber, float value);

	std::string getAccountsAsString();
	void printAccountsList();
	unsigned int getAccountsCount();

	virtual ~Company();

};

