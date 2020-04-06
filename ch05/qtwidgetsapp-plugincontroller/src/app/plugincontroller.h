#ifndef _PLUGINCONTROLLER_H_
#define _PLUGINCONTROLLER_H_

#include <interfaces/iplugincontroller.h>

namespace QtWidgetsApp
{

class QTWIDGETSAPPINTERFACES_EXPORT PluginController : public IPluginController
{
   Q_OBJECT

public:
   explicit PluginController(QObject *parent = nullptr);
   virtual ~PluginController() Q_DECL_OVERRIDE;

private:
   void loadPlugins();
};

}

#endif // _PLUGINCONTROLLER_H_
