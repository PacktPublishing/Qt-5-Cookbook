#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
   QApplication app {argc, argv};
   QApplication::setWindowIcon(
            QIcon {QStringLiteral(":/icons/qtlogo.svg")});
   QFile file {QStringLiteral(":/style.qss")};
   file.open(QIODevice::ReadOnly);
   app.setStyleSheet(file.readAll()); // clazy:exclude=qt4-qstring-from-array
   MainWindow w;

   w.show();

   return QApplication::exec();
}
