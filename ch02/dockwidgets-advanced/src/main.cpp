#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   QApplication::setWindowIcon(
      QIcon(QLatin1String(":/icons/qtlogo.svg")));
   MainWindow w;
   w.showMaximized();

   return QApplication::exec();
}

