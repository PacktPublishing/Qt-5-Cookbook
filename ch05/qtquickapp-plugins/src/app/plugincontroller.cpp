#include "plugincontroller.h"

#include <QCoreApplication>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>

PluginController::PluginController(QObject *parent) : QObject {parent}
{
   qRegisterMetaType<PluginController *>("PluginController *");

#ifdef Q_OS_ANDROID
   QDir dir {"assets:/plugins"};
#else
   QDir dir {qApp->applicationDirPath()};
   dir.cd(QStringLiteral("plugins"));
#endif
   QJsonArray mergedArray;
   const auto &entryList = dir.entryList(
               QStringList {} << QStringLiteral("*.json"));
   for(const auto &fileName : entryList) {
      QFile file {dir.absoluteFilePath(fileName)};
      file.open(QIODevice::ReadOnly);
      QJsonObject jsonObject =
              QJsonDocument::fromJson(file.readAll()).object();
      QDir pluginDir {dir};
      pluginDir.cd(fileName.split('.').first());
#ifdef Q_OS_ANDROID
      jsonObject[QLatin1String("pluginPath")] =
              fileName.split('.').first();
#else
      jsonObject[QLatin1String("pluginPath")] =
             QUrl::fromLocalFile(pluginDir.absolutePath()).toString();
#endif
      mergedArray.append(jsonObject);
      file.close();
   }
   _pluginMetaData = mergedArray;
}

QJsonArray PluginController::pluginMetaData() const
{
   return _pluginMetaData;
}
