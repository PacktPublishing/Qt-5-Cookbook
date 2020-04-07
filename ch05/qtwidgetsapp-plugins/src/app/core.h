#ifndef _CORE_H_
#define _CORE_H_

#include <interfaces/icore.h>

namespace QtWidgetsApp
{

class QTWIDGETSAPPINTERFACES_EXPORT Core : public ICore
{
   Q_OBJECT

public:
   virtual ~Core() Q_DECL_OVERRIDE;

   static bool initialize();

   virtual QtWidgetsApp::IUIController *uiController() const;
   virtual QtWidgetsApp::IPluginController *pluginController() const;

private:
   explicit Core(QObject *parent = nullptr);

   QtWidgetsApp::IUIController *_uiController;
   QtWidgetsApp::IPluginController *_pluginController;
};

}

#endif // _CORE_H_
