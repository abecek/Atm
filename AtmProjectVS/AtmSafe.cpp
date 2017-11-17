#include "stdafx.h"
#include "AtmSafe.h"

AtmSafe::AtmSafe()
{
	//ctor
}

AtmSafe::AtmSafe(std::map<unsigned int, unsigned int> safeContent, std::string currency)
{
	this->currency = currency;
	for (auto it = safeContent.begin(); it != safeContent.end(); it++) {
		this->content[it->first] = it->second;
	}

	this->countContent();
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
	if (this->moneyAmount < amount) return false;
	if (amount == 0) return false;
	//if (amount % this->content[0] != 0) return false;

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

unsigned int AtmSafe::getNominalCount(unsigned int amount) {
	return 0;
}

unsigned int AtmSafe::getRowPos(unsigned int x)
{
	for (int i = 1; i < temporary->size(); i++) {
		if (temporary->at(i).at(0) == x) {
			return i;
		}
	}
	return 0;
}

unsigned int AtmSafe::getColPos(unsigned int x)
{
	for (int i = 1; i < temporary->size(); i++) {
		if (temporary->at(0).at(i) == x) {
			return i;
		}
	}
	return 0;
}

unsigned int AtmSafe::getRest(unsigned int amount, unsigned int posX, unsigned int posY)
{
	unsigned int multipiler = temporary->at(posX).at(posY);
	return (amount - (temporary->at(posX).at(0) * multipiler));
}

bool AtmSafe::getMoneyFromSafe2(const unsigned int amount)
{
	if (amount % 10 != 0) return false;
	unsigned int colsAmount = (amount / 10);
	unsigned int size = 0;
	for (auto const& temp : this->content) {
		if (amount >= temp.first) {
			size++;
		}
	}
	this->temporary = new std::vector<std::vector<int>>(size + 1, std::vector<int>(colsAmount + 1));

	int k = 1;
	for (auto const& temp : this->content) {
		if(amount >= temp.first) {
			temporary->at(k)[0] = temp.first;
			k++;
		}
	}

	int val = 10;
	for (int j = 1; j < temporary->at(0).size(); j++) {
		temporary->at(0)[j] = val;
		val += 10;
	}

	for (int i = 1; i < temporary->size(); i++) {
		for (int j = 1; j < temporary->at(0).size(); j++) {
			int colLabel = temporary->at(0).at(j);
			int rowLabeL = temporary->at(i).at(0);
			int div = (int)floor(colLabel/rowLabeL);
			temporary->at(i)[j] = div;
		}
	}

	this->printAnyVector(temporary);
	
	unsigned int counter = 0;
	unsigned int rest = 0;
	
	int multipiler = 0;
	do {
		int rowNr = temporary->size() - 1;
		int colNr = temporary->at(0).size() - 1;
		std::map<unsigned int, std::map<unsigned int, unsigned int>> temp;
		std::vector<int, int> tempVec;
		int rowNext = 0;
		int colNext = 0;
		


		unsigned int tempAmount = amount;
		rest = amount;
		
		for (int i = rowNr; i > 0; i--) {
			for (int j = colNr; j > 0; j--) {
				multipiler = temporary->at(i)[j];
				if (multipiler != 0) {
					rowNext = temporary->at(i)[0];
					colNext = temporary->at(0)[j];

					rest -= this->getRest(amount, i, j);
				}
			}
		}
		counter++;
	} while (rest != 0);

	std::cout << "Counter: " << counter << std::endl;
	

	
	

	return true;
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
	bool flag = true;
	if (withdrawArray) {
		for (auto it = withdrawArray->begin(); it != withdrawArray->end(); it++) {
			if (this->content.at(it->first) >= it->second) {
				this->content.at(it->first) -= it->second;
			}
			else {
				flag = false;
				break;
			}
		}
	}
	else {
		flag = false;
	}
	
	this->possibleWithdrawArray.clear();

	return flag;
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

void AtmSafe::printAnyVector(std::vector<std::vector<int>>* vec)
{
	std::cout << "Array height: " << vec->size() << ", width: " << vec->at(0).size() << std::endl;
	for (int i = 0; i < vec->size(); i++) {
		std::cout << std::endl;
		if (i == 0) std::cout << "  ";
		if (i == 1 || i == 2) std::cout << " ";
		for (int j = 0; j < vec->at(i).size(); j++) {
			std::cout << vec->at(i)[j] << " "; 
			if (i != 0) std::cout << " ";
			if (j >= 9 && i != 0) std::cout << " ";
		}
	}
	std::cout << std::endl;

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
