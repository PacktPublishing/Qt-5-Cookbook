#ifndef _PLUGINCONTROLLER_H_
#define _PLUGINCONTROLLER_H_

#include <interfaces/iplugincontroller.h>

namespace MyApp
{

class PluginController : public IPluginController
{
   Q_OBJECT

public:
   explicit PluginController(QObject *parent = nullptr);
   ~PluginController() Q_DECL_OVERRIDE = default;

   bool initialize() Q_DECL_OVERRIDE;
};

} // namespace MyApp

#endif // _PLUGINCONTROLLER_H_
