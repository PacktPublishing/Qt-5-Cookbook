#include "uicontroller.h"

#include <QDebug>

namespace MyApp
{

UIController::UIController(QObject *parent) : IUIController {parent}
{
   qDebug() << "Initializing UIController";
}

bool UIController::initialize()
{
   return true;
}

} // namespace MyApp
