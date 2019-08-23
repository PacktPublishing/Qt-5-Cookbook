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
   app.setStyleSheet(QString::fromLatin1(file.readAll()));
   MainWindow w;

   w.show();

   return QApplication::exec();
}

