#ifndef _IUICONTROLLER_H_
#define _IUICONTROLLER_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QObject>

class QAction;

namespace QtWidgetsApp
{

class QTWIDGETSAPPINTERFACES_EXPORT IUIController : public QObject
{
   Q_OBJECT

public:
   virtual ~IUIController() Q_DECL_OVERRIDE;

   virtual void addMenuItem(const QString &menu, QAction *action) = 0;
   virtual void addToolButton(const QString &objectName, QAction *action) = 0;

protected:
   explicit IUIController(QObject *parent = nullptr);
};

}

#endif // _IUICONTROLLER_H_
