#include <QApplication>

#include "core.h"

int main(int argc, char *argv[])
{
   QApplication app {argc, argv};

   MyApp::Core::initialize();

   return QApplication::exec();
}
