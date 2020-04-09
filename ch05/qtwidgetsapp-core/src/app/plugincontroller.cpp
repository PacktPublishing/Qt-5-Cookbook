#include "plugincontroller.h"

#include <QDebug>

namespace MyApp
{

PluginController::PluginController(QObject *parent)
   : IPluginController {parent}
{
}

bool PluginController::initialize()
{
   qDebug() << "Initializing PluginController";
   return true;
}

} // namespace MyApp
