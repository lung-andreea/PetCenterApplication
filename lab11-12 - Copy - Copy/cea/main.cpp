#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	/*QWidget* choiceWidget = new QWidget{};
	QVBoxLayout* layout = new QVBoxLayout{};
	QLabel* choose = new QLabel{ "Choose the type of file:" };
	QRadioButton* csv = new QRadioButton{ "CSV file" };
	QRadioButton* html = new QRadioButton{ "HTML file" };
	QPushButton* pick = new QPushButton{ "OK" };
	layout->addWidget(choose);
	layout->addWidget(csv);
	layout->addWidget(html);
	layout->addWidget(pick);
	choiceWidget->setLayout(layout);
	choiceWidget->show();

	
	if()
	
	if (csv->isChecked())
		adoptionList = new CSVAdoptionList{ "CSV.csv" };
	else
		adoptionList = new HTMLAdoptionList{ "HTML.html" };
*/
	AdoptionList* adoptionList;
	FileRepo repo{ "file.txt" };
	repo.readFromFile();
	Controller ctrl{ repo, adoptionList };
	GUI gui{ctrl};
	//repo.writeToFile(ctrl.getRepo().getPets());
	return a.exec();
	delete adoptionList;
}
