#ifndef _IPLUGIN_H_
#define _IPLUGIN_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QObject>

namespace MyApp
{

class QTWIDGETSAPPINTERFACES_EXPORT IPlugin : public QObject
{
   Q_OBJECT

public:
   explicit IPlugin(QObject *parent = nullptr);
   ~IPlugin() Q_DECL_OVERRIDE = default;

   virtual bool initialize() = 0;
};

} // namespace MyApp

#endif // _IPLUGIN_H_
