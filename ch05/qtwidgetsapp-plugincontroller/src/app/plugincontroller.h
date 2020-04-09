#ifndef _PLUGINCONTROLLER_H_
#define _PLUGINCONTROLLER_H_

#include <interfaces/iplugincontroller.h>

namespace MyApp
{

class QTWIDGETSAPPINTERFACES_EXPORT PluginController
        : public IPluginController
{
   Q_OBJECT

public:
   explicit PluginController(QObject *parent = nullptr);
   ~PluginController() Q_DECL_OVERRIDE = default;

   bool initialize() Q_DECL_OVERRIDE;

private:
   void loadPlugins();
};

} // namespace MyApp

#endif // _PLUGINCONTROLLER_H_
