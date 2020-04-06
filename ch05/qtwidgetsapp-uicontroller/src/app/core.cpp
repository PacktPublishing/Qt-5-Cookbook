#include "core.h"

#include "plugincontroller.h"
#include "uicontroller.h"

namespace QtWidgetsApp
{

Core::~Core()
{
}

bool Core::initialize()
{
   if (_self)
      return true;

   new Core;

   return true;
}

QtWidgetsApp::IUIController *Core::uiController() const
{
   return _uiController;
}

QtWidgetsApp::IPluginController *Core::pluginController() const
{
   return _pluginController;
}

Core::Core(QObject *parent)
   : ICore(parent)
{
   _self = this;
   _uiController = new UIController(this);
   _pluginController = new PluginController(this);
}

}
