#ifndef _ICORE_H_
#define _ICORE_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QObject>

namespace QtWidgetsApp
{

class IPluginController;
class IUIController;

class QTWIDGETSAPPINTERFACES_EXPORT ICore : public QObject
{
   Q_OBJECT

public:
   virtual ~ICore() Q_DECL_OVERRIDE;

   static ICore *self();

   virtual QtWidgetsApp::IUIController *uiController() const = 0;
   virtual QtWidgetsApp::IPluginController *pluginController() const = 0;

protected:
   explicit ICore(QObject *parent = nullptr);
   static ICore *_self;
};

}

#endif // _ICORE_H_
