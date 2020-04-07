#ifndef _IPLUGINCONTROLLER_H_
#define _IPLUGINCONTROLLER_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QHash>
#include <QJsonObject>
#include <QObject>

namespace QtWidgetsApp
{

class IPlugin;

class QTWIDGETSAPPINTERFACES_EXPORT IPluginController : public QObject
{
   Q_OBJECT

public:
   virtual ~IPluginController() Q_DECL_OVERRIDE;

   virtual bool initialize() = 0;

   template<typename T = IPlugin>
   QHash<T *, QJsonObject> loadedPlugins() const {
      QHash<T *, QJsonObject> loadedPluginsByType;
      T *pluginOfType = nullptr;
      for (const auto &plugin : _loadedPlugins.keys())
         if (pluginOfType = dynamic_cast<T *>(plugin))
            loadedPluginsByType[pluginOfType] = _loadedPlugins[plugin];
      return loadedPluginsByType;
   }

Q_SIGNALS:
   void allPluginsLoaded();

protected:
   explicit IPluginController(QObject *parent = nullptr);

   QHash<IPlugin *, QJsonObject> _loadedPlugins;
};

}

#endif // _IPLUGINCONTROLLER_H_
