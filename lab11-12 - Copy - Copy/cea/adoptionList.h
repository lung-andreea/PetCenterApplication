#pragma once
#include"domain.h"
#include<vector>
using namespace std;

class AdoptionList
{
protected:
	vector<Pet> adoptedPets;
public:
	AdoptionList() {};
	virtual ~AdoptionList() {};

	void addToList(const Pet& p);
	void deleteFromList(const std::string& name);

	vector<Pet> getAdoptedList() const { return adoptedPets; }

	virtual void storeAdoptionList() = 0;
	virtual void viewAdoptionList() = 0;
};

class CSVAdoptionList : public AdoptionList
{
private:
	string CSVfile;
public:
	CSVAdoptionList(string filename) : CSVfile{ filename } {};
	~CSVAdoptionList() {};

	void storeAdoptionList() override;
	void viewAdoptionList() override;
};

class HTMLAdoptionList : public AdoptionList
{
private:
	string HTMLfile;
public:
	HTMLAdoptionList(string filename) : HTMLfile{ filename } {};
	~HTMLAdoptionList() {};

	void storeAdoptionList() override;
	void viewAdoptionList() override;
};
