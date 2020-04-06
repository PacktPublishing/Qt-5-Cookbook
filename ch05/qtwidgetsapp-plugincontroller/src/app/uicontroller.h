#ifndef _UICONTROLLER_H_
#define _UICONTROLLER_H_

#include <interfaces/iuicontroller.h>

namespace QtWidgetsApp
{

class QTWIDGETSAPPINTERFACES_EXPORT UIController : public IUIController
{
   Q_OBJECT

public:
   explicit UIController(QObject *parent = nullptr);
   virtual ~UIController() Q_DECL_OVERRIDE;
};

}

#endif // _UICONTROLLER_H_
