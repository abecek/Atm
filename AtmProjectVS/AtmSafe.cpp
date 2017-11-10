#include "stdafx.h"
#include "AtmSafe.h"

AtmSafe::AtmSafe()
{
	//ctor
}

AtmSafe::AtmSafe(std::map<unsigned int, unsigned int> safeContent, std::string currency)
{
	this->content = content;
	this->currency = currency;
}

unsigned int AtmSafe::getMoneyAmount()
{
	return this->moneyAmount;
}

std::string AtmSafe::getCurrency()
{
	return this->currency;
}

void AtmSafe::addContent(std::map<unsigned int, unsigned int> *contentToAdd)
{
	auto it = this->content.begin();
	auto it2 = contentToAdd->begin();
	for (; it != this->content.end();) {
		it->second += it2->second;
		it++;
		it2++;
	}

	this->countContent();
}

int AtmSafe::countContent()
{
	unsigned int temp = 0;
	for (std::map<unsigned int, unsigned int>::iterator i = this->content.begin(); i != this->content.end(); i++) {
		temp += (i->second * i->first);
	}
	this->moneyAmount = temp;
	//this->getMedian();
	return this->moneyAmount;
}

/*
float AtmSafe::getMedian()
{
	std::vector<unsigned int> temp;

	auto it = this->content.begin();
	for(;it != this->content.end();) {
	temp.push_back(it->second);
	it++;
	}

	size_t size = temp.size();
	std::sort(temp.begin(), temp.end());

	if (size  % 2 == 0) {
	this->median = (temp[size / 2 - 1] + temp[size / 2]) / 2;
	}
	else {
	this->median = temp[size / 2];
	}

	return this->median;
}
*/

bool AtmSafe::checkAmountIsPossibleToWithdraw(unsigned int amount)
{
	if (amount % this->content[0] != 0) return false;

	return true;
}

/*
bool AtmSafe::getMoneyFromSafe(std::map<unsigned int, unsigned int> money)
{
	
}
*/

bool AtmSafe::getMoneyFromSafe(const unsigned int amount)
{
	std::map<unsigned int, unsigned int> tempArray = {
		{ 20, 0 },
		{ 50, 0 },
		{ 100, 0 },
		{ 200, 0 },
		{ 500, 0 },
	};

	bool isFirstDivision = true;
	for (auto tempIt = this->content.begin(); tempIt != this->content.end(); tempIt++) {

		//The reason for outer loop is omissing each nominal value after first step
		// valToOmiss is current nominal value which will be omissed in inner loops
		unsigned int valToOmiss = tempIt->first;
		auto it = this->content.end();
		
		do {
			it--;
			unsigned int tempAmount = amount;
			std::map<unsigned int, unsigned int> temp;
			unsigned int papersCount = 0;
			auto it2 = it;
			
			do {
				int tempMod = (tempAmount % it2->first);
				int tempDiv = floor(tempAmount / it2->first);
		
				// todo: Have to remake whole algorithm, because it isnt still working for values like 210, 230, 260, 280
				if (it2->first == valToOmiss && !isFirstDivision) {
					std::cout << std::endl << "POMIJAM: " << valToOmiss << "  mod: " << tempMod << std::endl << std::endl;
					if (it2 == this->content.begin()) break;
					it2--;
					//if is for values 160, 180
					if (tempMod == 10 || tempMod == 30) {
						continue;
					}
				}
				
				std::cout << tempDiv << " = " << tempAmount << " / " << it2->first << std::endl;

				// todo: I suppose there is a reason why these amounts above arent working
				// have to add next condition (tempDiv > 1)
				if (tempDiv >= 1) {
					temp[it2->first] = tempDiv;
					papersCount += tempDiv;
					tempAmount -= tempDiv*it2->first;
				}				

				if (it2 == this->content.begin()) break;
				it2--;
			} while (tempAmount > 0);

			//this->printAnyContent(tempArray);
			//this->printAnyContent(temp);

			if (tempAmount == 0) {
				//std::cout << std::endl << "Ilosc banknotow: " << papersCount;
				//this->printAnyContent(temp);
				if (this->checkIsWithdrawPossible(temp)) {
					this->addPossibleWithdraw(papersCount, temp);
				}
			}
			else {
				std::cout << "Reszta: " << tempAmount << std::endl << std::endl;
			}

			//if i remembered well there was some bug when condition was in the loop below in CodeBlocks and i had to use value - true as condition
			//In Virutal Studio loop condition works correctly
			//if (it == tempArray.begin()) break;
		} while (it != this->content.begin());

		//Omission of first loop step
		isFirstDivision = false;

		std::cout << std::endl << "---------------------------------------" << std::endl;
	}

	std::map<unsigned int, unsigned int> *arrayToWithdraw = this->chooseProperWithdraw();
	return this->proceedWithdraw(arrayToWithdraw);
}

bool AtmSafe::checkIsWithdrawPossible(std::map<unsigned int, unsigned int> &temp)
{
	for (auto it = temp.begin(); it != temp.end(); it++) {
		//std::cout << std::endl << this->content.at(it->first) << " - " << it->second << " = " << (int(this->content.at(it->first)) - int(it->second)) << std::endl;
		if ((int(this->content.at(it->first)) - int(it->second)) < 0) {
			return false;
		}
	}
	return true;
}

void AtmSafe::addPossibleWithdraw(unsigned int papersCount, std::map<unsigned int, unsigned int> &temp)
{
	bool isInArray = false;
	if (possibleWithdrawArray.size() > 0) {
		for (const std::map<unsigned int, unsigned int> &withdraw : possibleWithdrawArray) {
			bool isTabContentEqualAtIndex = true;
			auto it2 = temp.begin();
			for (auto it = withdraw.begin(); it != withdraw.end(); it++) {
				if (it->first != it2->first || it->second != it2->second) {
					isTabContentEqualAtIndex = false;
					break;
				}
				it2++;
			}

			if (isTabContentEqualAtIndex) {
				isInArray = true;
				break;
			}
		}
	}

	if (!isInArray) {
		this->possibleWithdrawArray.push_back(temp);
	}
}

std::pair <unsigned int, unsigned int>* AtmSafe::getPairWithMaxValue(std::map<unsigned int, unsigned int> &values)
{
	std::pair <unsigned int, unsigned int> *maxPair = new std::pair<unsigned int, unsigned int>;
	if(!values.empty()) {
		auto it = values.begin();
		maxPair->first = it->first;
		maxPair->second = it->second;

		for (; it != values.end(); it++) {
			if (maxPair->second < it->second) {
				maxPair->first = it->first;
				maxPair->second = it->second;
			}
		}
	}
	else {
		maxPair = nullptr;
	}
	

	return maxPair;
}

std::map<unsigned int, unsigned int>* AtmSafe::chooseProperWithdraw()
{
	std::map<unsigned int, unsigned int> *chosenOne = nullptr;
	std::map<unsigned int, unsigned int> values;
	unsigned index = 0;

	for (const std::map<unsigned int, unsigned int> &withdraw : possibleWithdrawArray) {
		unsigned int currentValue = 0;
		for (auto it = withdraw.begin(); it != withdraw.end(); it++) {
			currentValue += (this->content[it->first] - it->second);
		}
		values[index] = currentValue;
		index++;
	}

	std::pair<unsigned int, unsigned int> *pair = this->getPairWithMaxValue(values);
	//std::cout << pair.first << "  " << pair.second << std::endl;
	chosenOne = nullptr;
	try {
		if (pair) {
			chosenOne = &this->possibleWithdrawArray.at(pair->first);
		}
		else {
			throw std::exception();
		}
	}
	catch (const std::exception &err) {
		std::cout << std::endl << "We are unable to withdraw this value. Sorry." << std::endl << err.what() << std::endl << std::endl;
	}

	//For tests
	/*if (chosenOne) {
		this->printAnyContent(*chosenOne);
	}*/
	
	

	return chosenOne;
}

bool AtmSafe::proceedWithdraw(std::map<unsigned int, unsigned int> *withdrawArray)
{
	if (withdrawArray) {
		for (auto it = withdrawArray->begin(); it != withdrawArray->end(); it++) {
			this->content.at(it->first) -= it->second;
		}
	}
	else {
		return false;
	}
	
	this->possibleWithdrawArray.clear();

	return true;
}

void AtmSafe::printSafe()
{
	std::cout << "Atmsafe - moneyValue: " << this->getMoneyAmount() << std::endl;
	std::cout << "Nominal Value - Count" << std::endl;
	auto it = this->content.begin();
	for (int i = 0; it != this->content.end(); i++) {
		std::cout << it->first << " - " << it->second << std::endl;
		it++;
	}
}

void AtmSafe::printAnyContent(std::map<unsigned int, unsigned int> &temp)
{
	std::cout << std::endl;
	auto it = temp.begin();
	for (; it != temp.end();) {
		std::cout << it->first << " - " << it->second << std::endl;
		it++;
	}
}

void AtmSafe::printAnyContent2()
{
	std::cout << "----------" << std::endl;
	for (const std::map<unsigned int, unsigned int> &withdraw : possibleWithdrawArray) {
		for (auto it = withdraw.begin(); it != withdraw.end(); it++) {
			std::cout << it->first << " - " << it->second << std::endl;
		}
		std::cout << "----------" << std::endl;
	}
}

AtmSafe::~AtmSafe()
{
	//dtor
}
