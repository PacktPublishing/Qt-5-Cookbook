#include "mainwindow.h"

#include <QApplication>
#include <QCalendarWidget>
#include <QDockWidget>
#include <QLabel>
#include <QListWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   createStandardWidgets(tr("DockWidgets Example Application"));

   // A list widget
   auto listWidget = new QListWidget;
   listWidget->addItems({
      tr("First item"), tr("Second item"), tr("Third item")});
   const QList<QListWidgetItem *> &items = listWidget->findItems(
            QStringLiteral("*"),Qt::MatchWildcard);
   for (auto item : items) {
      item->setIcon(QIcon {QStringLiteral(":/icons/qtlogo.svg")});
   }

   // Left dockwidget 1
   _leftDockWidget1 = new QDockWidget {tr("ListWidget")};
   _leftDockWidget1->setWidget(listWidget);
   connect(_leftDockWidget1, &QDockWidget::topLevelChanged,
           this, &MainWindow::topLevelChanged);
   addDockWidget(Qt::LeftDockWidgetArea, _leftDockWidget1);

   // Left dockwidget 2
   _leftDockWidget2 = new QDockWidget {tr("Calendar")};
   auto calendarWidgetWrapper = new QWidget;
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
   _rightDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                     Qt::RightDockWidgetArea);
   auto webEngineView = new QWebEngineView;
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
   mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   mainToolBar->addAction(exitAction);

   // Central widget
   auto label = new QLabel {title};
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);
}
