#include "iplugincontroller.h"

namespace QtWidgetsApp
{

IPluginController::~IPluginController()
{
}

IPluginController::IPluginController(QObject *parent)
   : QObject(parent)
{
}

}
