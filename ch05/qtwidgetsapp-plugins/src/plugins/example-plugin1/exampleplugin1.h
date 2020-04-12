#ifndef _EXAMPLEPLUGIN1_H_
#define _EXAMPLEPLUGIN1_H_

#include <QObject>

#include <interfaces/iplugin.h>

namespace MyApp
{

class ExamplePlugin1 : public QObject, public IPlugin
{
   Q_OBJECT
   Q_PLUGIN_METADATA(IID "com.packtpub.qt5.exampleplugin1"
                     FILE "exampleplugin1.json")
   Q_INTERFACES(MyApp::IPlugin)

public:
   ~ExamplePlugin1() Q_DECL_OVERRIDE = default;

   bool initialize() Q_DECL_OVERRIDE;
};

} // namespace MyApp

#endif // _EXAMPLEPLUGIN1_H_
