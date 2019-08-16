#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QMenuBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   createStandardWidgets(
      tr("Handling Graphical Items Example Application"));
}

void MainWindow::createStandardWidgets(const QString &title)
{
   // Set window title
   setWindowTitle(title);

   // Menu with simple menu item
   auto fileMenu = menuBar()->addMenu(tr("&File"));
   auto exitAction = fileMenu->addAction(
            QIcon(QLatin1String(":/icons/exit.svg")),
            tr("E&xit"),
            QApplication::instance(), &QApplication::exit,
            Qt::CTRL + Qt::Key_Q
            );

   // Main toolbar with simple action
   auto mainToolBar = addToolBar(tr("Main toolbar"));
   mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   mainToolBar->addAction(exitAction);

   // Central widget
   auto label = new QLabel { title };
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);
}
