#include "interfata.h"
#include "ProgramCrud.h"
#include "ProgramRead.h"
#include "Observer.h"
#include <sstream>

//PENTRU PROGRAM
void ConsoleGUIProgram::initializeGUIProgComponents() {
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//COMPONENTA LEFT
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//adaugare
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	this->editNrInmP= new QLineEdit;

	lyForm->addRow(lblNrInmP, editNrInmP);
	btnAddProgram = new QPushButton("Adauga masina in program");
	lyForm->addWidget(btnAddProgram);

	lyLeft->addWidget(form);

	//adaugare random
	QWidget* formAddR = new QWidget;
	QFormLayout* lyFormAddR = new QFormLayout;
	formAddR->setLayout(lyFormAddR);
	this->editNr = new QLineEdit;

	lyFormAddR->addRow(lblNr, editNr);
	btnAddRandom = new QPushButton("Adauga masini random in program");
	lyFormAddR->addWidget(btnAddRandom);

	lyLeft->addWidget(formAddR);

	//export
	QWidget* formEx = new QWidget;
	QFormLayout* lyFormEx = new QFormLayout;
	formEx->setLayout(lyFormEx);
	this->editFile = new QLineEdit;

	lyFormEx->addRow(lblFile, editFile);
	btnExport = new QPushButton("Export");
	lyFormEx->addWidget(btnExport);

	lyLeft->addWidget(formEx);

	//goleste program
	btnGoleste = new QPushButton("Goleste lista masini!");
	lyLeft->addWidget(btnGoleste);

	//COMPONENTA RIGHT
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	this->tableMasini = new QListWidget;
	lyRight->addWidget(tableMasini);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

}

void ConsoleGUIProgram::update() {
	this->reloadMasiniListFromProg(this->srv.getAllProgram());
}

void ConsoleGUIProgram::reloadMasiniListFromProg(vector<Masina> masini) {
	this->tableMasini->clear();
	for (auto& masina : masini)
	{
		this->tableMasini->addItem(masina.getNrInmatriculare().c_str());
		this->tableMasini->addItem(masina.getProducator().c_str());
		this->tableMasini->addItem(masina.getModel().c_str());
		this->tableMasini->addItem(masina.getTip().c_str());
	}
}

void ConsoleGUIProgram::connectSignalsSlotsProg() {
	QObject::connect(btnAddProgram, &QPushButton::clicked, this, &ConsoleGUIProgram::gui_AddProgram);
	QObject::connect(btnAddRandom, &QPushButton::clicked, this, &ConsoleGUIProgram::gui_AddProgramRandom);

	QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
		srv.golesteProgram();
		QMessageBox::information(this, "Info", QString::fromStdString("Lista de masini din program a fost golita!"));
		reloadMasiniListFromProg(srv.getAllProgram());
		notify();
		});

	QObject::connect(btnExport, &QPushButton::clicked, this, &ConsoleGUIProgram::gui_Export);
}


void ConsoleGUIProgram::gui_AddProgram() {
	try {
		string nr_inm = editNrInmP->text().toStdString();

		editNrInmP->clear();

		srv.adaugaProgram(nr_inm);
		reloadMasiniListFromProg(this->srv.getAllProgram());
		notify();
		QMessageBox::information(this, "Info", QString::fromStdString("Masina adaugata cu succes in program!"));
	}
	catch (exception&) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Nu exista masina cu acest nr de inmatriculare sau ea a fost deja adaugata!"));
	}
}

void ConsoleGUIProgram::gui_AddProgramRandom() {
	try {
		string n = editNr->text().toStdString();
		int nr;

		editNr->clear();

		nr = stoi(n);
		srv.adaugaRandom(nr);
		reloadMasiniListFromProg(this->srv.getAllProgram());
		notify();
		QMessageBox::information(this, "Info", QString::fromStdString("Masini adaugate random cu succes in program!"));
	}
	catch (exception&) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Trebuie sa introduceti un numar!"));
	}
}

void ConsoleGUIProgram::gui_Export() {
	try {
		string fileName = editFile->text().toStdString();

		editFile->clear();

		srv.salveazaProgram(fileName);
		reloadMasiniListFromProg(this->srv.getAllProgram());
		notify();
		QMessageBox::information(this, "Info", QString::fromStdString("Programul a fost adaugat in fisier!"));
	}
	catch (exception&) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Fisierul nu se poate deschide"));
	}
}


//PENTRU MASINA
void ConsoleGUI::initializeGUIComponents() {
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	//COMPONENTA LEFT LEFT
	QWidget* leftleft = new QWidget;
	QVBoxLayout* lyLeftleft = new QVBoxLayout;
	leftleft->setLayout(lyLeftleft);

	//adaugare
	QWidget* formleft = new QWidget;
	QFormLayout* lyFormleft = new QFormLayout;
	formleft->setLayout(lyFormleft);
	this->editNrInmP = new QLineEdit;

	lyFormleft->addRow(lblNrInmP, editNrInmP);
	btnAddProgram = new QPushButton("Adauga masina in program");
	lyFormleft->addWidget(btnAddProgram);

	lyLeftleft->addWidget(formleft);

	//adaugare random
	QWidget* formAddR = new QWidget;
	QFormLayout* lyFormAddR = new QFormLayout;
	formAddR->setLayout(lyFormAddR);
	this->editNr = new QLineEdit;

	lyFormAddR->addRow(lblNr, editNr);
	btnAddRandom = new QPushButton("Adauga masini random in program");
	lyFormAddR->addWidget(btnAddRandom);

	lyLeftleft->addWidget(formAddR);

	//export
	QWidget* formEx = new QWidget;
	QFormLayout* lyFormEx = new QFormLayout;
	formEx->setLayout(lyFormEx);
	this->editFile = new QLineEdit;

	lyFormEx->addRow(lblFile, editFile);
	btnExport = new QPushButton("Export");
	lyFormEx->addWidget(btnExport);

	lyLeftleft->addWidget(formEx);

	//goleste program
	btnGoleste = new QPushButton("Goleste lista masini!");
	lyLeftleft->addWidget(btnGoleste);
	//CRUD
	btnCRUD = new QPushButton("ARATA CRUD");
	lyLeftleft->addWidget(btnCRUD);

	//DRAW
	btnDRAW = new QPushButton("ARATA DRAW");
	lyLeftleft->addWidget(btnDRAW);

	//COMPONENTA LEFT
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//adaugare
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	this->editNrInm = new QLineEdit;
	this->editProducator = new QLineEdit;
	this->editModel = new QLineEdit;
	this->editTip = new QLineEdit;

	lyForm->addRow(lblNrInm, editNrInm);
	lyForm->addRow(lblProducator, editProducator);
	lyForm->addRow(lblModel, editModel);
	lyForm->addRow(lblTip, editTip);
	btnAddMasina = new QPushButton("Adauga masina");
	lyForm->addWidget(btnAddMasina);

	lyLeft->addWidget(form);

	//stergere
	QWidget* formDell = new QWidget;
	QFormLayout* lyFormDell = new QFormLayout;
	formDell->setLayout(lyFormDell);

	this->editNrInmD = new QLineEdit;
	lyFormDell->addRow(lblNrInmD, editNrInmD);

	btnDellMasina = new QPushButton("Sterge masina");
	lyFormDell->addWidget(btnDellMasina);
	lyLeft->addWidget(formDell);

	//modificare
	QWidget* formMod = new QWidget;
	QFormLayout* lyFormMod = new QFormLayout;
	formMod->setLayout(lyFormMod);

	this->editNrInmM = new QLineEdit;
	this->editProducatorM = new QLineEdit;
	this->editModelM = new QLineEdit;
	this->editTipM = new QLineEdit;

	lyFormMod->addRow(lblNrInmM, editNrInmM);
	lyFormMod->addRow(lblProducatorM, editProducatorM);
	lyFormMod->addRow(lblModelM, editModelM);
	lyFormMod->addRow(lblTipM, editTipM);

	btnModifyMasina = new QPushButton("Modifica masina");
	lyFormMod->addWidget(btnModifyMasina);
	lyLeft->addWidget(formMod);

	//filtrare
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterProd = new QLineEdit;
	lyFormFilter->addRow(lblFilterProd, editFilterProd);
	btnFilterProd = new QPushButton("Filtreaza dupa producator");
	lyFormFilter->addWidget(btnFilterProd);

	editFilterTip = new QLineEdit;
	lyFormFilter->addRow(lblFilterTip, editFilterTip);
	btnFilterTip = new QPushButton("Filtreaza dupa tip");
	lyFormFilter->addWidget(btnFilterTip);

	lyLeft->addWidget(formFilter);

	//sortare
	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBoxSort->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSortNrInm);
	lyRadioBox->addWidget(radioSortTip);
	lyRadioBox->addWidget(radioSortProdModel);

	btnSortMasini = new QPushButton("Sorteaza masinile");
	lyRadioBox->addWidget(btnSortMasini);
	lyRadioBox->addWidget(groupBoxSort);

	lyLeft->addWidget(groupBoxSort); //adaugam in partea stanga.

	//undo
	btnUndo = new QPushButton("Undo");
	lyLeft->addWidget(btnUndo);

	//COMPONENTA RIGHT
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	this->tableMasini = new QListWidget;

	table_new->setColumnCount(4);
	lyRight->addWidget(table_new);
	//lyRight->addWidget(tableMasini);

	//PROGRAM
	btnProgram = new QPushButton{ "DESCHIDE PROGRAM" };
	lyLeft->addWidget(btnProgram);

	lyMain->addWidget(leftleft);
	lyMain->addWidget(left);
	lyMain->addWidget(right);

	//tip
	QWidget* formTip = new QWidget;
	QFormLayout* lyFormTip = new QFormLayout;
	formTip->setLayout(lyFormTip);
	btnTip = new QPushButton("Elemente de tip");
	lyFormTip->addWidget(btnTip);

	lyRight->addWidget(btnTip);

	lyMain->addWidget(left);
	lyMain->addWidget(right);
	QWidget* btn_widget = new QWidget;
	btn_layout = new QVBoxLayout;
	btn_widget->setLayout(btn_layout);
	lyMain->addWidget(btn_widget);
	gui_addTip();

}

void ConsoleGUI::reloadMasiniList(vector<Masina> masini) {
	/*this->tableMasini->clear();
	for (auto& masina : masini)
	{
		this->tableMasini->addItem(masina.getNrInmatriculare().c_str());
		this->tableMasini->addItem(masina.getProducator().c_str());
		this->tableMasini->addItem(masina.getModel().c_str());
		this->tableMasini->addItem(masina.getTip().c_str());
	}*/

	table_new->clearContents(); // Șterge conținutul existent din tabel

	int row = 0;
	table_new->setRowCount(masini.size()); // Setează numărul de rânduri conform dimensiunii listei de mașini

	for (const auto& masina : masini) {
		// Adaugă fiecare mașină în tabel pe un rând nou
		QTableWidgetItem* itemNrInm = new QTableWidgetItem(QString::fromStdString(masina.getNrInmatriculare()));
		QTableWidgetItem* itemProducator = new QTableWidgetItem(QString::fromStdString(masina.getProducator()));
		QTableWidgetItem* itemModel = new QTableWidgetItem(QString::fromStdString(masina.getModel()));
		QTableWidgetItem* itemTip = new QTableWidgetItem(QString::fromStdString(masina.getTip()));

		table_new->setItem(row, 0, itemNrInm);
		table_new->setItem(row, 1, itemProducator);
		table_new->setItem(row, 2, itemModel);
		table_new->setItem(row, 3, itemTip);

		row++;
	}
}

void ConsoleGUI::gui_AddProgram() {
	try {
		string nr_inm = editNrInmP->text().toStdString();

		editNrInmP->clear();

		srv.adaugaProgram(nr_inm);
		reloadMasiniListFromProg(this->srv.getAllProgram());
		notify();
		QMessageBox::information(this, "Info", QString::fromStdString("Masina adaugata cu succes in program!"));
	}
	catch (exception&) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Nu exista masina cu acest nr de inmatriculare sau ea a fost deja adaugata!"));
	}
}

void ConsoleGUI::gui_AddProgramRandom() {
	try {
		string n = editNr->text().toStdString();
		int nr;

		editNr->clear();

		nr = stoi(n);
		srv.adaugaRandom(nr);
		reloadMasiniListFromProg(this->srv.getAllProgram());
		notify();
		QMessageBox::information(this, "Info", QString::fromStdString("Masini adaugate random cu succes in program!"));
	}
	catch (exception&) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Trebuie sa introduceti un numar!"));
	}
}

void ConsoleGUI::gui_Export() {
	try {
		string fileName = editFile->text().toStdString();

		editFile->clear();

		srv.salveazaProgram(fileName);
		reloadMasiniListFromProg(this->srv.getAllProgram());
		notify();
		QMessageBox::information(this, "Info", QString::fromStdString("Programul a fost adaugat in fisier!"));
	}
	catch (exception&) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Fisierul nu se poate deschide"));
	}
}

void ConsoleGUI::reloadMasiniListFromProg(vector<Masina> masini)
{
	this->tableMasini->clear();
	for (auto& masina : masini)
	{
		this->tableMasini->addItem(masina.getNrInmatriculare().c_str());
		this->tableMasini->addItem(masina.getProducator().c_str());
		this->tableMasini->addItem(masina.getModel().c_str());
		this->tableMasini->addItem(masina.getTip().c_str());
	}
}

void ConsoleGUI::connectSignalsSlots() {

	QObject::connect(btnAddMasina, &QPushButton::clicked, this, &ConsoleGUI::gui_AddMasina);

	QObject::connect(btnDellMasina, &QPushButton::clicked, this, &ConsoleGUI::gui_DellMasina);

	QObject::connect(btnModifyMasina, &QPushButton::clicked, this, &ConsoleGUI::gui_ModifyMasina);

	QObject::connect(btnFilterProd, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterProd->text().toStdString();
		this->reloadMasiniList(srv.filtrareProd(filterC));
		editFilterProd->clear();
		});

	QObject::connect(btnFilterTip, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterTip->text().toStdString();
		this->reloadMasiniList(srv.filtrareTip(filterC));
		editFilterTip->clear();
		});

	QObject::connect(btnSortMasini, &QPushButton::clicked, [&]() {
		if (radioSortNrInm->isChecked())
			this->reloadMasiniList(srv.sortByNrInm());
		else if (radioSortTip->isChecked())
			this->reloadMasiniList(srv.sortByTip());
		else if (radioSortProdModel->isChecked())
			this->reloadMasiniList(srv.sortByProdModel());
		});


	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
			this->reloadMasiniList(srv.getAll());
		}
		catch (exception&) { QMessageBox::warning(this, "Warning", QString::fromStdString("Nu se mai poate face undo!")); }
		});

	QObject::connect(btnTip, &QPushButton::clicked, this, &ConsoleGUI::gui_addTip);

	QObject::connect(btnProgram, &QPushButton::clicked, [&]() {
		gui_2.update();
		gui_2.show();
		});

	//PROGRAM
	QObject::connect(btnAddProgram, &QPushButton::clicked, this, &ConsoleGUI::gui_AddProgram);
	QObject::connect(btnAddRandom, &QPushButton::clicked, this, &ConsoleGUI::gui_AddProgramRandom);

	QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
		srv.golesteProgram();
		QMessageBox::information(this, "Info", QString::fromStdString("Lista de masini din program a fost golita!"));
		reloadMasiniListFromProg(srv.getAllProgram());
		notify();
		});

	QObject::connect(btnExport, &QPushButton::clicked, this, &ConsoleGUI::gui_Export);

	//afisare window CRUD
	QObject::connect(btnCRUD, &QPushButton::clicked, [this] {
	auto program = new programCRUDGUI(srv.get_program(), srv);
	program->run();
	});

	//afisare window DRAW
	QObject::connect(btnDRAW, &QPushButton::clicked, [this] {
	auto program = new programReadOnlyGUI(srv.get_program());
	program->show();
	});
}

void ConsoleGUI::gui_AddMasina() {
		string nr_inm = editNrInm->text().toStdString();
		string prod = editProducator->text().toStdString();
		string model = editModel->text().toStdString();
		string tip = editTip->text().toStdString();

		editNrInm->clear();
		editProducator->clear();
		editModel->clear();
		editTip->clear();

		srv.adaugaMasina(nr_inm, prod, model, tip);
		reloadMasiniList(this->srv.getAll());

		QMessageBox::information(this, "Info", QString::fromStdString("Masina adaugata cu succes!"));
		gui_addTip();
	
}

void ConsoleGUI::gui_DellMasina() {
		string nr_inm = editNrInmD->text().toStdString();

		editNrInmD->clear();

		srv.stergeMasina(nr_inm);
		reloadMasiniList(srv.getAll());
		QMessageBox::information(this, "Info", QString::fromStdString("Masina stearsa cu succes!"));
		gui_addTip();
}

void ConsoleGUI::gui_ModifyMasina() {
		string nr_inm = editNrInmM->text().toStdString();
		string prod = editProducatorM->text().toStdString();
		string model = editModelM->text().toStdString();
		string tip = editTipM->text().toStdString();

		editNrInmM->clear();
		editProducatorM->clear();
		editModelM->clear();
		editTipM->clear();

		srv.modificaMasina(nr_inm, prod, model, tip);
		reloadMasiniList(srv.getAll());

		QMessageBox::information(this, "Info", QString::fromStdString("Masina modificata cu succes!"));
		gui_addTip();
}

void ConsoleGUI::gui_addTip() {
	vector<Masina> masini = srv.getAll();
	vector<std::pair<string, int>> tipuri;
	for (auto m : masini) {
		bool ok = false;
		int i = 0;
		for (auto t : tipuri) {
			if (t.first == m.getTip()) {
				ok = true;
				break;
			}
		}
		if (ok == true)
			tipuri[i].second++;
		else tipuri.emplace_back(m.getTip(), 1);
	}
	QLayoutItem* item;
	while ((item = btn_layout->takeAt(0)) != NULL)
	{
		delete item->widget();
		delete item;
	}

	for (auto t : tipuri) {
		string tip = t.first;
		int nr = t.second;
		auto item = new QRadioButton(QString::fromStdString(tip));

		QObject::connect(item, &QRadioButton::clicked, [nr] {
			string n = std::to_string(nr);
			auto* lbl = new QLabel(QString::fromStdString(n));
			lbl->show();
			});
		btn_layout->addWidget(item);
	}
}
