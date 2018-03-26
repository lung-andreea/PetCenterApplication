#pragma once
#include"util.h"
#include<string>
#include<vector>
#include<fstream>
#include"domain.h"
using namespace std;

class Repository
{
protected:
	vector<Pet> pets;
	int current;

public:
	Repository() : current(0) {};
	//Repository(const Repository& repo);
	Repository(vector<Pet> v) : pets(v), current(0) {};
	virtual ~Repository() {};
	void addPet(Pet p);
	void deletePet(const Pet& p);
	void updatePet(const Pet& p, int newAge, const std::string& newPhoto);
	Pet& findByName(const std::string& name);
	vector<Pet> getPets() const { return pets; }

	void next();
	void prev();
	Pet& getCurrent();

	vector<Pet> getAllBreedYoungerThanRepo(const std::string& breed, int age);
	vector<Pet> getAllSortedByAge();
};


class FileRepo :public Repository
{
private:
	string filename;
public:
	FileRepo(const string& filename) : filename{ filename } {};
	~FileRepo() {};
	void readFromFile();
	void writeToFile(vector<Pet> pets);
};
