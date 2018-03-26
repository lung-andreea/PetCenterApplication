#include "domain.h"
#include<iostream>
#include<string>
#include<Windows.h>

size_t Pet::count = 0;
size_t Pet::all = 0;
//Default constructor
Pet::Pet()
{
	this->breed = "";
	this->name = "";
	this->age = 0;
	this->photo = "";
	count++;
	all++;
}

//Constructor with parameters
Pet::Pet(const std::string& breed, const std::string& name, int age, const std::string& photo)
{
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photo = photo;
	count++;
	all++;
}

Pet::Pet(const Pet & pet)
{
	this->breed = pet.breed;
	this->name = pet.name;
	this->age = pet.age;
	this->photo = pet.photo;
	count++;
	all++;
}

Pet & Pet::operator=(const Pet & pet)
{
	if (this == &pet)
		return *this;
	this->breed = pet.breed;
	this->name = pet.name;
	this->age = pet.age;
	this->photo = pet.photo;
	//count++;
	//all++;
	return *this;
}

bool Pet::operator==(const Pet & pet)
{
	// TODO: insert return statement here
	if (this->name == pet.name&&this->age == pet.age&&this->breed == pet.breed&&this->photo == pet.photo)
		return true;
	return false;
}

//Opens associated link
void Pet::openPhoto()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getPhoto().c_str(), NULL, SW_SHOWMAXIMIZED);
}

size_t Pet::getExistentInstances()
{
	return count;
}

size_t Pet::getAllInstances()
{
	return all;
}

ostream& operator<<(ostream& os, const Pet& pet)
{
	os << pet.getBreed() << "," << pet.getName() << "," << pet.getAge() << "," << pet.getPhoto() << "\n";
	return os;
}

istream& operator >> (istream& is, Pet& pet)
{
	string str;
	is >> str;
	char* ch = new char[str.length() + 1];
	strcpy(ch, str.c_str());
	char* p;
	p = strtok(ch, ",");
	if (p == NULL)
		return is;
	pet.setBreed(p);
	p = strtok(NULL, ",");
	pet.setName(p);
	p = strtok(NULL, ",");
	int age;
	age = atoi(p);
	pet.setAge(age);
	p = strtok(NULL, ",");
	pet.setPhoto(p);
	delete[] ch;
	return is;

}
