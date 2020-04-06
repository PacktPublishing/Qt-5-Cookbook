#include "plugincontroller.h"

#include <QDebug>

namespace QtWidgetsApp
{

PluginController::PluginController(QObject *parent)
   : IPluginController(parent)
{
   qDebug() << "Initializing PluginController";
}

PluginController::~PluginController()
{
}

}
