#include "iplugin.h"

namespace QtWidgetsApp
{

IPlugin::~IPlugin()
{
}

IPlugin::IPlugin(QObject *parent)
   : QObject(parent)
{
}

}
