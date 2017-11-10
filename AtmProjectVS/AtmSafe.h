#pragma once

class AtmSafe
{
public:
	AtmSafe();
	AtmSafe(std::map<unsigned int, unsigned int> safeContent, std::string currency = "PLN");

	unsigned int getMoneyAmount();
	std::string getCurrency();
	void addContent(std::map<unsigned int, unsigned int> *content);
	int countContent();
	//Unused function
	//float getMedian();

	bool checkAmountIsPossibleToWithdraw(unsigned int amount);
	//Unused function
	//bool getMoneyFromSafe(std::map<unsigned int,unsigned int> money);
	bool getMoneyFromSafe(const unsigned int amount);
	bool checkIsWithdrawPossible(std::map<unsigned int, unsigned int> &temp);
	void addPossibleWithdraw(unsigned int papersCount, std::map<unsigned int, unsigned int> &temp);
	std::map<unsigned int, unsigned int>* chooseProperWithdraw();
	bool proceedWithdraw(std::map<unsigned int, unsigned int> *withdrawArray);

	void printSafe();
	void printAnyContent(std::map<unsigned int, unsigned int> &temp);
	void printAnyContent2();

	virtual ~AtmSafe();
protected:

private:
	std::pair <unsigned int, unsigned int>* getPairWithMaxValue(std::map<unsigned int, unsigned int> &values);
	std::string currency = "PLN";
	unsigned int moneyAmount = 0;

	float median = 0;
	std::map<unsigned int, unsigned int> content = {
		{ 20, 0 },
		{ 50, 0 },
		{ 100, 0 },
		{ 200, 0 },
		{ 500, 0 },
	};

	std::vector<std::map<unsigned int, unsigned int>> possibleWithdrawArray;

};

