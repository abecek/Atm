#pragma once

#include "AtmSafe.h"
#include "Address.h"
#include "Card.h"
#include "Company.h"

struct Language {
	std::string shortCut;
	std::string name;
};

class Atm
{
public:
	Atm();
	void setId(int id);
	int getId();

	void addToSafe(std::map<unsigned int, unsigned int> *safeContent);
	AtmSafe* getSafe();

	void setLocalization(Address *address);
	Address getLocalization();
	void setOwner(Company *company);
	Company* getOwner();

	void loadCard(Card *card);
	Card *getCard();
	void pullOutCard();
	void rejectCard();
	bool isCardLoaded();

	bool chooseLanguage(Language lg);
	void loadPlainPIN(std::string PIN);
	bool checkPIN();
	bool getIsAuthorized();

	float getAvailableMoney();
	bool makeWithdraw(unsigned int amount, bool printContribution = false);

	std::map<std::string, std::map<std::string, std::string>>* getLanguageList();
	//Language getLanguage();
	//void setLanguage(Language lg);

	void addSupportedCompanyToList(Company *comp);
	//std::map<unsigned int id, *Company> getSupportedCompaniesList();

	void printAtm();

protected:
	int id;
	std::string plainPin = "";
	bool isOn = true;
	bool isAuthorized = false;
	float availableMoneyAmount = 0;

	std::map<std::string, std::map<std::string, std::string>> langList = {
		{ "pl",{
			{ "welcome", "Witamy w naszym bankomacie." },
			{ "possibleCards", "Lista mozliwych kart: " },
			{ "putInCardWithId", "Wloz karte do bankomatu o id: " },
			{ "wrongCardId", "Bledne id karty." },
			{ "chooseLanguage", "Wybierz jezyk: " },
			{ "wrongData", "Zle dane." },
			{ "number", "Numer: " },
			{ "chosenLanguage", "Wybrano jezyk: " },
			{ "wrongPin", "Bledny PIN." },
			{ "enterPin", "Wprowadz PIN: " },
			{ "accessToAccountIsGranted", "Otrzymano dostep do konta!" },
			{ "chooseAction", "Wybierz czynnosc: " },
			{ "withdrawMoney", "Wyplata srodkow" },
			{ "withdrawSpecificAmountOfMoney", "Wyplac konkretna kwote" },
			{ "exit", "Wyjscie." },
			{ "availableAmounts", "Dostepne kwoty:" },
			{ "enterAmountOfMoney", "Wprowadz kwote: " },
			{ "withdrawInformation1", "Wyplacono: " },
			{ "withdrawInformation2", " z konta, przy uzyciu karty." },
			{ "notEnoughMoneyOnAccount", "Brak wystarczajacych srodkow na koncie." },
			{ "pressESCtoRejectCard", "Nacisnij ESC, by wysunac karte lub inny przycisk, by kontynuowac." },
			{ "putYourCardIntoATM", "Wloz karte do bankomatu." },
			{ "pressESCtoExitATM", "Nacisnij ESC, by przerwac prace programu lub inny przycisk, by kontynuowac." },
		} },

		{ "eng",{
			{ "welcome", "Welcome in our Atm." },
			{ "possibleCards", "List of possible cards: " },
			{ "putInCardWithId", "Put card in Atm with Id: " },
			{ "wrongCardId", "Wrong cards Id." },
			{ "chooseLanguage", "Choose language: " },
			{ "wrongData", "Wrong data." },
			{ "number", "Number: " },
			{ "chosenLanguage", "Chosen language: " },
			{ "wrongPin", "Wrong PIN." },
			{ "enterPin", "Enter PIN: " },
			{ "accessToAccountIsGranted", "Access to account is granted!" },
			{ "chooseAction", "Choose action: " },
			{ "withdrawMoney", "Withdraw your money" },
			{ "withdrawSpecificAmountOfMoney", "Withdraw specific money amount" },
			{ "exit", "Exit." },
			{ "availableAmounts", "Available amounts:" },
			{ "enterAmountOfMoney", "Enter money amount: " },
			{ "withdrawInformation1", "Withdrawed money: " },
			{ "withdrawInformation2", " from account, by using card." },
			{ "notEnoughMoneyOnAccount", "There is not enough money on the account." },
			{ "pressESCtoRejectCard", "Press ESC to reject card or other button to continue." },
			{ "putYourCardIntoATM", "Put in card into ATM." },
			{ "pressESCtoExitATM", "Press ESC to finish programs work or other button to continue." },
		} },
	};

	//Language lang;

	AtmSafe *safe = nullptr;
	Address *localization = nullptr;
	Company *owner = nullptr;
	Card *card = nullptr;

	std::map<unsigned int, Company*> supportedCompaniesList;

};


