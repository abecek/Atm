#include "stdafx.h"
#include "CppUnitTest.h"

#include "Atm.h"
#include "ToString.h"

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
				unsigned int inSafe = safe->getMoneyAmount();

				unsigned int possibleValue = (inSafe - 500);
				Assert::IsTrue(safe->checkAmountIsPossibleToWithdraw(possibleValue), L"This value should be possible to withdraw.", LINE_INFO());

				unsigned int impossibleValue = (inSafe + 500);
				Assert::IsFalse(safe->checkAmountIsPossibleToWithdraw(impossibleValue), L"This value should not be possible to withdraw.", LINE_INFO());

				impossibleValue = 0;
				Assert::IsFalse(safe->checkAmountIsPossibleToWithdraw(impossibleValue), L"Division by 0 is not allowed.", LINE_INFO());
				// todo: add more possiblities to the AtmSafe::checkAmountIsPossibleToWithdraw(unsigned int amount) and next tests here...
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