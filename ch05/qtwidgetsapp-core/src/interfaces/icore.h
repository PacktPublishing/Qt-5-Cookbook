#ifndef _ICORE_H_
#define _ICORE_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QObject>

namespace MyApp
{

class IPluginController;
class IUIController;

class QTWIDGETSAPPINTERFACES_EXPORT ICore : public QObject
{
   Q_OBJECT

public:
   ~ICore() Q_DECL_OVERRIDE = default;

   static ICore *self();

   virtual MyApp::IUIController *uiController() const = 0;
   virtual MyApp::IPluginController *pluginController() const = 0;

protected:
   explicit ICore(QObject *parent = nullptr);
   static ICore *_self;
};

} // namespace MyApp

#endif // _ICORE_H_
