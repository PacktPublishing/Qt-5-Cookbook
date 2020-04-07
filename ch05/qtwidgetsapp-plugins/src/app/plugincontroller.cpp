#include "plugincontroller.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>

#include "../interfaces/iplugin.h"

namespace QtWidgetsApp
{

PluginController::PluginController(QObject *parent)
   : IPluginController(parent)
{
   qDebug() << "Initializing PluginController";
}

PluginController::~PluginController()
{
}

bool PluginController::initialize()
{
   loadPlugins();
   return true;
}

void PluginController::loadPlugins()
{
   auto pluginsDir = QDir(qApp->applicationDirPath());
   #if defined(Q_OS_WIN)
   if (pluginsDir.dirName().toLower() == "debug" ||
           pluginsDir.dirName().toLower() == "release")
      pluginsDir.cdUp();
   #elif defined(Q_OS_MAC)
   if (pluginsDir.dirName() == "MacOS") {
      pluginsDir.cdUp();
      pluginsDir.cdUp();
      pluginsDir.cdUp();
   }
   #endif
   if (!pluginsDir.cd("plugins")) {
       qDebug("Plugin directory does not exist! Creating...");
       pluginsDir.mkdir ("plugins");
       pluginsDir.cd("plugins");
   }
   const auto entryList = pluginsDir.entryList(QDir::Files);
   qDebug() << entryList.count() << "plugins found!" << entryList;
   for (const QString &fileName : entryList) {
      qDebug() << "Loading plugin" << fileName;
      QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
      auto pluginObject = loader.instance();
      if (pluginObject) {
         auto plugin = qobject_cast<IPlugin *>(pluginObject);
         if (plugin) {
            qDebug() << "Initializing plugin" << fileName;
            plugin->initialize();
            _loadedPlugins[plugin] = loader.metaData();
         } else
             qDebug() << "Plugin" << fileName << "is not an IPlugin";
      } else qDebug() << "Error when loading plugin" << fileName;
   }
   Q_EMIT allPluginsLoaded();
}

}
