#include "Controller.h"
#include"util.h"

//Add new pet to the repository of pets

void Controller::addToRepo(const std::string & breed, const std::string & name, int age, const std::string & photo)
{
	Pet p = Pet(breed, name, age, photo);

	try
	{
		validatePet(p);
	}
	catch (Exception& ex)
	{
		string error;
		error += "Invalid pet! The following errors occurred:\n";
		error += ex.what();
		throw Exception{ error };
	}
	this->repo.addPet(p);

	this->undoActions.push_back(make_unique<UndoRedoAdd>(this->repo, p));
}

//Delete the pet with the given name from the repository 
void Controller::deleteFromRepo(const std::string & name)
{
	if (hasDigits(name))
		throw Exception{ "Invalid name!\n" };
	try
	{
		Pet p = this->repo.findByName(name);
		this->undoActions.push_back(make_unique<UndoRedoDelete>(this->repo, p));
		this->repo.deletePet(p);
		
		
	}
	catch (Exception& e)
	{
		throw Exception{ e.what() };
	}
}

//Update the fields age and photo of the pet with the given name
void Controller::updateInRepo(const std::string & name, int newAge, const std::string& newPhoto)
{
	string errors;
	if (hasDigits(name))
		errors += "Name should not contain digits!\n";
	if (!validatePhoto(newPhoto))
		errors += "Photo link should contain http(s)://\n";
	if (errors.size() > 0)
	{
		string err;
		err += "Pet could no be updated! The following errors occured:\n";
		err += errors;
		throw Exception{ err };
	}
	try
	{
		Pet p = this->repo.findByName(name);
		this->repo.updatePet(p, newAge, newPhoto);
		this->undoActions.push_back(make_unique<UndoRedoUpdate>(this->repo,p, newAge, newPhoto));
	}
	catch(Exception& e)
	{
		throw Exception{ e.what() };
	}
}

void Controller::undo()
{
	if (undoActions.empty())
		throw Exception{ "No more operations to undo!" };
	undoActions.back()->executeUndo();
	this->redoActions.push_back(move(undoActions.back()));
	undoActions.pop_back();
}

void Controller::redo()
{
	if (this->redoActions.empty())
		throw Exception{ "No more operations to redo!" };
	this->redoActions.back()->executeRedo();
	this->undoActions.push_back(move(this->redoActions.back()));
	redoActions.pop_back();
}

//Adds a pet to the adoption list
void Controller::addToAdoptionList(const Pet & p)
{
	(*this->adoptionList).addToList(p);
	this->adoptionList->storeAdoptionList();
}

//Deletes the pet with the given name from the adoption list
void Controller::deleteFromAdoptionList(const std::string & name)
{
	(*this->adoptionList).deleteFromList(name);
	this->adoptionList->storeAdoptionList();
}

//Returns a dynamic vector type containing all the pets of the given breed having and age less than the given value
vector<Pet> Controller::getAllBreedYoungerThan(const std::string& breed, int age)
{
	return this->repo.getAllBreedYoungerThanRepo(breed, age);
}

//Returns a dynamic vector type containing all the pets in the repsository sorted ascending by age
vector<Pet> Controller::getAllSorted()
{
	return this->repo.getAllSortedByAge();
}
