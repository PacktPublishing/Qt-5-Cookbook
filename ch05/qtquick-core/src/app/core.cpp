#include "core.h"

#include "plugincontroller.h"

Core *Core::_self = nullptr;

Core::Core(QObject *parent) : QObject(parent)
{
   _pluginController = new PluginController(this);
}

Core *Core::self()
{
   if (_self == nullptr)
      _self = new Core;
   return _self;
}

PluginController *Core::pluginController() const
{
   return _pluginController;
}
