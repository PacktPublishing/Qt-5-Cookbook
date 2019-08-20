#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   QApplication::setWindowIcon(
      QIcon(QStringLiteral(":/icons/qtlogo.svg"))
   );

   QTranslator myappTranslator;
   // Use system locale
   myappTranslator.load(QLocale::system(), ":/l10n/i18n-l10n", ".");
//   // Force a specific locale using the default locale
//   QLocale::setDefault(QLocale::Portuguese);
//   myappTranslator.load(QLocale(), ":/l10n/i18n-l10n", ".");
   app.installTranslator(&myappTranslator);

   QTranslator qtTranslator;
   qDebug() << qtTranslator.load("qt_de.qm", "/usr/share/qt/translations/");
   app.installTranslator(&qtTranslator);

   MainWindow w;
   w.showMaximized();

   return QApplication::exec();
}

