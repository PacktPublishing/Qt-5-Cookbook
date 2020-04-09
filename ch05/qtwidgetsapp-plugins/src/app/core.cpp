#include "core.h"

#include "plugincontroller.h"
#include "uicontroller.h"

namespace MyApp
{

bool Core::initialize()
{
   if (!_self) {
       new Core;
   }

   return true;
}

MyApp::IUIController *Core::uiController() const
{
   return _uiController;
}

MyApp::IPluginController *Core::pluginController() const
{
   return _pluginController;
}

Core::Core(QObject *parent) : ICore(parent)
{
   _self = this;
   _uiController = new UIController {this};
   _pluginController = new PluginController {this};
   _uiController->initialize();
   _pluginController->initialize();
}

} // namespace MyApp
