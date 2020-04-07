#ifndef _IPLUGINCONTROLLER_H_
#define _IPLUGINCONTROLLER_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QObject>

namespace QtWidgetsApp
{

class QTWIDGETSAPPINTERFACES_EXPORT IPluginController : public QObject
{
   Q_OBJECT

public:
   virtual ~IPluginController() Q_DECL_OVERRIDE;

   virtual bool initialize() = 0;

protected:
   explicit IPluginController(QObject *parent = nullptr);
};

}

#endif // _IPLUGINCONTROLLER_H_
