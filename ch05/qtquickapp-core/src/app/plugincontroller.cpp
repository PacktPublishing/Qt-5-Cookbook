#include "plugincontroller.h"

PluginController::PluginController(QObject *parent) : QObject {parent}
{
   qRegisterMetaType<PluginController *>("PluginController *");
}
