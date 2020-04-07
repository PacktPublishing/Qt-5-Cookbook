#ifndef _EXAMPLEPLUGIN2_H_
#define _EXAMPLEPLUGIN2_H_

#include <interfaces/iplugin.h>

namespace QtWidgetsApp
{

class ExamplePlugin2 : public IPlugin
{
   Q_OBJECT
   Q_PLUGIN_METADATA(IID "com.packtpub.qt5.exampleplugin2" FILE "exampleplugin2.json")

public:
   explicit ExamplePlugin2(QObject *parent = nullptr);
   virtual ~ExamplePlugin2() Q_DECL_OVERRIDE;

   virtual bool initialize();
};

}

#endif // _EXAMPLEPLUGIN2_H_
