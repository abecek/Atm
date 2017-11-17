#include "stdafx.h"
#include "CppUnitTest.h"

#include "Atm.h"
#include "ToString.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AtmProjectNativeTests
{		
	TEST_CLASS(EntitiesTests)
	{
	
	public:

		TEST_METHOD(AddressPostCodeTestJustForTest)
		{
			//Address* a1 = new Address("Poland", "Lodz", "Piotrkowska", "85");
			std::string country = "Poland";
			std::string city = "Lodz";
			std::string street = "Piotrkowska";
			std::string number = "85";
			std::string pc = "90-423";
			Address a1(country, city, street, number);
			a1.setPostCode(pc);

			Assert::AreEqual(pc, a1.getPostCodeAsString(), L"PostCode in address is not correct.");
		}


	};

	TEST_CLASS(MoneyWithdrawTests) 
	{
		public:
			TEST_METHOD(InitAtmSafeTest)
			{
				std::map<unsigned int, unsigned int> safeContent = {
					{ 20, 10 },
					{ 50, 10 },
					{ 100, 10 },
					{ 200, 10 },
					{ 500, 10 },
				};

				unsigned int amount = 0;
				for (auto it = safeContent.begin(); it != safeContent.end(); it++) {
					amount += it->first*it->second;
				}

				AtmSafe* safe = new AtmSafe(safeContent);
				std::string currency = "PLN";

				Assert::AreEqual(amount, safe->getMoneyAmount(), L"Money amount inside is not correct.");
				Assert::AreEqual(currency, safe->getCurrency(), L"Currency is wrong.");
			}

			TEST_METHOD(AddContentToAtmSafeTest)
			{
				std::map<unsigned int, unsigned int> safeContent = {
					{ 20, 10 },
					{ 50, 10 },
					{ 100, 10 },
					{ 200, 10 },
					{ 500, 10 },
				};

				AtmSafe* safe = new AtmSafe(safeContent);
				unsigned int oldAmount = safe->getMoneyAmount();
				

				std::map<unsigned int, unsigned int> safeContentToAdd = {
					{ 20, 5 },
					{ 50, 5 },
					{ 100, 5 },
					{ 200, 5 },
					{ 500, 5 },
				};

				unsigned int valueToAdd = 0;
				for (auto it = safeContentToAdd.begin(); it != safeContentToAdd.end(); it++) {
					valueToAdd += it->first*it->second;
				}


				safe->addContent(&safeContentToAdd);
				Assert::AreEqual((oldAmount + valueToAdd), safe->getMoneyAmount(), L"Money amount inside is not correct after adding.");
			}

			TEST_METHOD(checkAmountIsPossibleToWithdrawTest)
			{
				std::map<unsigned int, unsigned int> safeContent = {
					{ 20, 10 },
					{ 50, 10 },
					{ 100, 10 },
					{ 200, 10 },
					{ 500, 10 },
				};
				AtmSafe* safe = new AtmSafe(safeContent);
				unsigned int inSafeAmount = safe->getMoneyAmount();

				unsigned int possibleValue = (inSafeAmount - 500);
				Assert::IsTrue(safe->checkAmountIsPossibleToWithdraw(possibleValue), L"This value should be possible to withdraw.", LINE_INFO());

				unsigned int impossibleValue = (inSafeAmount + 500);
				Assert::IsFalse(safe->checkAmountIsPossibleToWithdraw(impossibleValue), L"This value should not be possible to withdraw.", LINE_INFO());

				impossibleValue = 0;
				Assert::IsFalse(safe->checkAmountIsPossibleToWithdraw(impossibleValue), L"Division by 0 is not allowed.", LINE_INFO());
				// todo: add more possiblities to the AtmSafe::checkAmountIsPossibleToWithdraw(unsigned int amount) and next tests here...
			}

			TEST_METHOD(getMoneyFromSafeTests)
			{
				/*
				std::map<unsigned int, unsigned int> safeContent = {
					{ 20, 10 },
					{ 50, 10 },
					{ 100, 10 },
					{ 200, 10 },
					{ 500, 10 },
				};
				AtmSafe* safe = new AtmSafe(safeContent);


				std::vector<unsigned int> moneyValues = {
					20,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,
					240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420
				};

				for (auto const& value : moneyValues) {
					std::wstring strVal = std::to_wstring(value);
					std::wstring str = L"Value: " + strVal;
					str += L" should be possible to withdraw.";
					Assert::IsTrue(safe->getMoneyFromSafe(value), str.c_str(), LINE_INFO());
				}
				*/

			}

			TEST_METHOD(areWithdrawsPossibleTest)
			{
				std::map<unsigned int, unsigned int> safeContent = {
					{ 20, 5 },
					{ 50, 1 },
					{ 100, 9 },
					{ 200, 9 },
					{ 500, 3 },
				};
				AtmSafe *safe = new AtmSafe(safeContent);


				std::map<unsigned int, unsigned int> contentToWithdraw1 = {
					{ 20, 0 },
					{ 50,  1},
					{ 100, 9 },
					{ 200, 8 },
					{ 500, 0 },
				};
				Assert::IsTrue(safe->checkIsWithdrawPossible(contentToWithdraw1), L"This withdraw should be possible.", LINE_INFO());


				std::map<unsigned int, unsigned int> contentToWithdraw2 = {
					{ 20, 0 },
					{ 50,  3 },
					{ 100, 9 },
					{ 200, 8 },
					{ 500, 0 },
				};
				Assert::IsFalse(safe->checkIsWithdrawPossible(contentToWithdraw2), L"This withdraw should be impossible.", LINE_INFO());
			}

			TEST_METHOD(ChooseProperWithdrawTest) 
			{
				std::map<unsigned int, unsigned int> safeContent = {
					{ 20, 10 },
					{ 50, 1 },
					{ 100, 10 },
					{ 200, 10 },
					{ 500, 10 },
				};

				std::map<unsigned int, unsigned int>* contentToWithdraw1 = new  std::map<unsigned int, unsigned int>{
					{ 20, 0 },
					{ 50, 1 },
					{ 100, 2 },
					{ 200, 0 },
					{ 500, 0 },
				};

				std::map<unsigned int, unsigned int>* contentToWithdraw2 = new  std::map<unsigned int, unsigned int>{
					{ 20, 0 },
					{ 50, 3 },
					{ 100, 1 },
					{ 200, 0 },
					{ 500, 0 },
				};
				AtmSafe* safe = new AtmSafe(safeContent);
				std::map<unsigned int, unsigned int>* chosenOne = safe->chooseProperWithdraw();
				Assert::IsNull(chosenOne, L"Something wrong.", LINE_INFO());


				safe->addPossibleWithdraw(3, *contentToWithdraw1);
				safe->addPossibleWithdraw(4, *contentToWithdraw2);
				chosenOne = safe->chooseProperWithdraw();
				Assert::IsNotNull(chosenOne, L"There is no proper withdraw that could be realized.", LINE_INFO());

				
				if (contentToWithdraw1->size() != chosenOne->size()) {
					Assert::Fail(L"Maps strings are not the same. Sizes are not equal.", LINE_INFO());
				}
				else {
					std::map<unsigned int, unsigned int>::iterator it2 = contentToWithdraw1->begin();
					for (auto it = chosenOne->begin(); it != chosenOne->end(); it++) {
						if (it->first != it2->first || it->second != it2->second) {
							Assert::Fail(L"Maps strings are not the same.", LINE_INFO());
							break;
						}
						it2++;
					}
				}
			}

			TEST_METHOD(proceedWithdrawTest)
			{
				std::map<unsigned int, unsigned int> safeContent = {
					{ 20, 10 },
					{ 50, 10 },
					{ 100, 10 },
					{ 200, 1 },
					{ 500, 10 },
				};
				AtmSafe safe(safeContent);

				std::map<unsigned int, unsigned int> contentToWithdraw1 = {
					{ 20, 0 },
					{ 50, 1 },
					{ 100, 2 },
					{ 200, 0 },
					{ 500, 0 },
				};
				Assert::IsTrue(safe.proceedWithdraw(&contentToWithdraw1), L"Proceed went wrong.", LINE_INFO());

				safe.addContent(&safeContent);
				std::map<unsigned int, unsigned int> contentToWithdraw2 = {
					{ 20, 0 },
					{ 50, 1 },
					{ 100, 2 },
					{ 200, 100 },
					{ 500, 0 },
				};
				Assert::IsFalse(safe.proceedWithdraw(&contentToWithdraw2), L"Proceed went wrong. Fuse did not work.", LINE_INFO());


				std::map<unsigned int, unsigned int>* testNullptr = nullptr;
				Assert::IsFalse(safe.proceedWithdraw(testNullptr), L"Proceed went wrong for nullptr", LINE_INFO());
			}


	};

}