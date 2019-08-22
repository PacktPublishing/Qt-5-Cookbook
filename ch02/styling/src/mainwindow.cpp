#include "mainwindow.h"

#include <QApplication>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QStatusBar>
#include <QStyledItemDelegate>
#include <QToolBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   // Set window attributes
   setWindowTitle(tr("Styling Example Application"));
   resize(640, 480);

   // Menu with simple menu item
   auto fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addAction(tr("&New"));
   fileMenu->addAction(tr("&Save"));
   fileMenu->addAction(tr("Save &as"));
   fileMenu->addSeparator();
   fileMenu->addAction(tr("E&xit"),
      QApplication::instance(), &QApplication::exit);
   auto alignMenu = menuBar()->addMenu(tr("&Align"));
   alignMenu->addActions({
                            new QAction(tr("Align &left")),
                            new QAction(tr("Align &center")),
                            new QAction(tr("Align &right"))
                         });
   alignMenu->addSeparator();
   alignMenu->addActions({
                            new QAction(tr("Align &top")),
                            new QAction(tr("Align ce&nter")),
                            new QAction(tr("Align &bottom"))
                         });

   // Main toolbar with simple action
   auto mainToolBar = addToolBar(tr("Main toolbar"));
//   mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   mainToolBar->addActions(fileMenu->actions());
   mainToolBar->addSeparator();
   mainToolBar->addAction(tr("&Alignment Large Text"))->setMenu(alignMenu);

   // Central widget
   auto centralWidget = new QWidget;
   auto layout = new QVBoxLayout { centralWidget };

   // ComboBox and Slider
   auto horizontalLayout1 = new QHBoxLayout;
   auto comboBox = new QComboBox;
   comboBox->setItemDelegate(new QStyledItemDelegate(comboBox));
   comboBox->addItems({ tr("One"), tr("Two"), tr("Three"), tr("Four")});
   horizontalLayout1->addWidget(comboBox);
   auto slider = new QSlider { Qt::Horizontal };
   slider->setSizePolicy(comboBox->sizePolicy());
   horizontalLayout1->addWidget(slider);
   layout->addLayout(horizontalLayout1);

   auto horizontalLayout2 = new QHBoxLayout;
   horizontalLayout2->addWidget(new QLabel { tr("A lineedit: ") });
   horizontalLayout2->addWidget(new QLineEdit);
   layout->addLayout(horizontalLayout2);

   setCentralWidget(centralWidget);

   // Status bar
   statusBar()->addPermanentWidget(new QLabel { tr("Ready!") }, 1);

   setAttribute(Qt::WA_TranslucentBackground);
   setWindowFlags(Qt::FramelessWindowHint);
}
