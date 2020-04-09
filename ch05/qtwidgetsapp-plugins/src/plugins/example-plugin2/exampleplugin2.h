#ifndef _EXAMPLEPLUGIN2_H_
#define _EXAMPLEPLUGIN2_H_

#include <interfaces/iplugin.h>

namespace MyApp
{

class ExamplePlugin2 : public IPlugin
{
   Q_OBJECT
   Q_PLUGIN_METADATA(IID "com.packtpub.qt5.exampleplugin2"
                     FILE "exampleplugin2.json")

public:
   explicit ExamplePlugin2(QObject *parent = nullptr);
   ~ExamplePlugin2() Q_DECL_OVERRIDE = default;

   bool initialize() Q_DECL_OVERRIDE;
};

} // namespace MyApp

#endif // _EXAMPLEPLUGIN2_H_
