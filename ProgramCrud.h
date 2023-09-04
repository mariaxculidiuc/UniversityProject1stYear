#pragma once
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\Program.h"
#include "Observer.h"
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\MasinaService.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qslider.h>
#include <qlayout>
#include <vector>
#include "Observer.h"
#include "TableModel.h"

using std::vector;

class programCRUDGUI : public QWidget, public Observer {
private:
    Program& program;
    MasinaService& srv;
    QWidget* wnd;
    QHBoxLayout* layout;
    //QTableWidget* table;
    QTableView* table;
    QSlider* slider;
    QPushButton* btnadd;
    QPushButton* btnempty;

    TableModel* model;

    void initComponents();
    void connectSignals();

    //void populateTable(QTableWidget* table,vector<Masina>& all);
    void populateTable(QTableView* table, vector<Masina>& all);
public:
    explicit programCRUDGUI(Program& program, MasinaService& srv) :program{ program }, srv{ srv }{
        wnd = new QWidget;
        layout = new QHBoxLayout;
        btnadd = new QPushButton("GENERARE MASINI RANDOM");
        btnempty = new QPushButton("GOLESTE PROGRAM");
        slider = new QSlider;
        //table = new QTableWidget(0, 4);
        table = new QTableView;
        this->model = new TableModel{ srv.getAllProgram() };
        program.addObserver(this);
    };
    void run();

    void update() override;

    ~programCRUDGUI() {
        this->program.removeObserver(this);
    }
};
