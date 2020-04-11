#ifndef _IUICONTROLLER_H_
#define _IUICONTROLLER_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QObject>

namespace MyApp
{

class QTWIDGETSAPPINTERFACES_EXPORT IUIController : public QObject
{
   Q_OBJECT

public:
   explicit IUIController(QObject *parent = nullptr);
   ~IUIController() Q_DECL_OVERRIDE = default;

   virtual bool initialize() = 0;
};

} // namespace MyApp

#endif // _IUICONTROLLER_H_
