#include "adoptionList.h"
#include"util.h"
#include<algorithm>
#include<fstream>
#include<Windows.h>

//Adds pet to the dynamic vector in the adoption list
void AdoptionList::addToList(const Pet & p)
{
	string name = p.getName();
	if (find_if(this->adoptedPets.begin(), this->adoptedPets.end(), [name](Pet el) {return el.getName() == name; }) != this->adoptedPets.end())
		throw Exception{ "Pet is already in the adoption list!\n" };
	this->adoptedPets.push_back(p);
}

//Removes the pet with the given name from the adoption list
void AdoptionList::deleteFromList(const std::string & name)
{
	auto pos = find_if(this->adoptedPets.begin(), this->adoptedPets.end(), [name](Pet el) {return el.getName() == name; });
	if (pos != this->adoptedPets.end())
		this->adoptedPets.erase(pos);
}



void CSVAdoptionList::storeAdoptionList()
{
	ofstream f{ this->CSVfile };
	for (Pet p : this->adoptedPets)
		f << p;
	f.close();
}

void CSVAdoptionList::viewAdoptionList()
{
	ShellExecuteA(NULL, NULL, "Notepad", this->CSVfile.c_str(), NULL, SW_SHOWMAXIMIZED);
}

void HTMLAdoptionList::storeAdoptionList()
{
	ofstream f{ this->HTMLfile };
	f << "<HTML>\n<HEAD>\n\t<TITLE>Pet shelter</TITLE>\n</HEAD>\n<BODY>\n\t<table border = '1'>\n\t\t<tr>\n\t\t\t<td>Breed</td>\n\t\t\t<td>Name</td>\n\t\t\t<td>Age</td>\n\t\t\t<td>Photo</td>\n\t\t</tr>\n";
	for (Pet p : this->adoptedPets)
	{
		f << "\n\t\t<tr>\n\t\t\t<td>" << p.getBreed().c_str() << "</td>\n\t\t\t<td>" << p.getName().c_str() << "</td>\n\t\t\t<td>" << p.getAge() << "</td>\n";
		f << "\t\t\t<td><a href =" << p.getPhoto().c_str() << ">Link</a></td>\n\t\t</tr>\n";
	}
	f << "\t</table>\n</BODY>\n</HTML>";
	f.close();
}

void HTMLAdoptionList::viewAdoptionList() 
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->HTMLfile.c_str(), NULL, SW_SHOWMAXIMIZED);
}

