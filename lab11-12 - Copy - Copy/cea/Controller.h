#pragma once
#include"repository.h"
#include"adoptionList.h"
#include"UndoRedoAction.h"
#include<memory>

class Controller
{
private:
	Repository repo;
	AdoptionList* adoptionList;
	vector<unique_ptr<UndoRedoAction>> undoActions;
	vector<unique_ptr<UndoRedoAction>> redoActions;

public:
	Controller() {};
	Controller(const Repository& repo, AdoptionList* a) : repo(repo), adoptionList(a) {};
	Controller(const Controller& ctrl) = delete;		// controller cannot be copied now, because it contains unique_ptr
	void operator=(const Controller& ctrl) = delete;	// same for assignment

	Repository& getRepo() { return repo; };
	AdoptionList* getAdoptionList() const { return adoptionList; };
	void setAdoptionList(AdoptionList* adopt) { adoptionList = adopt; };

	void addToRepo(const std::string& breed, const std::string& name, int age, const std::string& photo);
	void deleteFromRepo(const std::string& name);
	void updateInRepo(const std::string & name, int newAge, const std::string& newPhoto);
	void undo();
	void redo();

	vector<Pet> getAllBreedYoungerThan(const std::string& breed, int age);
	vector<Pet> getAllSorted();

	void addToAdoptionList(const Pet& p);
	void deleteFromAdoptionList(const std::string& name);
};