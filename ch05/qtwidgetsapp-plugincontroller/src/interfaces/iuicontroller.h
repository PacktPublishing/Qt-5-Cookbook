#ifndef _IUICONTROLLER_H_
#define _IUICONTROLLER_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QObject>

namespace QtWidgetsApp
{

class QTWIDGETSAPPINTERFACES_EXPORT IUIController : public QObject
{
   Q_OBJECT

public:
   virtual ~IUIController() Q_DECL_OVERRIDE;

protected:
   explicit IUIController(QObject *parent = nullptr);
};

}

#endif // _IUICONTROLLER_H_
