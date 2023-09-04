#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QListWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "Observer.h"
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\MasinaService.h"

using std::vector;
using std::string;

class ConsoleGUIProgram :public QWidget, public Observable {
private:
	MasinaService& srv;

	//add
	QLabel* lblNrInmP = new QLabel("Nr de inmatriculare:");
	QLineEdit* editNrInmP;
	QPushButton* btnAddProgram;

	//add random
	QLabel* lblNr = new QLabel("Numar:");
	QLineEdit* editNr;
	QPushButton* btnAddRandom;

	//goleste program
	QPushButton* btnGoleste;

	//export
	QLabel* lblFile = new QLabel("Fisier:");
	QLineEdit* editFile;
	QPushButton* btnExport;

	QListWidget* tableMasini;


	void initializeGUIProgComponents();
	void connectSignalsSlotsProg();
	void reloadMasiniListFromProg(vector<Masina> masini);

public:
	ConsoleGUIProgram(MasinaService& srv) : srv{ srv } {
		initializeGUIProgComponents();
		connectSignalsSlotsProg();
		reloadMasiniListFromProg(srv.getAllProgram());
	}

	void gui_AddProgram();
	void gui_AddProgramRandom();
	void gui_Export();
	void update();
};



class ConsoleGUI : public QWidget, public Observable{
private:
	QVBoxLayout* btn_layout;
	MasinaService& srv;
	ConsoleGUIProgram gui_2{srv};

	//add
	QLabel* lblNrInmP = new QLabel("Nr de inmatriculare:");
	QLineEdit* editNrInmP;
	QPushButton* btnAddProgram;

	//add random
	QLabel* lblNr = new QLabel("Numar:");
	QLineEdit* editNr;
	QPushButton* btnAddRandom;

	//goleste program
	QPushButton* btnGoleste;

	//export
	QLabel* lblFile = new QLabel("Fisier:");
	QLineEdit* editFile;
	QPushButton* btnExport;

	//program crud
	QPushButton* btnCRUD;

	//program draw
	QPushButton* btnDRAW;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//adauga
	QGroupBox* groupBoxAdd = new QGroupBox(tr("Adaugare"));

	QLabel* lblNrInm = new QLabel("Nr inmatriculare:");
	QLabel* lblProducator = new QLabel("Producator:");
	QLabel* lblModel = new QLabel("Model:");
	QLabel* lblTip = new QLabel("Tip:");

	QLineEdit* editNrInm;
	QLineEdit* editProducator;
	QLineEdit* editModel;
	QLineEdit* editTip;

	//sterge
	QGroupBox* groupBoxDell = new QGroupBox(tr("Stergere"));

	QLabel* lblNrInmD = new QLabel("Numarul de inmatriculare:");
	QLineEdit* editNrInmD;

	//modifica
	QGroupBox* groupBoxMod = new QGroupBox(tr("Modificare"));

	QLabel* lblNrInmM = new QLabel("Numarul de inmatriculare:");
	QLabel* lblProducatorM = new QLabel("Producatorul nou:");
	QLabel* lblModelM = new QLabel("Modelul nou:");
	QLabel* lblTipM = new QLabel("Tipul nou:");
	QLineEdit* editNrInmM;
	QLineEdit* editProducatorM;
	QLineEdit* editModelM;
	QLineEdit* editTipM;

	QPushButton* btnAddMasina;
	QPushButton* btnDellMasina;
	QPushButton* btnModifyMasina;
	QPushButton* btnFindMasina;

	//filter
	QGroupBox* groupBoxFilter = new QGroupBox(tr("Filtrare"));

	QLabel* lblFilterProd = new QLabel{ "Producator dupa care se filtreaza:" };
	QLineEdit* editFilterProd;
	QLabel* lblFilterTip = new QLabel{ "Tipul dupa care se filtreaza:" };
	QLineEdit* editFilterTip;
	QPushButton* btnFilterProd;
	QPushButton* btnFilterTip;

	//sort
	QGroupBox* groupBoxSort = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSortNrInm = new QRadioButton(QString::fromStdString("Nr inmatriculare"));
	QRadioButton* radioSortTip = new QRadioButton(QString::fromStdString("Tip"));
	QRadioButton* radioSortProdModel = new QRadioButton(QString::fromStdString("Produs si model"));
	QPushButton* btnSortMasini;

	QListWidget* tableMasini;
	QTableWidget* table_new = new QTableWidget();

	//tip
	QPushButton* btnTip;

	//undo
	QPushButton* btnUndo;

	void initializeGUIComponents();

	void connectSignalsSlots();

	void reloadMasiniList(vector<Masina> masini);

	//PROGRAM
	QPushButton* btnProgram;
	void gui_AddProgram();
	void gui_AddProgramRandom();
	void gui_Export();
	void reloadMasiniListFromProg(vector<Masina> masini);


public:
	ConsoleGUI(MasinaService& srv) : srv{ srv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadMasiniList(srv.getAll());
	}

	void gui_AddMasina();
	void gui_DellMasina();
	void gui_ModifyMasina();
	void gui_addTip();
};

