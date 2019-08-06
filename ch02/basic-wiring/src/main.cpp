#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>

#include "mycounter.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QMainWindow mainWindow;
   auto spinBox = new QSpinBox;
   auto slider = new QSlider { Qt::Horizontal };
   auto label = new QLabel { QObject::tr("This is a QLabel!") };
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

   auto layout = new QVBoxLayout;
   layout->addWidget(spinBox);
   layout->addWidget(slider);
   layout->addWidget(label);

   auto myCounter = new MyCounter { 0, &mainWindow };

   QObject::connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
                    slider, &QSlider::setValue);
   QObject::connect(slider, &QSlider::valueChanged,
                    spinBox, &QSpinBox::setValue);
   QObject::connect(slider, &QSlider::valueChanged,
                    myCounter, &MyCounter::setValue);
   QObject::connect(myCounter, &MyCounter::valueChanged,
                    label, [label](int value) {
                       label->setText("Value changed to " + QString::number(value) + "!");
                    });

   auto centralWidget = new QWidget;
   centralWidget->setLayout(layout);
   mainWindow.setCentralWidget(centralWidget);

   mainWindow.setWindowTitle(
      QObject::tr("Basic Wiring Application")
   );
   mainWindow.resize(640, 480);
   mainWindow.show();

   return QApplication::exec();
}
