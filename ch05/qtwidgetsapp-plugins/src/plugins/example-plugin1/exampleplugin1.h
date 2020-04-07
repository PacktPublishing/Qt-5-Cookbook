#ifndef _EXAMPLEPLUGIN1_H_
#define _EXAMPLEPLUGIN1_H_

#include <interfaces/iplugin.h>

namespace QtWidgetsApp
{

class ExamplePlugin1 : public IPlugin
{
   Q_OBJECT
   Q_PLUGIN_METADATA(IID "com.packtpub.qt5.exampleplugin1"
                     FILE "exampleplugin1.json")

public:
   explicit ExamplePlugin1(QObject *parent = nullptr);
   virtual ~ExamplePlugin1() Q_DECL_OVERRIDE;

   virtual bool initialize();
};

}

#endif // _EXAMPLEPLUGIN1_H_
