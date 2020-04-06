#ifndef _EXAMPLEPLUGIN_H_
#define _EXAMPLEPLUGIN_H_

#include <interfaces/iplugin.h>

namespace QtWidgetsApp
{

class ExamplePlugin : public IPlugin
{
   Q_OBJECT
   Q_PLUGIN_METADATA(IID "com.packtpub.qt5.exampleplugin" FILE "exampleplugin.json")

public:
   explicit ExamplePlugin(QObject *parent = nullptr);
   virtual ~ExamplePlugin() Q_DECL_OVERRIDE;

   virtual bool initialize();
};

}

#endif // _EXAMPLEPLUGIN_H_
