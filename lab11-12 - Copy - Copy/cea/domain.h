#pragma once
#include<iostream>
using namespace std;

class Pet
{
private:
	std::string breed;
	std::string name;
	int age;
	std::string photo;

public:
	Pet();
	Pet(const std::string& breed, const std::string& name, int age, const std::string& photo);
	Pet(const Pet& pet);
	Pet& operator=(const Pet& pet);
	bool operator==(const Pet& pet);

	~Pet() { --count; };

	std::string getBreed() const { return breed; };
	std::string getName() const { return name; };
	int getAge() const { return age; };
	std::string getPhoto() const { return photo; };
	void setBreed(const string& newBreed) { this->breed = newBreed; }
	void setName(const string& newName) { this->name = newName; }
	void setAge(int newAge) { this->age = newAge; };
	void setPhoto(const string& newPhoto) { this->photo = newPhoto; };

	void openPhoto();
	static size_t getExistentInstances();
	static size_t getAllInstances();

	friend ostream& operator<<(ostream& os, const Pet& pet);
	friend istream& operator >> (istream& is, Pet& pet);
private:
	static size_t count;
	static size_t all;
};

