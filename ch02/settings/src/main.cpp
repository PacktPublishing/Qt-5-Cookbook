#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication app {argc, argv};

   QApplication::setOrganizationName(QStringLiteral("PacktPub"));
   QApplication::setOrganizationDomain(
      QStringLiteral("packtpub.com"));
   QApplication::setApplicationName(QStringLiteral("settings"));

   QApplication::setWindowIcon(
            QIcon {QStringLiteral(":/icons/qtlogo.svg")});
   MainWindow w;
   w.show();

   return QApplication::exec();
}

