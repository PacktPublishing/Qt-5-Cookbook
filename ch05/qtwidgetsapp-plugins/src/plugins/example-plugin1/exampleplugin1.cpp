#include "exampleplugin1.h"

#include <QAction>
#include <QDebug>

#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>

namespace MyApp
{

bool ExamplePlugin1::initialize()
{
   qDebug() << "Initializing ExamplePlugin1";

   auto uiController = ICore::self()->uiController();

   auto editAction = new QAction {
           QIcon {QStringLiteral(":/icons/item.svg")},
           QStringLiteral("Edit item")};
   uiController->addMenuItem(QStringLiteral("&Edit"), editAction);
   uiController->addToolButton(QStringLiteral("main-toolbar"),
                               editAction);
   connect (editAction, &QAction::triggered, this, []() {
       qDebug() << "Action triggered!"; });

   uiController->addToolButton(QStringLiteral("secondary-toolbar"),
            new QAction {QIcon {QStringLiteral(":/icons/item.svg")},
                         QStringLiteral("Action in another toolbar")},
            Qt::RightToolBarArea);
   uiController->addMenuItem(QStringLiteral("&File"),
            new QAction {QIcon {QStringLiteral(":/icons/item.svg")},
                         QStringLiteral("Another file item")});
   uiController->addMenuItem(QStringLiteral("&Help"),
            new QAction {QIcon {QStringLiteral(":/icons/item.svg")},
                         QStringLiteral("Another help item")});

   return true;
}

} // namespace MyApp
