#include "stdafx.h"
#include "Company.h"
#include "ToString.h"

unsigned int Account::pinLength = 6;

Account::Account()
{

}

Account::Account(unsigned int id, std::string pin)
{
	this->accountId = id;
	if (pin == "") {
		this->cardPIN = Company::generateRandomPIN(Account::pinLength);
	}
	else {
		if (pin.length() > Account::pinLength) {
			pin = pin.substr(0, Account::pinLength);
		}
		this->cardPIN = pin;
	}

}

Card* Account::getCard()
{
	return this->card;
}

void Account::setCard(Card *card)
{
	this->card = card;
}

unsigned int Account::getAccountId()
{
	return this->accountId;
}

std::string Account::getCardPIN()
{
	return this->cardPIN;
}

std::string Account::getAccountNumber()
{
	return this->accountNumber;
}

Account Account::setAccountNumber(std::string number)
{
	this->accountNumber = number;
	return *this;
}

float Account::getMoneyAmount()
{
	return this->moneyAmount;
}

void Account::setMoneyAmount(float amount)
{
	this->moneyAmount = amount;
}


unsigned int Company::banksCount = 0;

Company::Company()
{
	this->companyId = this->banksCount;
	this->banksCount++;
}

Company::Company(std::string name, Address address) : name(name), address(address)
{
	this->companyId = this->banksCount;
	this->banksCount++;
	/*
	this->name = name;
	this->address = address;
	*/
}

std::string Company::toString()
{
	std::string output = "";
	output += " Company - Name: " + name;
	output += ", CompanyId: " + ToString<int>::SSTR(companyId);
	output += "\n isBank: ";
	output += (isBank == true) ? "true" : "false";
	output += ", address: ( " + address.toString() + " )";

	output += "\n";
	return output;
}

unsigned int Company::getCompanyId()
{
	return this->companyId;
}

std::string Company::createNewAccount(float moneyAmount)
{
	//std::string id = std::to_string(this->bankId);
	std::string bId = ToString<int>::SSTR(this->companyId);
	while (bId.length() < 4) {
		bId = "0" + bId;
	}

	std::string accId = ToString<int>::SSTR((this->accountsCount + 1));
	while (accId.length() < 12) {
		accId = "0" + accId;
	}

	std::string accNum = "83" + bId + "1111" + accId;
	Account *acc = new Account((this->accountsCount + 1));
	acc->setAccountNumber(accNum);
	acc->setMoneyAmount(moneyAmount);

	//Adding new account to Bank AccountsList
	this->addAccount(acc);
	this->accountsCount++;

	return acc->getAccountNumber();
}

void Company::addAccount(Account *account)
{
	this->accountsList[account->getAccountNumber()] = *account;
}

Account* Company::getAccount(std::string accNum)
{
	Account *acc = nullptr;
	try {
		acc = &accountsList.at(accNum);
	}
	catch (const std::out_of_range &oor) {
		std::cout << "Account with this accountNumber: " << accNum << ", does not exist in this Company/Bank: ";
		std::cout << this->name << ", id: " << this->companyId << std::endl;
	}

	return acc;
}

Card* Company::generateCardForAccount(User *cardOwner, std::string cardNr, std::string accountNr, cardType type)
{
	Account *acc = this->getAccount(accountNr);
	Card *card = new Card(cardOwner, this->companyId, cardNr, accountNr, type);
	acc->setCard(card);

	return card;
}

bool Company::checkPIN(Card *card, std::string plainPIN)
{
	Account *acc = this->getAccount(card->getAccountNumber());
	if (acc->getCardPIN() == plainPIN) return true;

	return false;
}

float Company::getFundsOnAccount(std::string accountNumber)
{
	Account *acc = this->getAccount(accountNumber);
	return acc->getMoneyAmount();
}

void Company::getMoneyFromAccount(std::string accountNumber, float value)
{
	Account *acc = this->getAccount(accountNumber);
	acc->setMoneyAmount(acc->getMoneyAmount() - value);
}


std::string Company::generateRandomPIN(unsigned int length) {
	std::string str = "";

	std::string alpha = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (unsigned int i = 0; i < length; ++i) {
		str += alpha.at(std::rand() % (alpha.length() - 1));
	}

	return str;
}

std::string Company::getAccountsAsString()
{
	std::string output = "";
	auto it = this->accountsList.begin();
	for (int i = 0; it != this->accountsList.end(); i++) {
		output += "Id: " + ToString<int>::SSTR(it->second.getAccountId());
		output += ", Nr:" + ToString<std::string>::SSTR(it->second.getAccountNumber());
		output += ", Money: " + ToString<float>::SSTR(it->second.getMoneyAmount()) + "\n";
		it++;
	}

	return output;
}

void Company::printAccountsList()
{
	auto it = this->accountsList.begin();
	for (int i = 0; it != this->accountsList.end(); i++) {
		if (i == 0) std::cout << "Company - Id: " << this->companyId << " AccountsList:" << std::endl;
		std::cout << "Id: " << it->second.getAccountId() << ", Nr:" << it->second.getAccountNumber();
		std::cout << ", Pin: " << it->second.getCardPIN();
		std::cout << ", Money: " << it->second.getMoneyAmount() << std::endl;
		it++;
	}
	std::cout << std::endl;
}

unsigned int Company::getAccountsCount()
{
	return this->accountsCount;
}

Company::~Company()
{
	this->banksCount--;
}
