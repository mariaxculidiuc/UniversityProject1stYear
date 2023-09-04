#include "Observer.h"
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\MasinaService.h"
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\Program.h"
#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include <cmath>

#define RECTANGLE_MAX_DIM 256

class programReadOnlyGUI : public QWidget, public Observer {
private:
    Program& program;

public:
    programReadOnlyGUI(Program& program);

    void update() override;

    void paintEvent(QPaintEvent* event) override;

    ~programReadOnlyGUI() {
        this->program.removeObserver(this);
    }
};
