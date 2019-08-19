#include "mainwindow.h"

#include <QApplication>
#include <QCalendarWidget>
#include <QDockWidget>
#include <QLabel>
#include <QListWidget>
#include <QMenuBar>
#include <QSettings>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   _tabifyAction(new QAction(tr("&Tabify"), this))
{
   createStandardWidgets(tr("Settings Example Application"));

   // A list widget
   auto listWidget = new QListWidget;
   listWidget->addItems({
      tr("First item"), tr("Second item"), tr("Third item")
   });
   const QList<QListWidgetItem *> &items = listWidget->findItems(
      QStringLiteral("*"),Qt::MatchWildcard
   );
   for (auto item : items) {
      item->setIcon(QIcon(QStringLiteral(":/icons/qtlogo.svg")));
   }

   // Left dockwidget 1
   auto leftDockWidget1 = new QDockWidget { tr("ListWidget") };
   leftDockWidget1->setObjectName(QStringLiteral("leftDockWidget1"));
   leftDockWidget1->setWidget(listWidget);
   connect(leftDockWidget1, &QDockWidget::topLevelChanged,
           this, &MainWindow::topLevelChanged);
   addDockWidget(Qt::LeftDockWidgetArea, leftDockWidget1);

   // Left dockwidget 2
   auto leftDockWidget2 = new QDockWidget { tr("Calendar") };
   leftDockWidget2->setObjectName(QStringLiteral("leftDockWidget2"));
   auto calendarWidgetWrapper = new QWidget;
   auto layout = new QVBoxLayout { calendarWidgetWrapper };
   layout->addWidget(new QCalendarWidget);
   layout->addItem(
      new QSpacerItem(0, 0,
                      QSizePolicy::Minimum, QSizePolicy::Expanding)
   );
   leftDockWidget2->setWidget(calendarWidgetWrapper);
   connect(leftDockWidget2, &QDockWidget::topLevelChanged,
           this, &MainWindow::topLevelChanged);
   addDockWidget(Qt::LeftDockWidgetArea, leftDockWidget2);

   // Right dockwidget
   auto rightDockWidget = new QDockWidget { tr("WebEngineView") };
   rightDockWidget->setObjectName(QStringLiteral("rightDockWidget"));
   rightDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                    Qt::RightDockWidgetArea);
   auto webEngineView = new QWebEngineView();
   webEngineView->setUrl(QStringLiteral("https://www.qt.io"));
   rightDockWidget->setWidget(webEngineView);
   connect(rightDockWidget, &QDockWidget::topLevelChanged,
           this, &MainWindow::topLevelChanged);
   addDockWidget(Qt::RightDockWidgetArea, rightDockWidget);

   // View menu
   auto viewMenu = menuBar()->addMenu(tr("&View"));
   viewMenu->addActions(createPopupMenu()->actions());

   // Tabify
   _tabifyAction->setShortcut(Qt::CTRL + Qt::Key_T);
   _tabifyAction->setCheckable(true);
   connect(_tabifyAction, &QAction::toggled, this,
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
   viewMenu->addAction(_tabifyAction);

   readSettings();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
   writeSettings();
   QMainWindow::closeEvent(event);
}

void MainWindow::topLevelChanged(bool topLevel)
{
   Q_UNUSED(topLevel)
   auto dockWidget = qobject_cast<QDockWidget *>(sender());
   if (_tabifyAction->isChecked()) {
      if (tabifiedDockWidgets(dockWidget).size() < 2) {
         _tabifyAction->blockSignals(true);
         _tabifyAction->setChecked(false);
         _tabifyAction->blockSignals(false);
      }
   } else {
      if (dockWidgetArea(dockWidget) == Qt::LeftDockWidgetArea &&
          tabifiedDockWidgets(dockWidget).size() == 2) {
         _tabifyAction->blockSignals(true);
         _tabifyAction->setChecked(true);
         _tabifyAction->blockSignals(false);
      }
   }
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
   mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
   mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   mainToolBar->addAction(exitAction);

   // Central widget
   auto label = new QLabel { title };
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);
}

void MainWindow::writeSettings()
{
   QSettings settings;
   settings.setValue(QStringLiteral("geometry"), saveGeometry());
   settings.setValue(QStringLiteral("windowState"), saveState());
   settings.setValue(QStringLiteral("menu/tabify"),
                     _tabifyAction->isChecked());
}

void MainWindow::readSettings()
{
   QSettings settings;
   const QByteArray geometry = settings.value(
            QStringLiteral("geometry"), QByteArray()
            ).toByteArray();
   if (!geometry.isEmpty()) {
      restoreGeometry(geometry);
      restoreState(
         settings.value(QStringLiteral("windowState")).toByteArray()
      );
   }
   _tabifyAction->setChecked(
      settings.value(QStringLiteral("tabify"), false).toBool()
   );
}
