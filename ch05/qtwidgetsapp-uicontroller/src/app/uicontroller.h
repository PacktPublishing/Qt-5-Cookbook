#ifndef _UICONTROLLER_H_
#define _UICONTROLLER_H_

#include <interfaces/iuicontroller.h>

#include <QMainWindow>

namespace QtWidgetsApp
{

class QTWIDGETSAPPINTERFACES_EXPORT UIController : public IUIController
{
   Q_OBJECT

public:
   explicit UIController(QObject *parent = nullptr);
   virtual ~UIController() Q_DECL_OVERRIDE;

   virtual void addMenuItem(const QString &menu, QAction *action) Q_DECL_OVERRIDE;
   virtual void addToolButton(const QString &objectName, QAction *action) Q_DECL_OVERRIDE;

private:
   QMainWindow _mainWindow;
};

}

#endif // _UICONTROLLER_H_
