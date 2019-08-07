#include "mainwindow.h"

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QListWidget>
#include <QLabel>

#include "orientabletoolbutton.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   // Menu bar
   auto fileMenu = menuBar()->addMenu(tr("&File"));
   auto exitAction = fileMenu->addAction(QIcon(":/icons/exit.svg"),
                                         tr("E&xit"),
                                         qApp, &QApplication::exit,
                                         Qt::CTRL + Qt::Key_Q
                                         );

   // Tool bar
   auto mainToolBar = addToolBar(tr("Main toolbar"));
   mainToolBar->addAction(exitAction);

   // Status bar
   statusBar()->addPermanentWidget(new QLabel(tr("Ready!")), 1);

   // Central widget
   auto label = new QLabel;
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);

   // Dock widget
   auto listWidget = new QListWidget;
   listWidget->addItems({ tr("First item"),
                          tr("Second item"),
                          tr("Third item") });
   for (auto item : listWidget->findItems("*", Qt::MatchWildcard))
      item->setIcon(QIcon(":/icons/qtlogo.svg"));
   auto dockWidget = new QDockWidget;
   dockWidget->setWidget(listWidget);
   addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

   // Connections
   connect(listWidget, &QListWidget::currentTextChanged,
           label, &QLabel::setText);
   listWidget->setCurrentRow(0);

   auto secondaryToolBar = new QToolBar { tr("Secondary toolbar") };
   addToolBar(Qt::RightToolBarArea, secondaryToolBar);
   secondaryToolBar->addWidget(new OrientableToolButton(QIcon(QLatin1String(":/icons/exit.svg")), "Teste", this));

   // Set window title
   setWindowTitle(tr("DockWidgets Application"));
}

MainWindow::~MainWindow() = default;
