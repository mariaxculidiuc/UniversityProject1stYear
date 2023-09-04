#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\Masina.h"
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\MasinaService.h"
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\MasinaRepo.h"
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\MasinaValidator.h"
#include "C:\Users\culid\OneDrive\Desktop\facultate\2nd semester of 1st year\OOP\Lab 6-7, Culidiuc Maria\Lab 6-7, Culidiuc Maria\console.h"
#include "interfata.h"

void testAll() {
	testeRepo();
	testValidator();
	testeSrv();
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	testAll();
	MasinaRepo rep;
	MasinaValidator val;
	MasinaService srv{ rep,val };
	ConsoleGUI gui(srv);
	gui.show();

	return app.exec();
}