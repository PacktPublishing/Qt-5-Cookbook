#include "mainwindow.h"

#include <QApplication>
#include <QCalendarWidget>
#include <QDockWidget>
#include <QLabel>
#include <QListWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QtWebEngineWidgets/QWebEngineView>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   createStandardWidgets(tr("DockWidgets Example Application"));

   // A list widget
   auto listWidget = new QListWidget;
   listWidget->addItems({
      tr("First item"), tr("Second item"), tr("Third item")
   });
   const QList<QListWidgetItem *> &items = listWidget->findItems(
      QStringLiteral("*"),Qt::MatchWildcard
   );
   for (auto item : items) {
      item->setIcon(QIcon(QLatin1String(":/icons/qtlogo.svg")));
   }

   // Left dockwidget 1
   auto leftDockWidget1 = new QDockWidget { tr("ListWidget") };
   leftDockWidget1->setWidget(listWidget);
   addDockWidget(Qt::LeftDockWidgetArea, leftDockWidget1);

   // Left dockwidget 2
   auto leftDockWidget2 = new QDockWidget { tr("Calendar") };
   auto calendarWidgetWrapper = new QWidget;
   auto layout = new QVBoxLayout;
   layout->addWidget(new QCalendarWidget);
   layout->addItem(
      new QSpacerItem(0, 0,
                      QSizePolicy::Minimum, QSizePolicy::Expanding)
   );
   calendarWidgetWrapper->setLayout(layout);
   leftDockWidget2->setWidget(calendarWidgetWrapper);
   addDockWidget(Qt::LeftDockWidgetArea, leftDockWidget2);

   // Right dockwidget
   auto rightDockWidget = new QDockWidget { tr("WebEngineView") };
   rightDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                    Qt::RightDockWidgetArea);
   auto webEngineView = new QWebEngineView();
   webEngineView->setUrl(QUrl(QStringLiteral("https://www.qt.io")));
   rightDockWidget->setWidget(webEngineView);
   addDockWidget(Qt::RightDockWidgetArea, rightDockWidget);

   // View menu
   auto viewMenu = menuBar()->addMenu(tr("&View"));
   viewMenu->addActions(createPopupMenu()->actions());

   // Tabify
   auto tabifyAction = new QAction(tr("&Tabify"), this);
   tabifyAction->setShortcut(Qt::CTRL + Qt::Key_T);
   tabifyAction->setCheckable(true);
   connect(tabifyAction, &QAction::toggled, this,
      [leftDockWidget1, leftDockWidget2, rightDockWidget, this]
      (bool checked) {
         if (checked) {
            addDockWidget(Qt::LeftDockWidgetArea, leftDockWidget1);
            tabifyDockWidget(leftDockWidget1, leftDockWidget2);
            tabifyDockWidget(leftDockWidget2, rightDockWidget);
         }
         else {
            addDockWidget(Qt::LeftDockWidgetArea, leftDockWidget1);
            addDockWidget(Qt::LeftDockWidgetArea, leftDockWidget2);
            addDockWidget(Qt::RightDockWidgetArea, rightDockWidget);
         }
   });
   viewMenu->addSeparator();
   viewMenu->addAction(tabifyAction);
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
