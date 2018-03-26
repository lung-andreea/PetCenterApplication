#pragma once
#include"domain.h"
#include"repository.h"

class UndoRedoAction
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~UndoRedoAction() {};
};

class UndoRedoAdd : public UndoRedoAction
{
private:
	Repository& repo;
	Pet addedPet;
public:
	UndoRedoAdd(Repository& repo, const Pet& p) :repo{ repo }, addedPet{ p } {};
	void executeUndo() override { repo.deletePet(addedPet); }
	void executeRedo() override { repo.addPet(addedPet); }
};

class UndoRedoDelete : public UndoRedoAction
{
private:
	Repository& repo;
	Pet deletedPet;
public:
	UndoRedoDelete(Repository& repo, const Pet p) :repo{ repo }, deletedPet{ p } {};
	void executeUndo() override { repo.addPet(deletedPet); };
	void executeRedo() override { repo.deletePet(deletedPet); };
};

class UndoRedoUpdate : public UndoRedoAction
{
private:
	Repository& repo;
	Pet updatedPet;
	int newAge;
	string newPhoto;
public:
	UndoRedoUpdate(Repository& repo, const Pet& p, int newAge, const string& newPhoto) : repo{ repo }, updatedPet{ p }, newAge{ newAge }, newPhoto{ newPhoto } {};
	void executeUndo() override { repo.updatePet(updatedPet, updatedPet.getAge(), updatedPet.getPhoto()); };
	void executeRedo() override { repo.updatePet(updatedPet, newAge, newPhoto); };
};