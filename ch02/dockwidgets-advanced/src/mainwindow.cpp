#include "mainwindow.h"

#include <QApplication>
#include <QCalendarWidget>
#include <QLabel>
#include <QListWidget>
#include <QMenuBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWebEngineView>

#include "docktoolbar.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   createStandardWidgets(
            tr("DockWidgets Advanced Example Application"));

   // A list widget
   auto listWidget = new QListWidget;
   listWidget->addItems({ tr("First item"),
                          tr("Second item"),
                          tr("Third item") }
                        );
   const QList<QListWidgetItem *> &items = listWidget->findItems(
            QStringLiteral("*"), Qt::MatchWildcard);
   for (auto item : items) {
      item->setIcon(QIcon(QStringLiteral(":/icons/qtlogo.svg")));
   }

   // Left toolbar with associated dockwidgets
   auto leftToolBar = new DockToolBar { tr("Left toolbar") };
   addToolBar(Qt::LeftToolBarArea, leftToolBar);
   leftToolBar->addDockWidget(
            QIcon(QStringLiteral(":/icons/listwidget.svg")),
            tr("ListView"),
            listWidget
            );
   leftToolBar->addDockWidget(
            QIcon(QStringLiteral(":/icons/textedit.svg")),
            tr("TextEdit"),
            new QTextEdit { tr("Edit me!") }
            );

   // Right toolbar with associated dockwidgets
   auto rightToolBar = new DockToolBar { tr("Right toolbar") };
   addToolBar(Qt::RightToolBarArea, rightToolBar);
   auto webEngine = new QWebEngineView;
   webEngine->load(QStringLiteral("https://www.qt.io"));
   rightToolBar->addDockWidget(
            QIcon(QStringLiteral(":/icons/webengine.svg")),
            tr("WebEngine"),
            webEngine);
   QWidget *calendarWidget = new QWidget;
   auto layout = new QVBoxLayout { calendarWidget };
   layout->addWidget(new QCalendarWidget);
   layout->addItem(new QSpacerItem { 0, 0,
                                   QSizePolicy::Minimum,
                                   QSizePolicy::Expanding }
                  );
   rightToolBar->addDockWidget(
            QIcon(QStringLiteral(":/icons/calendar.svg")),
            tr("Calendar"),
            calendarWidget
            );

   // View menu
   auto viewMenu = menuBar()->addMenu(tr("&View"));
   viewMenu->addActions(createPopupMenu()->actions());
}

void MainWindow::createStandardWidgets(const QString &title)
{
   // Set window title
   setWindowTitle(title);

   // Menu with simple menu item
   auto fileMenu = menuBar()->addMenu(tr("&File"));
   auto exitAction = fileMenu->addAction(
            QIcon(QStringLiteral(":/icons/exit.svg")),
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
