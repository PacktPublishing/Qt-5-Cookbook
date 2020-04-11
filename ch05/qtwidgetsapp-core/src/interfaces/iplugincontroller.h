#ifndef _IPLUGINCONTROLLER_H_
#define _IPLUGINCONTROLLER_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QObject>

namespace MyApp
{

class QTWIDGETSAPPINTERFACES_EXPORT IPluginController : public QObject
{
   Q_OBJECT

public:
   explicit IPluginController(QObject *parent = nullptr);
   ~IPluginController() Q_DECL_OVERRIDE = default;

   virtual bool initialize() = 0;
};

} // namespace MyApp

#endif // _IPLUGINCONTROLLER_H_
