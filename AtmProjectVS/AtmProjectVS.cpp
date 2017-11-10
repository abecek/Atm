// AtmProjectVS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "Atm.h"

using namespace std;

const int ESCAPE = 27;

int main()
{
	Address BankAddress("Polska", "Lodz", "Pilsudskiego", "6");
	BankAddress.setPostCode("90-200");
	Company *AtmOwner = new Company("XYZ Bank", BankAddress);

	Address *AtmAddress = new Address("Polska", "Lodz", "Piotrkowska", "43");
	AtmAddress->setPostCode("90-265");

	//Creating Atm for tests
	Atm *CashMachine = new Atm();
	CashMachine->setId(1);
	CashMachine->setLocalization(AtmAddress);
	CashMachine->setOwner(AtmOwner);
	CashMachine->addSupportedCompanyToList(AtmOwner);
	std::map<std::string, std::map<std::string, std::string>> *possibleLangs = CashMachine->getLanguageList();
	//CashMachine->printAtm();
	//cout << AtmAddress->toString() << endl << endl;
	//cout << AtmOwner->toString() << endl << endl;


	Address *UserAddress1 = new Address("Polska", "Zgierz", "Losowa", "123");

	User *Client1 = new User("Piotr", "Kowalski", "", UserAddress1);
	User *Client2 = new User("Rafal", "Wszedobylski");
	User *Client3 = new User("Marcin", "JakisTam");
	User *Client4 = new User("Jan", "Zdobywca");

	Address ClientBankAddress("Polska", "Warszawa", "Aleje Jerozolimskie", "253");
	Company *ClientBank = new Company("ZYX BigBank", ClientBankAddress);

	string accNumber1 = ClientBank->createNewAccount(1100.5);
	string accNumber2 = ClientBank->createNewAccount(190);
	string accNumber3 = ClientBank->createNewAccount(11.99);

	CashMachine->addSupportedCompanyToList(ClientBank);

	Company *ClientBank2 = new Company("ZYX BigBank", ClientBankAddress);
	string accNumber4 = ClientBank2->createNewAccount(350);

	vector<Card*> cardsList;
	// todo: Add autogenerating cardNumber when creating card for the account and move CardOwner into Account class
	Card *card1 = ClientBank->generateCardForAccount(Client1, "1", accNumber1, cardType::credit);
	cardsList.push_back(card1);
	Card *card2 = ClientBank->generateCardForAccount(Client2, "2", accNumber2, cardType::credit);
	cardsList.push_back(card2);
	Card *card3 = ClientBank->generateCardForAccount(Client3, "3", accNumber3, cardType::payment);
	cardsList.push_back(card3);

	Card *card4 = ClientBank2->generateCardForAccount(Client4, "11", accNumber4, cardType::debit);
	cardsList.push_back(card4);

	CashMachine->addSupportedCompanyToList(ClientBank2);

	std::map<unsigned int, unsigned int> safeContent = {
		{ 20, 5 },
		{ 50, 12 },
		{ 100, 11 },
		{ 200, 7 },
		{ 500, 4 },
	};
	CashMachine->addToSafe(&safeContent);

	map<string, map<string, string>> *langs = CashMachine->getLanguageList();

	char c1 = '96';
	do {
		cout << endl << "---------------------- Banks/Atm/Cards Stats ----------------------" << endl << endl;
		ClientBank->printAccountsList();
		ClientBank2->printAccountsList();
		CashMachine->getSafe()->printSafe();

		string chosenLang = "eng";

		unsigned int chosenCardId;
		cout << endl << langs->at(chosenLang)["possibleCards"] << endl;
		for (unsigned int i = 0; i < cardsList.size(); i++) {
			cout << "Id: " << i + 1 << " - AccNumber: " << cardsList.at(i)->getAccountNumber() << endl;
		}

		cout << endl << "-------------------------- End of Stats ---------------------------" << endl << endl;

		cout << endl << langs->at(chosenLang)["putInCardWithId"];
		cin >> chosenCardId;
		try {
			CashMachine->loadCard(cardsList.at(chosenCardId - 1));
			//cout << CashMachine->getCard()->toString();
		}
		catch (const std::out_of_range &err) {
			cout << langs->at(chosenLang)["wrongCardId"] << endl;
		}

		cout << "###########################" << endl;
		cout << langs->at("pl")["welcome"] << endl;
		cout << langs->at("eng")["welcome"] << endl;
		cout << "###########################" << endl;

		if (CashMachine->isCardLoaded()) {
			while (c1 != ESCAPE) {
				unsigned int x = 0;
				string plainPIN;
				do {
					//cout << endl << langs->at("pl")["chooseLanguage"] << endl;
					cout << endl << langs->at(chosenLang)["chooseLanguage"] << endl;
					auto it = langs->begin();
					for (unsigned i = 0; i < langs->size(); i++) {
						cout << i + 1 << ". - " << it->first << endl;
						++it;
					}

					cout << endl << langs->at(chosenLang)["number"];
					cin >> x;
					if (x < 1 || x > langs->size()) {
						cout << endl << langs->at(chosenLang)["wrongData"] << endl;
						continue;
					}

					x == 2 ? chosenLang = "pl" : chosenLang = "eng";
					//CashMachine->setLanguage(chosenLang);
					cout << endl << langs->at(chosenLang)["chosenLanguage"] << chosenLang << endl;


					int i = 0;
					do {
						if (i > 0) cout << langs->at(chosenLang)["wrongPin"] << endl;
						cout << langs->at(chosenLang)["enterPin"];
						cin >> plainPIN;
						c1 = *"c";
						CashMachine->loadPlainPIN(plainPIN);
						i++;
					} while (!CashMachine->checkPIN());

					if (CashMachine->getIsAuthorized()) {
						char c2;
						cout << endl << langs->at(chosenLang)["accessToAccountIsGranted"] << endl << endl;

						cout << langs->at(chosenLang)["chooseAction"] << endl;
						cout << "1 - " << langs->at(chosenLang)["withdrawMoney"] << endl;
						cout << "2 - " << langs->at(chosenLang)["withdrawSpecificAmountOfMoney"] << endl;
						cout << "3 - " << langs->at(chosenLang)["exit"] << endl;
						cin >> c2;

						vector<unsigned int> amountsTab = { 20, 50, 80, 100, 150, 200, 300, 400 };
						unsigned int moneyToWithdraw = 0;
						unsigned int moneyToWithdrawOption = 9;
						if (c2 == '1') {

							bool flag = false;
							do {
								cout << endl << langs->at(chosenLang)["availableAmounts"];
								for (unsigned int i = 0; i < ((amountsTab.size()) / 2); i++) {
									cout << endl << (i + 1) << " - " << amountsTab[i] << "     " << (i + 5) << " - " << amountsTab[i + 4];
								}
								cout << endl;
								cin >> moneyToWithdrawOption;
								flag = (moneyToWithdrawOption >= 1 && moneyToWithdrawOption <= 8) ? true : false;
							} while (!flag);

							moneyToWithdraw = amountsTab[moneyToWithdrawOption - 1];

						}
						else if (c2 == '2') {
							cout << langs->at(chosenLang)["enterAmountOfMoney"];
							cin >> moneyToWithdraw;
						}
						else if (c2 == '3') {
							break;
						}

						if ((float)moneyToWithdraw <= CashMachine->getAvailableMoney()) {
							//cout << "Wyplata : " << moneyToWithdraw << " z mozliwych: " << CashMachine->getAvailableMoney();
							char c3 = '1';
							/*
							//Option for confirmation printing after withdraw
							do{
							cout << endl << "Czy chcesz wydrukowac potwierdzenie wyplaty?" << endl;
							cout << "1 - Tak" << endl << "2 - Nie" << endl;
							cin >> c3;
							} while(!(c3 == '1' || c3 == '2'));
							*/

							bool howItWent;
							if (c3 == '1') {
								howItWent = CashMachine->makeWithdraw((float)moneyToWithdraw, true);
							}
							else {
								howItWent = CashMachine->makeWithdraw((float)moneyToWithdraw, false);
							}

							if (howItWent) {
								cout << endl << "--------------------------------------------" << endl;
								cout << langs->at(chosenLang)["withdrawInformation1"];
								cout << moneyToWithdraw << langs->at(chosenLang)["withdrawInformation2"] << endl;
								cout << "--------------------------------------------" << endl << endl;
							}

							cout << endl << "---------------------- Accounts Stats ----------------------" << endl << endl;
							ClientBank->printAccountsList();
							ClientBank2->printAccountsList();
							cout << endl << "----------------------- End of Stats -----------------------" << endl << endl;

						}
						else {
							cout << langs->at(chosenLang)["notEnoughMoneyOnAccount"] << endl;
							continue;
						}

					}
				} while (x < 1 || x > possibleLangs->size());


				cout << endl << endl << langs->at(chosenLang)["pressESCtoRejectCard"] << endl;
				c1 = _getch();
			}

			c1 = 55;
		}
		else {
			cout << langs->at(chosenLang)["putYourCardIntoATM"] << endl;
		}

		cout << endl << endl << langs->at(chosenLang)["pressESCtoExitATM"] << endl;
		c1 = _getch();
	} while (c1 != ESCAPE);


	return 0;
}

