#include "exampleplugin1.h"

#include <QAction>
#include <QDebug>

#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>

namespace QtWidgetsApp
{

ExamplePlugin1::~ExamplePlugin1()
{
}

ExamplePlugin1::ExamplePlugin1(QObject *parent)
   : IPlugin(parent)
{
}

bool ExamplePlugin1::initialize()
{
   qDebug() << "Initializing ExamplePlugin1";

   auto uiController = ICore::self()->uiController();

   auto editAction = new QAction {QIcon {":/icons/item.svg"}, "Edit item"};
   uiController->addMenuItem("&Edit", editAction);
   uiController->addToolButton("main-toolbar", editAction);
   connect (editAction, &QAction::triggered, this, []() { qDebug() << "Action triggered!"; });

   uiController->addToolButton("secondary-toolbar", new QAction {QIcon {":/icons/item.svg"}, "Action in another toolbar"}, Qt::RightToolBarArea);
   uiController->addMenuItem("&File", new QAction {QIcon {":/icons/item.svg"}, "Another file item"});
   uiController->addMenuItem("&Help", new QAction {QIcon {":/icons/item.svg"}, "Another help item"});

   return true;
}

}
