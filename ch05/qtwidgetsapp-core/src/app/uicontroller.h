#ifndef _UICONTROLLER_H_
#define _UICONTROLLER_H_

#include <interfaces/iuicontroller.h>

namespace MyApp
{

class QTWIDGETSAPPINTERFACES_EXPORT UIController
        : public IUIController
{
   Q_OBJECT

public:
   explicit UIController(QObject *parent = nullptr);
   ~UIController() Q_DECL_OVERRIDE = default;

   bool initialize() Q_DECL_OVERRIDE;
};

} // namespace MyApp

#endif // _UICONTROLLER_H_
