#include "uicontroller.h"

#include <QDebug>

namespace QtWidgetsApp
{

UIController::UIController(QObject *parent)
   : IUIController(parent)
{
   qDebug() << "Initializing UIController";
}

UIController::~UIController()
{
}

bool UIController::initialize()
{
   return true;
}

}
