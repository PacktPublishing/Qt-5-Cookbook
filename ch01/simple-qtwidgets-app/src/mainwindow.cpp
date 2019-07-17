#include "mainwindow.h"

#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QListWidget>
#include <QStringListModel>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   // Action
   auto exitAction = new QAction(QIcon(":/icons/application-exit.svg"),
                               tr("E&xit"),
                               this);
   exitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
   connect(exitAction, &QAction::triggered,
           []() { QApplication::exit(); });

   // Menu bar
   auto menuBar = new QMenuBar;
   auto fileMenu = new QMenu(tr("&File"), menuBar);
   fileMenu->addAction(exitAction);
   menuBar->addMenu(fileMenu);
   setMenuBar(menuBar);

   // Tool bar
   auto mainToolBar = addToolBar(tr("Main toolbar"));
   mainToolBar->addAction(exitAction);

   // Status bar
   auto statusBar = new QStatusBar;
   statusBar->addPermanentWidget(new QLabel(tr("Ready!")), 1);
   setStatusBar(statusBar);

   // Central widget
   auto label = new QLabel;
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);

   // Dock widget
   auto dockWidget = new QDockWidget;
   auto listWidget = new QListWidget;
   listWidget->addItems({ tr("First item"),
                          tr("Second item"),
                          tr("Third item") });
   for (auto item : listWidget->findItems("*", Qt::MatchWildcard))
      item->setIcon(QIcon(":/icons/qtlogo.svg"));
   dockWidget->setWidget(listWidget);
   addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

   // Connections
   connect(listWidget, &QListWidget::currentTextChanged,
           label, &QLabel::setText);
   listWidget->setCurrentRow(0);

   // Set window title
   setWindowTitle(tr("Simple QtWidgets Application"));
}

MainWindow::~MainWindow() = default;
