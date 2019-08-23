#include "mycounter.h"

#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
   QApplication app {argc, argv};

   // Main window and widgets
   QMainWindow mainWindow;
   auto spin = new QSpinBox;
   auto slider = new QSlider {Qt::Horizontal};
   auto label = new QLabel {QObject::tr("This is a QLabel!")};
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

   // Set central widget
   auto centralWidget = new QWidget;
   mainWindow.setCentralWidget(centralWidget);

   // Layout
   auto layout = new QVBoxLayout {centralWidget};
   layout->addWidget(spin);
   layout->addWidget(slider);
   layout->addWidget(label);

   // Our QObject
   auto myCounter = new MyCounter {0, &mainWindow};

   // Connections
   QObject::connect(spin, QOverload<int>::of(&QSpinBox::valueChanged),
                    slider, &QSlider::setValue);
   QObject::connect(slider, &QSlider::valueChanged,
                    spin, &QSpinBox::setValue);
   QObject::connect(slider, &QSlider::valueChanged,
                    myCounter, &MyCounter::setValue);
   QObject::connect(myCounter, &MyCounter::valueChanged,
                    label, [label](int value) {
                       label->setText("Value changed to " +
                                      QString::number(value) + "!");
                    }
   );

   // Show main window
   mainWindow.setWindowTitle(QObject::tr("Basic Wiring Application"));
   mainWindow.resize(640, 480);
   mainWindow.show();

   // Start event loop
   return QApplication::exec();
}
