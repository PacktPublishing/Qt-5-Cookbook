#include "uicontroller.h"

#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>

namespace QtWidgetsApp
{

UIController::UIController(QObject *parent)
   : IUIController(parent)
{
   qDebug() << "Initializing UIController";

   QMenu *fileMenu = nullptr;
   _mainWindow.menuBar()->addMenu(fileMenu = new QMenu("&File", _mainWindow.menuBar()));
   fileMenu->setObjectName("&File");
   _menuSeparators[QStringLiteral("&File")] = fileMenu->addSeparator();
   auto exitAction = fileMenu->addAction(
            QIcon {QStringLiteral(":/icons/exit.svg")}, tr("E&xit"),
            QApplication::instance(), &QApplication::exit,
            Qt::CTRL + Qt::Key_Q);
   auto mainToolBar = _mainWindow.addToolBar(QStringLiteral("main-toolbar"));
   mainToolBar->setObjectName(QStringLiteral("main-toolbar"));
   mainToolBar->addAction(exitAction);

   QMenu *helpMenu = nullptr;
   _helpAction = _mainWindow.menuBar()->addMenu(helpMenu = new QMenu("&Help", _mainWindow.menuBar()));
   helpMenu->setObjectName("&Help");
   _menuSeparators[QStringLiteral("&Help")] = helpMenu->addSeparator();
   helpMenu->addAction(new QAction {QIcon {":/icons/plugins.svg"}, "About &Plugins"});

   _mainWindow.showMaximized();

   // We will move the following sentences into a plugin in next recipe
   auto editAction = new QAction {QIcon {":/icons/item.svg"}, "Edit item"};
   addMenuItem("&Edit", editAction);
   addToolButton("main-toolbar", editAction);
   connect (editAction, &QAction::triggered, this, []() { qDebug() << "Action triggered!"; });

   addToolButton("secondary-toolbar", new QAction {QIcon {":/icons/item.svg"}, "Action in another toolbar"}, Qt::RightToolBarArea);
   addMenuItem("&File", new QAction {QIcon {":/icons/item.svg"}, "Another file item"});
   addMenuItem("&Help", new QAction {QIcon {":/icons/item.svg"}, "Another help item"});
}

UIController::~UIController()
{
}

void UIController::addMenuItem(const QString &menu, QAction *action)
{
   auto myMenu = _mainWindow.menuBar()->findChild<QMenu *>(menu);
   if (!myMenu) {
      _mainWindow.menuBar()->insertMenu(_helpAction, myMenu = new QMenu(menu, _mainWindow.menuBar()));
      myMenu->setObjectName(menu);
   }
   if (_menuSeparators.value(menu))
      myMenu->insertAction(_menuSeparators.value(menu), action);
   else
      myMenu->addAction(action);
}

void UIController::addToolButton(const QString &toolbar, QAction *action, Qt::ToolBarArea area)
{
   auto myToolBar = _mainWindow.findChild<QToolBar *>(toolbar);
   if (!myToolBar) {
      _mainWindow.addToolBar(area, myToolBar = new QToolBar(toolbar));
      myToolBar->setObjectName(toolbar);
   }
   myToolBar->addAction(action);
}

}
