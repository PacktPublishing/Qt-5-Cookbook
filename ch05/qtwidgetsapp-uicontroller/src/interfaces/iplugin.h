#ifndef _IPLUGIN_H_
#define _IPLUGIN_H_

#include <QtPlugin>

#include <interfaces/qtwidgetsappinterfacesexport.h>

namespace MyApp
{

class QTWIDGETSAPPINTERFACES_EXPORT IPlugin
{
public:
   virtual ~IPlugin() = default;

   virtual bool initialize() = 0;
};

} // namespace MyApp

#define IPlugin_iid "com.packtpub.qt5.iplugin/1.0"
Q_DECLARE_INTERFACE(MyApp::IPlugin, IPlugin_iid)

#endif // _IPLUGIN_H_
