#include "plugincontroller.h"

#include <QDebug>

namespace MyApp
{

PluginController::PluginController(QObject *parent)
   : IPluginController {parent}
{
   qDebug() << "Initializing PluginController";
}

bool PluginController::initialize()
{
   return true;
}

} // namespace MyApp
