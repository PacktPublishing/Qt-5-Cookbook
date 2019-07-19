#include <QApplication>
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QMainWindow mainWindow;
   auto label = new QLabel(QObject::tr("Hello from Qt Widgets!"));
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   mainWindow.setCentralWidget(label);
   mainWindow.setWindowTitle(
      QObject::tr("Simple Qt Widgets Application")
   );
   mainWindow.show();

   return QApplication::exec();
}
