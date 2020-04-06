#include "exampleplugin.h"

#include <QAction>
#include <QDebug>

#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>

namespace QtWidgetsApp
{

ExamplePlugin::~ExamplePlugin()
{
}

ExamplePlugin::ExamplePlugin(QObject *parent)
   : IPlugin(parent)
{
}

bool ExamplePlugin::initialize()
{
   qDebug() << "Initializing ExamplePlugin";
   auto uiController = ICore::self()->uiController();
   auto myAction = new QAction {QIcon {":/icons/configure.svg"}, "&Configure"};
   uiController->addMenuItem("&Edit", myAction);
   uiController->addToolButton("main-toolbar", myAction);
   connect (myAction, &QAction::triggered, this, []() { qDebug() << "Action triggered!"; });

   return true;
}

}
