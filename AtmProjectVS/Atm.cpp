#include "stdafx.h"
#include "Atm.h"


Atm::Atm()
{
	/*
	Language pl;
	pl.name = "polski";
	pl.shortCut = "pl";
	Language eng;
	eng.name = "angielski";
	eng.shortCut = "eng";

	this->langList.push_back(pl);
	this->langList.push_back(eng);
	*/

	this->safe = new AtmSafe();
}

std::map<std::string, std::map<std::string, std::string>>* Atm::getLanguageList()
{
	return &this->langList;
}

/*
Language Atm::getLanguage()
{
return this->lang;
}

void Atm::setLanguage(Language lg)
{
this->lang = lg;
}
*/

void Atm::setId(int id)
{
	this->id = id;
}

int Atm::getId()
{
	return this->id;
}

void Atm::addToSafe(std::map<unsigned int, unsigned int> *safeContent)
{
	this->safe->addContent(safeContent);
}

AtmSafe* Atm::getSafe()
{
	return this->safe;
}

void Atm::setLocalization(Address *address)
{
	this->localization = address;
}

Address Atm::getLocalization()
{
	return *this->localization;
}

void Atm::setOwner(Company *company)
{
	this->owner = company;
}

Company* Atm::getOwner()
{
	return this->owner;
}

void Atm::loadCard(Card *card)
{
	this->card = card;
}

Card *Atm::getCard() {
	return this->card;
}

void Atm::pullOutCard()
{
	this->isAuthorized = false;
	this->availableMoneyAmount = 0;
	delete this->card;
}

void Atm::rejectCard()
{

}

bool Atm::isCardLoaded()
{
	if (this->card == nullptr) {
		return false;
	}
	return true;
}

bool Atm::chooseLanguage(Language lg)
{
	return true;
}

void Atm::loadPlainPIN(std::string PIN)
{
	this->plainPin = PIN;
}

bool Atm::checkPIN()
{
	if (this->plainPin == "") return false;

	try {
		Company *company = this->supportedCompaniesList.at(this->card->getCardDistributorId());
		//std::cout << company->toString() << std::endl;
		//company->printAccountsList();

		this->isAuthorized = company->checkPIN(this->card, this->plainPin);
	}
	catch (const std::out_of_range &err) {
		std::cout << "Your card is not supported in this ATM." << std::endl;
	}

	return this->isAuthorized;
}

bool Atm::getIsAuthorized()
{
	return this->isAuthorized;
}

float Atm::getAvailableMoney()
{
	if (this->isAuthorized && this->card != nullptr) {
		Company *comp = supportedCompaniesList.at(this->card->getCardDistributorId());
		this->availableMoneyAmount = comp->getFundsOnAccount(this->card->getAccountNumber());
	}

	return this->availableMoneyAmount;
}

void Atm::addSupportedCompanyToList(Company *comp)
{
	this->supportedCompaniesList[comp->getCompanyId()] = comp;
}

bool Atm::makeWithdraw(unsigned int amount, bool printContribution)
{
	this->safe->getMoneyFromSafe2(amount);
	/*
	if (this->safe->getMoneyFromSafe(amount)) {
		Company *comp = this->supportedCompaniesList.at(this->card->getCardDistributorId());
		comp->getMoneyFromAccount(this->card->getAccountNumber(), (float)amount);
		return true;
	}
	*/
	return false;
}



void Atm::printAtm()
{
	std::cout << "ATM - Id: " << id << ", plainPIN in memory: " << plainPin << ", IsOn: ";
	(isOn == true) ? std::cout << " true" << std::endl : std::cout << " false" << std::endl;

	//if(this->localization == nullptr) std::cout << "KLOPS" << std::endl;
	//std::cout << this->localization->toString() << std::endl;
	//std::cout << "Localization: ( " << str << " ) " << std::endl;
	//std::cout << ", Owner: " << owner->toString() << ", " << std::endl;
}
