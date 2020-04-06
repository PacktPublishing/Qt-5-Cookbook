#ifndef _IPLUGINCONTROLLER_H_
#define _IPLUGINCONTROLLER_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QHash>
#include <QObject>

namespace QtWidgetsApp
{

class IPlugin;

class QTWIDGETSAPPINTERFACES_EXPORT IPluginController : public QObject
{
   Q_OBJECT

public:
   virtual ~IPluginController() Q_DECL_OVERRIDE;

   template<typename T = IPlugin>
   QHash<QString, T *> loadedPlugins() const {
      QHash<QString, T *> loadedPluginsByType;
      T *pluginOfType = nullptr;
      for (const auto &fileName : _loadedPlugins.keys())
         if ((pluginOfType = dynamic_cast<T *>(_loadedPlugins[fileName])))
            loadedPluginsByType[fileName] = pluginOfType;
      return loadedPluginsByType;
   }

protected:
   explicit IPluginController(QObject *parent = nullptr);

   QHash<QString, IPlugin *> _loadedPlugins;
};

}

#endif // _IPLUGINCONTROLLER_H_
