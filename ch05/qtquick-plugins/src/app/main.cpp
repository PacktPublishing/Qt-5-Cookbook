#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "core.h"

int main(int argc, char *argv[])
{
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
   QGuiApplication app(argc, argv);

   Core::self();
   QQmlApplicationEngine engine;
   engine.rootContext()->setContextProperty("core", Core::self());
   engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

   return app.exec();
}
