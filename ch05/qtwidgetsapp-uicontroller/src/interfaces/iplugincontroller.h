#ifndef _IPLUGINCONTROLLER_H_
#define _IPLUGINCONTROLLER_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QHash>
#include <QJsonObject>
#include <QObject>

namespace MyApp
{

class IPlugin;

class QTWIDGETSAPPINTERFACES_EXPORT IPluginController : public QObject
{
   Q_OBJECT

public:
   ~IPluginController() Q_DECL_OVERRIDE = default;

   virtual bool initialize() = 0;

   template<typename T = IPlugin>
   QHash<T *, QJsonObject> loadedPlugins() const {
      QHash<T *, QJsonObject> pluginsByType;
      T *pluginOfType = nullptr;
      const QList<IPlugin *> &keyList = _loadedPlugins.keys();
      for (const auto &plugin : keyList) {
         if ((pluginOfType = qobject_cast<T *>(plugin))) {
            pluginsByType[pluginOfType] = _loadedPlugins[plugin];
         }
      }
      return pluginsByType;
   }

Q_SIGNALS:
   void allPluginsLoaded();

protected:
   explicit IPluginController(QObject *parent = nullptr);

   QHash<IPlugin *, QJsonObject> _loadedPlugins;
};

} // namespace MyApp

#endif // _IPLUGINCONTROLLER_H_
