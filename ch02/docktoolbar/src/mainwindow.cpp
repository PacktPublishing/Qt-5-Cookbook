#include "mainwindow.h"

#include <QApplication>
#include <QButtonGroup>
#include <QCalendarWidget>
#include <QDockWidget>
#include <QLabel>
#include <QListWidget>
#include <QMenuBar>
#include <QSpacerItem>
#include <QStatusBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QtWebEngineWidgets/QWebEngineView>

#include "docktoolbar.h"
#include "orientabletoolbutton.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
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
   auto label = new QLabel { tr("Hello from docktoolbar!") };
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);

   // A list widget
   auto listWidget = new QListWidget;
   listWidget->addItems({
      tr("First item"),
      tr("Second item"),
      tr("Third item")
   });
   for (auto item : listWidget->findItems(QStringLiteral("*"), Qt::MatchWildcard)) {
      item->setIcon(QIcon(QLatin1String(":/icons/qtlogo.svg")));
   }

   // Left toolbar with associated dockwidgets
   auto leftToolBar = new DockToolBar { tr("Secondary toolbar") };
   addToolBar(Qt::LeftToolBarArea, leftToolBar);
   leftToolBar->addDockWidget(QIcon(QLatin1String(":/icons/listwidget.svg")), tr("ListView"), listWidget);
   leftToolBar->addDockWidget(QIcon(QLatin1String(":/icons/textedit.svg")), tr("TextEdit"), new QTextEdit { tr("Edit me!") });

   // Right toolbar with associated dockwidgets
   auto rightToolBar = new DockToolBar { tr("Secondary toolbar") };
   addToolBar(Qt::RightToolBarArea, rightToolBar);
   auto webEngine = new QWebEngineView;
   webEngine->load(QUrl(QStringLiteral("https://www.qt.io")));
   rightToolBar->addDockWidget(QIcon(QLatin1String(":/icons/webengine.svg")), tr("WebEngine"), webEngine);
   QWidget *calendarWidget = new QWidget;
   auto layout = new QVBoxLayout;
   layout->addWidget(new QCalendarWidget);
   layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
   calendarWidget->setLayout(layout);
   rightToolBar->addDockWidget(QIcon(QLatin1String(":/icons/calendar.svg")), tr("Calendar"), calendarWidget);

   // Set window title
   setWindowTitle(tr("Dock Toolbar Example Application"));
}
