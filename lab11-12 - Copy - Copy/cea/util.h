#pragma once
#include<string>
#include"domain.h"
#include<exception>
using namespace std;

int validatePhoto(const std::string& photo);
int hasDigits(const std::string& word);
void validatePet(const Pet& p);



class Exception : public exception
{
protected:
	string message;
	//string type;
public:
	Exception(const string& mess) : message{ mess } {};
	const char* what() const noexcept override;
	//const string getType() const;
};

