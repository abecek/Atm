#pragma once

struct PostCode {
	std::string firstPart;
	std::string secondPart;

	void setPostCodeFromString(std::string input) {
		for (unsigned int i = 0; i < input.length(); i++) {
			if (i <= 1) {
				firstPart += input[i];
			}
			else if (i >= 3) {
				secondPart += input[i];
			}
		}
	}

	std::string getPostCodeAsString() {
		return firstPart + "-" + secondPart;
	};

};

class Address
{
public:
	Address();
	Address(std::string country, std::string city, std::string street, std::string number, PostCode *pc = nullptr);
	void setPostCode(std::string content);
	std::string toString();
	virtual ~Address();
protected:
private:
	std::string country;
	std::string city;
	PostCode *postCode;
	std::string street;
	std::string number;

};