#include "uicontroller.h"

#include <QDebug>

namespace MyApp
{

UIController::UIController(QObject *parent) : IUIController {parent}
{
}

bool UIController::initialize()
{
   qDebug() << "Initializing UIController";
   return true;
}

} // namespace MyApp
