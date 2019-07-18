#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

int main(int argc, char *argv[])
{
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
   QGuiApplication app(argc, argv);
   app.setWindowIcon(QIcon(":/icons/qtlogo.svg"));

   QQmlApplicationEngine engine;
   engine.load(QUrl("qrc:/main.qml"));

   return app.exec();
}
