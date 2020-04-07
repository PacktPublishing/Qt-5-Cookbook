#include "plugincontroller.h"

#include <QCoreApplication>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

PluginController::PluginController(QObject *parent) : QObject(parent)
{
   qRegisterMetaType<PluginController *>("PluginController *");

#ifdef Q_OS_ANDROID
   QDir dir("assets:/plugins");
#else
   QDir dir(qApp->applicationDirPath());
   dir.cd("plugins");
#endif
   QString contents;
   QJsonArray mergedArray;
   foreach(const QString &fileName, dir.entryList(QStringList() << "*.json")) {
      QFile file(dir.absoluteFilePath(fileName));
      file.open(QIODevice::ReadOnly);
      QJsonObject jsonObject = QJsonDocument::fromJson(file.readAll()).object();
      QDir pluginDir(dir);
      pluginDir.cd(fileName.split('.').first());
#ifdef Q_OS_ANDROID
      jsonObject["pluginName"] = fileName.split('.').first();
#else
      jsonObject["pluginName"] = pluginDir.absolutePath();
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
