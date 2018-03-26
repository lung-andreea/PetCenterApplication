#include "GUI.h"

GUI::GUI(Controller& ctrl, QWidget *parent) : ctrl{ctrl}, QWidget { parent }
{
	this->choiceWidget = new QWidget{};
	QVBoxLayout* layout = new QVBoxLayout{};
	QLabel* choose = new QLabel{ "Choose the type of file:" };
	csv = new QRadioButton{ "CSV file" };
	html = new QRadioButton{ "HTML file" };
	pick = new QPushButton{ "OK" };
	layout->addWidget(choose);
	layout->addWidget(csv);
	layout->addWidget(html);
	layout->addWidget(pick);
	choiceWidget->setLayout(layout);
	choiceWidget->show();
	QObject::connect(this->pick, &QPushButton::clicked, this, &GUI::setAdoptionListGUI);
}

GUI::~GUI()
{
}

void GUI::keyPressEvent(QKeyEvent * event)
{
	switch (event->key()) {
	case (Qt::Key_Z):
		if (event->modifiers() == Qt::CTRL)
			undoGUI();
		break;
	case (Qt::Key_Y):
		if (event->modifiers() == Qt::CTRL)
			redoGUI();
		break;
	default:
		event->ignore();
		break;
	}
}

Chart::Chart( Controller& ctrl, QWidget *parent) :ctrl{ ctrl }, QWidget{ parent }
{
	QVBoxLayout* chartLayout = new QVBoxLayout{ this };
	QCustomPlot* customPlot = new QCustomPlot{};
	customPlot->setMinimumSize(700, 500);
	// set dark background gradient:
	QLinearGradient gradient(0, 0, 0, 400);
	gradient.setColorAt(0, QColor(90, 90, 90));
	gradient.setColorAt(0.38, QColor(105, 105, 105));
	gradient.setColorAt(1, QColor(70, 70, 70));
	customPlot->setBackground(QBrush(gradient));

	// create empty bar chart objects:
	QCPBars *fossil= new QCPBars(customPlot->xAxis, customPlot->yAxis);

	fossil->setAntialiased(false);
	fossil->setStackingGap(1);
	// set names and colors:
	fossil->setName("Pet chart");
	fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
	fossil->setBrush(QColor(111, 9, 176));

	// prepare x axis with country labels:
	QVector<QString> labels;
	QVector<double> ticks;
	ticks << 1 << 2 << 3 << 4 << 5 << 6;
	labels << "Labrador" << "Basset" << "Beagle" << "Bichon" << "Husky" << "Pomeranian";
	QVector<double> petData;
	vector<string> breeds{ "Labrador", "Basset", "Beagle", "Bichon", "Husky" ,"Pomeranian" };
	for (auto breed : breeds)
		petData << this->ctrl.getAllBreedYoungerThan(breed, 100).size();
	fossil->setData(ticks, petData);
	QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
	textTicker->addTicks(ticks, labels);
	customPlot->xAxis->setTicker(textTicker);
	customPlot->xAxis->setTickLabelRotation(60);
	customPlot->xAxis->setSubTicks(false);
	customPlot->xAxis->setTickLength(0, 4);
	customPlot->xAxis->setRange(0, 8);
	customPlot->xAxis->setBasePen(QPen(Qt::white));
	customPlot->xAxis->setTickPen(QPen(Qt::white));
	customPlot->xAxis->grid()->setVisible(true);
	customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
	customPlot->xAxis->setTickLabelColor(Qt::white);
	customPlot->xAxis->setLabelColor(Qt::white);

	// prepare y axis:
	customPlot->yAxis->setRange(0, 6);
	customPlot->yAxis->setPadding(5); // a bit more space to the left border
	customPlot->yAxis->setLabel("Breed distribution in \"Adopt a Pet\"\npet shelter (2017)");
	customPlot->yAxis->setBasePen(QPen(Qt::white));
	customPlot->yAxis->setTickPen(QPen(Qt::white));
	customPlot->yAxis->setSubTickPen(QPen(Qt::white));
	customPlot->yAxis->grid()->setSubGridVisible(true);
	customPlot->yAxis->setTickLabelColor(Qt::white);
	customPlot->yAxis->setLabelColor(Qt::white);
	customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
	customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

	// setup legend:
	customPlot->legend->setVisible(true);
	customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignHCenter);
	customPlot->legend->setBrush(QColor(255, 255, 255, 100));
	customPlot->legend->setBorderPen(Qt::NoPen);
	QFont legendFont = font();
	legendFont.setPointSize(10);
	customPlot->legend->setFont(legendFont);
	customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	chartLayout->addWidget(customPlot);
}

void GUI::initGUI()
{
	QHBoxLayout* mainWindow = new QHBoxLayout{this};
	mainWindow->setSizeConstraint(QLayout::SetFixedSize);
	this->menuWidget = new QGroupBox{ "Menu" };
	this->adminWidget = new QGroupBox{ "Administrator" };
	this->userWidget = new QGroupBox{ "User" };

	//Main menu
	QVBoxLayout* menuLayout = new QVBoxLayout{};
	this->adminButton = new QPushButton{ "Admin" };
	this->userButton = new QPushButton{ "User" };
	this->exitButton = new QPushButton{ "Exit" };
	this->chartButton = new QPushButton{ "Chart" };
	menuLayout->addWidget(this->adminButton);
	menuLayout->addWidget(this->userButton);
	menuLayout->addWidget(this->chartButton);
	menuLayout->addWidget(this->exitButton);
	this->menuWidget->setLayout(menuLayout);

	mainWindow->addWidget(this->menuWidget);

	//Administrator
	QHBoxLayout* adminLayout = new QHBoxLayout{};

	QWidget* leftSideAdminWidget = new QWidget{};
	leftSideAdminWidget->setMaximumWidth(300);
	QVBoxLayout* leftSideAdminLayout = new QVBoxLayout{};
	QWidget* infoWidget = new QWidget{};
	QFormLayout* info = new QFormLayout{};
	QLabel* breedLabel = new QLabel{ "&Breed" };
	this->breedField = new QLineEdit{};
	this->breedField->setMinimumWidth(160);
	breedLabel->setBuddy(this->breedField);
	QLabel* nameLabel = new QLabel{ "&Name" };
	this->nameField = new QLineEdit{};
	nameLabel->setBuddy(this->nameField);
	QLabel* ageLabel = new QLabel{ "&Age" };
	this->ageField = new QLineEdit{};
	ageLabel->setBuddy(this->ageField);
	QLabel* photoLabel = new QLabel{ "&Photo link:" };
	this->photoField = new QTextEdit{};
	photoLabel->setBuddy(this->photoField);
	info->addRow(breedLabel, this->breedField);
	info->addRow(nameLabel, this->nameField);
	info->addRow(ageLabel, this->ageField);
	info->addRow(photoLabel, this->photoField);
	infoWidget->setLayout(info);
	QWidget* buttons = new QWidget{};
	QGridLayout* gridLayout = new QGridLayout{};
	addButton = new QPushButton("Add");
	updateButton = new QPushButton("Update");
	deleteButton = new QPushButton("Delete");
	sortButton = new QPushButton("Sort");
	backButtonAdmin = new QPushButton("Back");
	gridLayout->addWidget(addButton, 0, 0);
	gridLayout->addWidget(updateButton, 0, 1);
	gridLayout->addWidget(deleteButton, 0, 2);
	gridLayout->addWidget(sortButton, 1, 0, 1, 3);
	gridLayout->addWidget(backButtonAdmin, 2, 1);
	buttons->setLayout(gridLayout);

	leftSideAdminLayout->addWidget(infoWidget);
	leftSideAdminLayout->addWidget(buttons);
	leftSideAdminWidget->setLayout(leftSideAdminLayout);
	adminLayout->addWidget(leftSideAdminWidget);

	QVBoxLayout* rightSideLayout = new QVBoxLayout{};
	options = new QComboBox{};
	options->addItem("Short");
	options->addItem("Detailed");
	rightSideLayout->addWidget(options);
	petList = new QListWidget{};
	petList->setMinimumWidth(200);
	petList->setSelectionMode(QAbstractItemView::SingleSelection);
	petList->setMinimumWidth(400);
	rightSideLayout->addWidget(petList);
	adminLayout->addLayout(rightSideLayout);
	
	this->adminWidget->setLayout(adminLayout);
	mainWindow->addWidget(this->adminWidget);

	//User 
	//User menu
	//User Widget
	QVBoxLayout* userLayout = new QVBoxLayout{};
	allButton = new QPushButton{"See all pets"};
	specificBreedButton = new QPushButton{"Only a specific breed"};
	specificBreedButton->setMinimumWidth(170);
	QLabel* giveBreedLabel = new QLabel{ "Give breed:" };
	giveBreed = new QLineEdit{};
	giveBreedLabel->setBuddy(giveBreed);
	QLabel* giveAgeLabel = new QLabel{ "Age less than:" };
	giveAge = new QLineEdit{};
	giveAgeLabel->setBuddy(giveAge);
	//giveBreed->setMaximumWidth(100);
	getBreedWidget = new QWidget{};
	QFormLayout* getBreedLayout= new QFormLayout{getBreedWidget};
	getBreedLayout->addRow(giveBreedLabel, giveBreed);
	getBreedLayout->addRow(giveAgeLabel, giveAge);
	userLayout->addWidget(allButton);
	userLayout->addWidget(specificBreedButton);
	userLayout->addWidget(getBreedWidget);
	openAdopList = new QPushButton{ "Open adoption list" };
	userLayout->addWidget(openAdopList);
	backButtonUser = new QPushButton{ "Back" };
	userLayout->addWidget(backButtonUser);
	getBreedWidget->hide();
	userWidget->setLayout(userLayout);
	mainWindow->addWidget(userWidget);
	userWidget->hide();
	
	mainWindow->addWidget(this->userWidget);
	
	//Adoption List
	playlistWidget = new QWidget{};
	QVBoxLayout* playlistLayout = new QVBoxLayout{};
	QGroupBox* petWidget = new QGroupBox{"Current pet"};
	QVBoxLayout* petWidgetLayout = new QVBoxLayout{petWidget};
	QHBoxLayout* buttonsLayout = new QHBoxLayout{};
	Pet pet = this->ctrl.getRepo().getPets()[0];
	currentPet = new QLabel{ QString::fromStdString(pet.getName() + " - " + pet.getBreed() + ", " + std::to_string(pet.getAge()) + " yro, " + pet.getPhoto()) };
	petWidgetLayout->addWidget(currentPet);
	prevButton = new QPushButton{"Prev"};
	adoptButton = new QPushButton{"Adopt"};
	nextButton = new QPushButton{ "Next" };
	buttonsLayout->addWidget(prevButton);
	buttonsLayout->addWidget(adoptButton);
	buttonsLayout->addWidget(nextButton);
	petWidgetLayout->addLayout(buttonsLayout);
	viewPhotoButton = new QPushButton{ "View Photo" };
	petWidgetLayout->addWidget(viewPhotoButton);
	playlistLayout->addWidget(petWidget);
	QLabel* playlistLabel = new QLabel{ "Adoption List" };
	QFont font("Courier", 10, 100, true);
	playlistLabel->setFont(font);
	playlistLayout->addWidget(playlistLabel);
	playlistLayout->setAlignment(playlistLabel, Qt::AlignCenter);
	playlist = new QListWidget{};
	playlist->setSelectionMode(QAbstractItemView::SingleSelection);	
	playlistLayout->addWidget(playlist);
	backButtonPlayList = new QPushButton{ "Back" };
	backButtonPlayList->setMaximumWidth(100);
	playlistLayout->addWidget(backButtonPlayList);
	playlistLayout->setAlignment(backButtonPlayList, Qt::AlignCenter);
	playlistWidget->setLayout(playlistLayout);
	mainWindow->addWidget(playlistWidget);
	playlistWidget->hide();

	showMenuOnly();

}

void GUI::setAdoptionListGUI()
{
	AdoptionList* adoptionList;
	if (csv->isChecked())
		adoptionList = new CSVAdoptionList{ "CSV.csv" };
	else
		adoptionList = new HTMLAdoptionList{ "HTML.htm" };
	this->ctrl.setAdoptionList(adoptionList);
	this->choiceWidget->hide();
	this->initGUI();
	this->connectSignalsAndSlots();
	this->populatePetList();
	this->show();
}

int GUI::getSelectedIndex()
{
	if (this->petList->count() == 0)
		return -1;

	QModelIndexList index = this->petList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		this->nameField->clear();
		this->breedField->clear();
		this->ageField->clear();
		this->photoField->clear();
		return -1;
	}

	int idx = index.at(0).row();
	return idx;
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::showAdminOnly);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::showUserOnly);
	QObject::connect(this->chartButton, &QPushButton::clicked, this, &GUI::showChartOnly);
	QObject::connect(this->exitButton, &QPushButton::clicked, QApplication::instance() , &QApplication::quit);
	QObject::connect(this->backButtonAdmin, &QPushButton::clicked, this, &GUI::showMenuOnly);
	QObject::connect(this->backButtonUser, &QPushButton::clicked, this, &GUI::showMenuOnly);
	QObject::connect(this->backButtonPlayList, &QPushButton::clicked, this, &GUI::backHandler);
	QObject::connect(this->specificBreedButton, &QPushButton::clicked, this->getBreedWidget, &QWidget::show);
	QObject::connect(this->allButton, &QPushButton::clicked, this, &GUI::allButtonHandler);
	QObject::connect(this->petList, &QListWidget::itemSelectionChanged, this, &GUI::listItemChanged);
	QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addPetUI);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deletePetUI);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updatePetUI);
	QObject::connect(this->options, &QComboBox::currentTextChanged, this, &GUI::populatePetList);
	QObject::connect(this->sortButton, &QPushButton::clicked, this, &GUI::sortHandler);
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &GUI::next);
	QObject::connect(this->prevButton, &QPushButton::clicked, this, &GUI::prev);
	QObject::connect(this->adoptButton, &QPushButton::clicked, this, &GUI::adopt);
	QObject::connect(this->viewPhotoButton, &QPushButton::clicked, this, &GUI::openPhoto);
	QObject::connect(this->giveAge, &QLineEdit::returnPressed, this, &GUI::initForSpecificBreed);
	QObject::connect(this->openAdopList, &QPushButton::clicked, this, &GUI::openAdoptionList);
}

void GUI::populatePetList()
{
	this->petList->clear();
	vector<Pet> v;
	if (sortNeeded == true)
		v = this->ctrl.getAllSorted();
	else
		v = this->ctrl.getRepo().getPets();
	for (auto pet : v)
	{
		QString item;
		if (this->options->currentText() == QString("Short"))
			item = QString::fromStdString(pet.getName() + " - " + pet.getBreed() + ", " + std::to_string(pet.getAge()) + " years old");
		else
			item = QString::fromStdString(pet.getName() + " - " + pet.getBreed() + ", " + std::to_string(pet.getAge()) + " yro, " + pet.getPhoto());
		this->petList->addItem(item);
	}

	if (this->ctrl.getRepo().getPets().size() > 0)
		this->petList->setCurrentRow(0);

	sortNeeded = false;
}


void GUI::populatePlayList()
{
	playlist->clear();
	for (auto pet : this->ctrl.getAdoptionList()->getAdoptedList())
	{
		QString item = QString::fromStdString(pet.getName() + " - " + pet.getBreed() + ", " + std::to_string(pet.getAge()) + " yro, " + pet.getPhoto());
		this->playlist->addItem(item);
	}
	if (this->ctrl.getAdoptionList()->getAdoptedList().size() > 0)
		this->playlist->setCurrentRow(0);
}

void GUI::sortHandler()
{
	sortNeeded = true;
	this->populatePetList();
}


void GUI::listItemChanged()
{
	int idx = this->getSelectedIndex();
	if (idx == -1)
		return;

	// get the song at the selected index
	if (idx >= this->ctrl.getRepo().getPets().size())
		return;
	Pet p = this->ctrl.getRepo().getPets()[idx];

	this->nameField->setText(QString::fromStdString(p.getName()));
	this->breedField->setText(QString::fromStdString(p.getBreed()));
	this->ageField->setText(QString::fromStdString(to_string(p.getAge())));
	this->photoField->setText(QString::fromStdString(p.getPhoto()));
}

void GUI::openAdoptionList()
{
	this->ctrl.getAdoptionList()->viewAdoptionList();
}

void GUI::addPetUI()
{
	try
	{
		QString breed = this->breedField->text();
		QString name = this->nameField->text();
		QString age = this->ageField->text();
		QString photo = this->photoField->toPlainText();
		this->ctrl.addToRepo(breed.toStdString(), name.toStdString(), atoi(age.toStdString().c_str()), photo.toStdString());
	}
	catch (Exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
		messageBox.setFixedSize(500, 200);
	}
	this->populatePetList();
}

void GUI::deletePetUI()
{
	try
	{
		QString name = this->nameField->text();
		this->ctrl.deleteFromRepo(name.toStdString());
	}
	catch (Exception& e)
	{
		QMessageBox::critical(0, "Error", e.what());
	}
	this->populatePetList();
}

void GUI::updatePetUI()
{
	try
	{
		QString name = this->nameField->text();
		QString newAge = this->ageField->text();
		QString newPhoto = this->photoField->toPlainText();
		this->ctrl.updateInRepo(name.toStdString(), atoi(newAge.toStdString().c_str()), newPhoto.toStdString());
	}
	catch (Exception& e)
	{
		QMessageBox::critical(0, "Error", e.what());
	}
	this->populatePetList();
}

void GUI::next()
{
	this->playlistRepo.next();
	Pet pet = this->playlistRepo.getCurrent();
	this->currentPet->setText(QString::fromStdString(pet.getName() + " - " + pet.getBreed() + ", " + std::to_string(pet.getAge()) + " yro, " + pet.getPhoto()));
}

void GUI::prev()
{
	this->playlistRepo.prev();
	Pet pet = this->playlistRepo.getCurrent();
	this->currentPet->setText(QString::fromStdString(pet.getName() + " - " + pet.getBreed() + ", " + std::to_string(pet.getAge()) + " yro, " + pet.getPhoto()));
}

void GUI::adopt()
{
	try
	{
		this->ctrl.addToAdoptionList(this->playlistRepo.getCurrent());
		this->populatePlayList();
	}
	catch (Exception& e)
	{
		QMessageBox::critical(0, "Error", e.what());
	}
}

void GUI::openPhoto()
{
	Pet pet = this->playlistRepo.getCurrent();
	pet.openPhoto();
}

void GUI::initForSpecificBreed()
{
	specificBreedCase = true;
	vector<Pet> pets = this->ctrl.getAllBreedYoungerThan(this->giveBreed->text().toStdString(), atoi(this->giveAge->text().toStdString().c_str()));
	Pet pet = pets[0];
	this->playlistRepo = Repository{ pets };
	this->showPlaylistOnly();
	this->currentPet->setText(QString::fromStdString(pet.getName() + " - " + pet.getBreed() + ", " + std::to_string(pet.getAge()) + " yro, " + pet.getPhoto()));
}

void GUI::allButtonHandler()
{
	this->specificBreedCase = false;
	this->showPlaylistOnly(); 
	this->playlistRepo = ctrl.getRepo();
}

void GUI::backHandler()
{
	showUserOnly();
	this->specificBreedCase = false;
}


void GUI::showChartOnly()
{
	chart = new Chart{ this->ctrl };
	this->chart->show();
}

void GUI::undoGUI()
{
	try
	{
		this->ctrl.undo();
		populatePetList();
	}
	catch(Exception& e)
	{
		QMessageBox::critical(0,"Error", e.what());
	}
}

void GUI::redoGUI()
{ 
	try
	{
		this->ctrl.redo();
		populatePetList();
	}
	catch (Exception& e)
	{
		QMessageBox::critical(0, "Error", e.what());
	}
}


void GUI::showAdminOnly()
{
	this->menuWidget->hide();
	this->playlistWidget->hide();
	this->userWidget->hide();
	this->adminWidget->show();
}

void GUI::showUserOnly()
{
	this->menuWidget->hide();
	this->adminWidget->hide();
	this->playlistWidget->hide();
	this->getBreedWidget->hide();
	this->userWidget->show();
}

void GUI::showMenuOnly()
{
	this->userWidget->hide();
	this->adminWidget->hide();
	this->playlistWidget->hide();
	this->menuWidget->show();
}

void GUI::showPlaylistOnly()
{
	this->menuWidget->hide();
	this->userWidget->hide();
	this->adminWidget->hide();
	this->playlistWidget->show();
}
