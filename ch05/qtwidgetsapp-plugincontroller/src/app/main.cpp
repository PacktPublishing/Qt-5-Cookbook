#include <QApplication>

#include "core.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QtWidgetsApp::Core::initialize();

   app.exec();
}
