#include "util.h"
#include<iostream>
#include<string>

//Validation functions

int validatePhoto(const std::string & photo)
{
	std::size_t pos1 = photo.find("http");
	std::size_t pos2 = photo.find("://");
	if (pos1 == std::string::npos)
		return 0;
	if (pos2 == std::string::npos)
		return 0;
	return 1;
}

int hasDigits(const std::string & word)
{
	for (int i = 0; i < word.length(); i++)
		if (isdigit(word[i]))
			return 1;
	return 0;
}

void validatePet(const Pet & p)
{
	string errors;
	if (!validatePhoto(p.getPhoto()))
		errors += "Photo should contain http(s)://!\n";
	if (hasDigits(p.getBreed()))
		errors += "Breed cannot contain digits!\n";
	if (hasDigits(p.getName()))
		errors += "Name cannot contain digits!\n";

	if (errors.size() > 0)
		throw Exception{ errors };
}

const char* Exception::what() const noexcept
{
	return message.c_str();
}

//const string Exception::getType() const
//{
//	return type;
//}
