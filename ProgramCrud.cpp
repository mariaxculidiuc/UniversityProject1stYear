#pragma once
#include "ProgramCRUD.h"
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\QtWidgetsApplication1\Observer.h"

void programCRUDGUI::run() {
    this->program.addObserver(this);

    this->initComponents();
    this->table->setModel(model);
    this->connectSignals();
    this->update();
    wnd->show();
}

void programCRUDGUI::initComponents() {
    wnd->setLayout(layout);

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    layout->addWidget(table);

    slider->setMinimum(0);
    slider->setMaximum(srv.getAllProgram().size());
    slider->setOrientation(Qt::Horizontal);
    slider->setTickPosition(QSlider::TicksAbove);
    layout->addWidget(slider);

    layout->addWidget(btnadd);
    layout->addWidget(btnempty);
}

void programCRUDGUI::connectSignals() {
    QObject::connect(btnadd, &QPushButton::clicked, [this]() {

        int number = slider->value();
        srv.adaugaRandom(number);
        program.notify();
        });
    QObject::connect(btnempty, &QPushButton::clicked, [this]() {
        program.goleste_program();
        program.notify();
        });
}

void programCRUDGUI::populateTable(QTableView* table, vector<Masina>& masini) {
    /*this->table->clearContents();
    this->table->setRowCount(static_cast<int>(masini.size()));

    int lineNumber = 0;
    for (Masina& masina : masini) {
        this->table->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(masina.getNrInmatriculare())));
        this->table->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(masina.getProducator())));
        this->table->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(masina.getModel())));
        this->table->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(masina.getTip())));
        lineNumber++;
    }*/
    this->model->setAct(masini);
}

void programCRUDGUI::update() {
    //this->model = new MyTableModel{ srv.get_all_program_srv() };
    //this->populateTable(table, this->program.get_all());
    /*auto l = this->program.get_all_program();
    this->populateTable(table, l);*/
    this->model->setAct(srv.getAllProgram());
}