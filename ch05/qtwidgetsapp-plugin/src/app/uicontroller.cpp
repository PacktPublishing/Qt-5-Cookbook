#include "uicontroller.h"

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
   _mainWindow.show();
}

UIController::~UIController()
{
}

void UIController::addMenuItem(const QString &menu, QAction *action)
{
   QMenu *myMenu = nullptr;
   for (auto menuBarAction : _mainWindow.menuBar()->actions())
      if (menuBarAction->menu()->title() == menu)
         myMenu = menuBarAction->menu();
   if (!myMenu)
      _mainWindow.menuBar()->addMenu(myMenu = new QMenu(menu));
   myMenu->addAction(action);
}

void UIController::addToolButton(const QString &objectName, QAction *action)
{
   QToolBar *myToolBar = nullptr;
   for (auto toolBar : _mainWindow.findChildren<QToolBar *>())
      if (toolBar->windowTitle() == objectName)
         myToolBar = toolBar;
   if (!myToolBar)
      _mainWindow.addToolBar(myToolBar = new QToolBar(objectName));
   myToolBar->addAction(action);
}

}
