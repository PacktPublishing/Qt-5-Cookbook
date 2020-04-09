#include "exampleplugin2.h"

#include <QCalendarWidget>
#include <QDebug>
#include <QSpacerItem>
#include <QVBoxLayout>

#include <interfaces/icore.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/iuicontroller.h>

namespace MyApp
{

ExamplePlugin2::ExamplePlugin2(QObject *parent)
   : IPlugin(parent)
{
}

bool ExamplePlugin2::initialize()
{
   qDebug() << "Initializing ExamplePlugin2";

   auto uiController = ICore::self()->uiController();

   auto calendarWidgetWrapper = new QWidget;
   auto layout = new QVBoxLayout {calendarWidgetWrapper};
   layout->addWidget(new QCalendarWidget);
   layout->addItem(new QSpacerItem {0, 0,
                                    QSizePolicy::Minimum,
                                    QSizePolicy::Expanding});

   uiController->addDockWidget(calendarWidgetWrapper);

   connect(ICore::self()->pluginController(),
           &IPluginController::allPluginsLoaded, this, []() {
      qDebug() << "All plugins have been loaded!";
   });

   return true;
}

} // namespace MyApp
