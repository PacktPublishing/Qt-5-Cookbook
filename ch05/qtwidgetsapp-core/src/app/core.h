#ifndef _CORE_H_
#define _CORE_H_

#include <interfaces/icore.h>

namespace MyApp
{

class QTWIDGETSAPPINTERFACES_EXPORT Core : public ICore
{
   Q_OBJECT

public:
   ~Core() Q_DECL_OVERRIDE = default;

   static bool initialize();

   MyApp::IUIController *uiController() const Q_DECL_OVERRIDE;
   MyApp::IPluginController *pluginController() const Q_DECL_OVERRIDE;

private:
   explicit Core(QObject *parent = nullptr);

   MyApp::IUIController *_uiController;
   MyApp::IPluginController *_pluginController;
};

} // namespace MyApp

#endif // _CORE_H_
