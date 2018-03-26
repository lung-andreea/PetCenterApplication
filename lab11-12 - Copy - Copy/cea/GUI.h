#pragma once
#include"Controller.h"
#include<QApplication>
#include <QWidget>
#include <qwidget.h>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include<qgroupbox.h>
#include<QMessageBox>
#include<QComboBox>
#include<QRadioButton>
#include<qcustomplot.h>

class Chart : public QWidget
{

	Q_OBJECT

private:
	Controller& ctrl;

public:
	Chart( Controller& ctrl, QWidget *parent = 0);
	~Chart() {};
};

class GUI : public QWidget 
{	
	Q_OBJECT

public:
	GUI(Controller& ctrl, QWidget *parent = 0);
	~GUI();

	//Controller getCtrl() const { return ctrl; };

protected:
	virtual void keyPressEvent(QKeyEvent *event);

private:
	Controller& ctrl;
	Chart* chart;
	QWidget* choiceWidget;

	bool sortNeeded;
	bool specificBreedCase;
	Repository playlistRepo;
	QRadioButton* csv;
	QRadioButton* html;
	QPushButton* pick;
	QPushButton* adminButton;
	QPushButton* userButton;
	QPushButton* chartButton;
	QPushButton* exitButton;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* sortButton;
	QPushButton* prevButton;
	QPushButton* adoptButton;
	QPushButton* nextButton;
	QPushButton* viewPhotoButton;
	QPushButton* allButton;
	QPushButton* specificBreedButton;
	QPushButton* backButtonAdmin;
	QPushButton* backButtonUser;
	QPushButton* backButtonPlayList;
	QListWidget* petList;
	QListWidget* playlist;
	QLineEdit* breedField;
	QLineEdit* nameField;
	QLineEdit* ageField;
	QTextEdit* photoField;
	QLineEdit* giveBreed;
	QLineEdit* giveAge;
	QGroupBox* menuWidget;
	QGroupBox* adminWidget;
	QGroupBox* userWidget;
	QWidget* playlistWidget;
	QWidget* getBreedWidget;
	QLabel* currentPet;
	QComboBox* options;
	QPushButton* openAdopList;

	void initGUI();
	void setAdoptionListGUI();
	int getSelectedIndex();
	void connectSignalsAndSlots();

	void populatePetList();
	void populatePlayList();
	void sortHandler();
	void listItemChanged();

	void openAdoptionList();
	void addPetUI();
	void deletePetUI();
	void updatePetUI();
	void next();
	void prev();
	void adopt();
	void openPhoto();
	void initForSpecificBreed();
	void allButtonHandler();
	void backHandler();
	void showChartOnly();
	void undoGUI();
	void redoGUI();
public slots:
	void showMenuOnly();
	void showAdminOnly();
	void showUserOnly();
	void showPlaylistOnly();

};

