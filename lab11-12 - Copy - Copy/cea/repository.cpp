#include "repository.h"
#include"util.h"
#include<assert.h>
#include<vector>
#include<algorithm>
#include<numeric>
#include<fstream>


//Repository::Repository(const Repository & repo)
//{
//	this->pets = repo.getPets();
//	this->current = repo.current;
//}

//Add new pet to the repository of pets
//Returns: 1 - if successful
//		   0 - otherwise
void Repository::addPet(Pet p)
{
	if (find_if(this->pets.begin(), this->pets.end(), [p](Pet& el) {return el == p; }) != this->pets.end())
		throw Exception{ "The pet already exists!\n" };
	this->pets.push_back(p);
}

//Delete the pet with the given name from the repository 
//Returns: 1 - if successful
//		   0 - otherwise
void Repository::deletePet(const Pet& p)
{
	auto pos = find(this->pets.begin(), this->pets.end(), p);
	this->pets.erase(pos);
}

//Update the fields age and photo of the pet with the given name
//Returns: 1 - if successful
//		   0 - otherwise
void Repository::updatePet(const Pet& p, int newAge, const std::string& newPhoto)
{
	auto pos = find_if(this->pets.begin(), this->pets.end(), [p](Pet& el) {return el.getName() == p.getName(); });
	(*pos).setAge(newAge);
	(*pos).setPhoto(newPhoto);
}

Pet & Repository::findByName(const std::string & name)
{
	auto pos = find_if(this->pets.begin(), this->pets.end(), [name](Pet& el) {return el.getName() == name; });
	if (pos == this->pets.end())
		throw Exception{ "Pet doesn't exist!\n" };
	return *pos;
}

//Moves the counter which tells us the current pet in the repository
void Repository::next()
{
	if (this->current == this->pets.size() - 1)
	{
		this->current = 0;
		return;
	}
	this->current++;
}

void Repository::prev()
{
	if (this->current == 0)
	{
		this->current = this->pets.size()-1;
		return;
	}
	this->current--;
}

//Returns current pet in the repository (the one we will see next if the user chooses to view photo)
Pet& Repository::getCurrent()
{
	return this->pets[this->current];
}

////Returns a dynamic vector type containing all the pets of the given breed having and age less than the given value
vector<Pet> Repository::getAllBreedYoungerThanRepo(const std::string& breed, int age)
{
	vector<Pet> v(this->pets.size());
	auto it = copy_if(this->pets.begin(), this->pets.end(), v.begin(), [breed, age](Pet p) {return p.getBreed() == breed && p.getAge() < age; });
	v.resize(distance(v.begin(), it));
	return v;
}

//Returns a dynamic vector type containing all the pets in the repsository sorted ascending by age
vector<Pet> Repository::getAllSortedByAge()
{
	vector<Pet> v(this->pets.size());
	copy(this->pets.begin(), this->pets.end(), v.begin());
	sort(v.begin(), v.end(), [](const Pet& p1, const Pet& p2) {return p1.getAge() < p2.getAge(); });
	return v;
}

void FileRepo::readFromFile()
{
	Pet p;
	ifstream f(this->filename);
	while (f >> p)
	{
		try
		{
			validatePet(p);
		}
		catch (Exception& v)
		{
			string error;
			error += "Reading from file was unsuccessful. The following errors occured:\n";
			error += v.what();
			throw Exception{ error };
		}
		addPet(p);
	}
	f.close();
}

void FileRepo::writeToFile(vector<Pet> pets)
{
	ofstream f{ this->filename };
	for (Pet p : pets)
		f << p;
	f.close();
}
