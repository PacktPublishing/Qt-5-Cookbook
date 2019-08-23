#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   // Set window attributes
   setWindowTitle(tr("Menus and Toolbars Example Application"));
   resize(640, 480);

   // Menu with simple menu item
   auto fileMenu = menuBar()->addMenu(tr("&File"));
   auto exitAction = fileMenu->addAction(
            QIcon(QStringLiteral(":/icons/exit.svg")), tr("E&xit"),
            QApplication::instance(), &QApplication::exit,
            Qt::CTRL + Qt::Key_Q);

   // Main toolbar with simple action
   auto mainToolBar = addToolBar(tr("Main toolbar"));
   mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   mainToolBar->addAction(exitAction);

   // Central widget
   auto label = new QLabel {
         QStringLiteral("Menus and Toolbars Example Application")};
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);

   // Secondary tool bar with action groups
   auto alignHActionGroup = createActionGroup({
      { QStringLiteral(":/icons/h-left.svg"),   tr("Align &left") },
      { QStringLiteral(":/icons/h-center.svg"), tr("Align &center") },
      { QStringLiteral(":/icons/h-right.svg"),  tr("Align &right") }
   });
   auto alignVActionGroup = createActionGroup({
      { QStringLiteral(":/icons/v-top.svg"),    tr("Align &top") },
      { QStringLiteral(":/icons/v-center.svg"), tr("Align ce&nter") },
      { QStringLiteral(":/icons/v-bottom.svg"), tr("Align &bottom") }
   });
   auto secondaryToolBar = new QToolBar { tr("Secondary toolbar") };
   secondaryToolBar->addActions(alignHActionGroup->actions());
   secondaryToolBar->addSeparator();
   secondaryToolBar->addActions(alignVActionGroup->actions());
   addToolBar(Qt::RightToolBarArea, secondaryToolBar);

   // Toolbutton with menu
   auto alignMenu = new QMenu;
   alignMenu->addActions(alignHActionGroup->actions());
   alignMenu->addSeparator();
   alignMenu->addActions(alignVActionGroup->actions());
   auto alignAction = mainToolBar->addAction(
            QIcon(QStringLiteral(":/icons/configure.svg")),
            QStringLiteral("&Align"));
   alignAction->setMenu(alignMenu);
   (qobject_cast<QToolButton *>(
            mainToolBar->widgetForAction(alignAction))
         )->setPopupMode(QToolButton::MenuButtonPopup);

   // Menu with submenu
   auto formatMenu = menuBar()->addMenu(tr("F&ormat"));
   formatMenu->addMenu(alignMenu);

   // Status bar
   statusBar()->addPermanentWidget(new QLabel { tr("Ready!") }, 1);
}

QActionGroup *MainWindow::createActionGroup(
   const QVector<QPair<QString, QString>> &data)
{
   auto actionGroup = new QActionGroup { this };
   for (const auto &pair : data) {
      actionGroup->addAction(QIcon(pair.first),
                             pair.second)->setCheckable(true);
   }
   actionGroup->actions().constFirst()->setChecked(true);
   return actionGroup;
}
