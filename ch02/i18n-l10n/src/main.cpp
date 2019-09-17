#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QLibraryInfo>
#include <QTranslator>

int main(int argc, char *argv[])
{
   QApplication app {argc, argv};
   QApplication::setWindowIcon(
            QIcon {QStringLiteral(":/icons/qtlogo.svg")});

   // Parse arguments
   QCommandLineParser parser;
   parser.addHelpOption();
   QCommandLineOption languageOption {
      {QStringLiteral("l"), QStringLiteral("language")},
       QStringLiteral("Adjusts application language."),
       QStringLiteral("language")};
   parser.addOption(languageOption);
   parser.process(app);
   QString language = parser.value(languageOption);
   QLocale locale = (language.isEmpty()) ?
            QLocale::system():QLocale(language);
   QLocale::setDefault(locale);

   QTranslator qtTranslator;
   qtTranslator.load(locale, QStringLiteral("qt"),
            QStringLiteral("_"),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
   QApplication::installTranslator(&qtTranslator);

   QTranslator myappTranslator;
   myappTranslator.load(locale, QStringLiteral(":/l10n/i18n-l10n"),
                        QStringLiteral("_"));
   QApplication::installTranslator(&myappTranslator);

   MainWindow w {locale};
   w.show();

   return QApplication::exec();
}
