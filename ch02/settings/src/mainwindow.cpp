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

MainWindow::MainWindow(QWidget *parent) : QMainWindow {parent}
{
   createStandardWidgets(tr("Settings Example Application"));

   // A list widget
   auto listWidget = new QListWidget;
   listWidget->setSizePolicy(QSizePolicy::Expanding,
                             QSizePolicy::Expanding);
   listWidget->addItems({
      tr("First item"), tr("Second item"), tr("Third item")});
   const QList<QListWidgetItem *> &items = listWidget->findItems(
            QStringLiteral("*"), Qt::MatchWildcard);
   for (auto item : items) {
      item->setIcon(QIcon {QStringLiteral(":/icons/qtlogo.svg")});
   }

   // Left dockwidget 1
   _leftDockWidget1 = new QDockWidget {tr("ListWidget")};
   _leftDockWidget1->setObjectName(QStringLiteral("leftDockWidget1"));
   _leftDockWidget1->setWidget(listWidget);
   connect(_leftDockWidget1, &QDockWidget::topLevelChanged,
           this, &MainWindow::topLevelChanged);
   addDockWidget(Qt::LeftDockWidgetArea, _leftDockWidget1);

   // Left dockwidget 2
   _leftDockWidget2 = new QDockWidget {tr("Calendar")};
   _leftDockWidget2->setObjectName(QStringLiteral("leftDockWidget2"));
   auto calendarWidgetWrapper = new QWidget;
   calendarWidgetWrapper->setSizePolicy(QSizePolicy::Expanding,
                                        QSizePolicy::Expanding);
   auto layout = new QVBoxLayout {calendarWidgetWrapper};
   layout->addWidget(new QCalendarWidget);
   layout->addItem(new QSpacerItem {0, 0,
                                    QSizePolicy::Minimum,
                                    QSizePolicy::Expanding});
   _leftDockWidget2->setWidget(calendarWidgetWrapper);
   connect(_leftDockWidget2, &QDockWidget::topLevelChanged,
           this, &MainWindow::topLevelChanged);
   addDockWidget(Qt::LeftDockWidgetArea, _leftDockWidget2);

   // Right dockwidget
   _rightDockWidget = new QDockWidget {tr("WebEngineView")};
   _rightDockWidget->setObjectName(QStringLiteral("rightDockWidget"));
   _rightDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                     Qt::RightDockWidgetArea);
   auto webEngineView = new QWebEngineView;
   webEngineView->setSizePolicy(QSizePolicy::Expanding,
                                QSizePolicy::Expanding);
   webEngineView->setUrl(QStringLiteral("https://www.qt.io"));
   _rightDockWidget->setWidget(webEngineView);
   connect(_rightDockWidget, &QDockWidget::topLevelChanged,
           this, &MainWindow::topLevelChanged);
   addDockWidget(Qt::RightDockWidgetArea, _rightDockWidget);

   // View menu
   auto viewMenu = menuBar()->addMenu(tr("&View"));
   viewMenu->addActions(createPopupMenu()->actions());

   // Tabify action
   _tabifyAction = new QAction {tr("&Tabify"), this};
   _tabifyAction->setShortcut(Qt::CTRL + Qt::Key_T);
   _tabifyAction->setCheckable(true);
   connect(_tabifyAction, &QAction::toggled,
           this, &MainWindow::tabifyActionToogled);
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

void MainWindow::tabifyActionToogled(bool checked)
{
   if (checked) {
      addDockWidget(Qt::LeftDockWidgetArea, _leftDockWidget1);
      tabifyDockWidget(_leftDockWidget1, _leftDockWidget2);
      tabifyDockWidget(_leftDockWidget2, _rightDockWidget);
   } else {
      addDockWidget(Qt::LeftDockWidgetArea, _leftDockWidget1);
      addDockWidget(Qt::LeftDockWidgetArea, _leftDockWidget2);
      addDockWidget(Qt::RightDockWidgetArea, _rightDockWidget);
   }
}

void MainWindow::createStandardWidgets(const QString &title)
{
   // Set window title
   setWindowTitle(title);

   // Menu with simple menu item
   auto fileMenu = menuBar()->addMenu(tr("&File"));
   auto exitAction = fileMenu->addAction(
            QIcon {QStringLiteral(":/icons/exit.svg")}, tr("E&xit"),
            QApplication::instance(), &QApplication::exit,
            Qt::CTRL + Qt::Key_Q);

   // Main toolbar with simple action
   auto mainToolBar = addToolBar(tr("Main toolbar"));
   mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
   mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   mainToolBar->addAction(exitAction);

   // Central widget
   auto label = new QLabel {title};
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);
}

void MainWindow::writeSettings()
{
   QSettings settings;
   settings.setValue(QStringLiteral("geometry"), geometry());
   settings.setValue(QStringLiteral("windowState"), saveState());
   settings.setValue(QStringLiteral("menu/tabify"),
                     _tabifyAction->isChecked());
   settings.setValue(QStringLiteral("leftDock1Raised"),
                     !_leftDockWidget1->visibleRegion().isEmpty());
   settings.setValue(QStringLiteral("leftDock2Raised"),
                     !_leftDockWidget2->visibleRegion().isEmpty());
   settings.setValue(QStringLiteral("rightDockRaised"),
                     !_rightDockWidget->visibleRegion().isEmpty());
}

void MainWindow::readSettings()
{
   QSettings settings;
   setGeometry(settings.value(
                  QStringLiteral("geometry")).toRect());
   restoreState(settings.value(
                   QStringLiteral("windowState")).toByteArray());
   _tabifyAction->setChecked(
      settings.value(QStringLiteral("menu/tabify"), false).toBool());
   if (settings.value(QStringLiteral("leftDock1Raised")).toBool()) {
      _leftDockWidget1->raise();
   }
   if (settings.value(QStringLiteral("leftDock2Raised")).toBool()) {
      _leftDockWidget2->raise();
   }
   if (settings.value(QStringLiteral("rightDockRaised")).toBool()) {
      _rightDockWidget->raise();
   }
}
