#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QToolButton>

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

   // Secondary tool bar with action groups
   auto alignHorizontalActionGroup = createActionGroup({
      { QLatin1String(":/icons/horizontal-left.svg"),   tr("Align &left") },
      { QLatin1String(":/icons/horizontal-center.svg"), tr("Align &center") },
      { QLatin1String(":/icons/horizontal-right.svg"),  tr("Align &right") }
   });
   auto alignVerticalActionGroup = createActionGroup({
      { QLatin1String(":/icons/vertical-top.svg"),    tr("Align &top") },
      { QLatin1String(":/icons/vertical-center.svg"), tr("Align ce&nter") },
      { QLatin1String(":/icons/vertical-bottom.svg"), tr("Align &bottom") }
   });
   auto secondaryToolBar = new QToolBar { tr("Secondary toolbar") };
   secondaryToolBar->addActions(alignHorizontalActionGroup->actions());
   secondaryToolBar->addSeparator();
   secondaryToolBar->addActions(alignVerticalActionGroup->actions());
   addToolBar(Qt::RightToolBarArea, secondaryToolBar);

   // Toolbutton with menu
   auto alignMenu = new QMenu;
   alignMenu->addActions(alignHorizontalActionGroup->actions());
   alignMenu->addSeparator();
   alignMenu->addActions(alignVerticalActionGroup->actions());
   auto alignAction = mainToolBar->addAction(QIcon(QLatin1String(":/icons/configure.svg")), QStringLiteral("&Align"));
   alignAction->setMenu(alignMenu);
   (qobject_cast<QToolButton *>(mainToolBar->widgetForAction(alignAction)))->setPopupMode(QToolButton::MenuButtonPopup);

   // Menu with submenu
   auto formatMenu = menuBar()->addMenu(tr("F&ormat"));
   formatMenu->addMenu(alignMenu);

   // Status bar
   statusBar()->addPermanentWidget(new QLabel { tr("Ready!") }, 1);

   // Central widget
   auto label = new QLabel { QStringLiteral("Hello with menus and toolbars!") };
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);

   // Set window attributes
   setWindowTitle(tr("Menus and Toolbars Example Application"));
   resize(640, 480);

   dumpObjectTree();
}

QActionGroup *MainWindow::createActionGroup(const QVector<QPair<QString, QString>> &data)
{
   auto actionGroup = new QActionGroup { this };
   for (const auto &pair : data) {
      actionGroup->addAction(QIcon(pair.first), pair.second)->setCheckable(true);
   }
   actionGroup->actions().constFirst()->setChecked(true);
   return actionGroup;
}
