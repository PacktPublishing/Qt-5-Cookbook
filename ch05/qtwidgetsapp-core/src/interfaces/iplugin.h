#ifndef _IPLUGIN_H_
#define _IPLUGIN_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QObject>

namespace QtWidgetsApp
{

class QTWIDGETSAPPINTERFACES_EXPORT IPlugin : public QObject
{
   Q_OBJECT

public:
   virtual ~IPlugin() Q_DECL_OVERRIDE;

   virtual bool initialize() = 0;

protected:
   explicit IPlugin(QObject *parent = nullptr);
};

}

#endif // _IPLUGIN_H_
