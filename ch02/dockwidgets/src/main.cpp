#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   app.setWindowIcon(QIcon(":/icons/qtlogo.svg"));
   MainWindow w;
   w.show();

   return QApplication::exec();
}

