#ifndef PLUGINCONTROLLER_H
#define PLUGINCONTROLLER_H

#include <QJsonArray>
#include <QObject>

class PluginController : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QJsonArray pluginMetaData READ pluginMetaData NOTIFY pluginMetaDataChanged)

public:
   explicit PluginController(QObject *parent = nullptr);

   QJsonArray pluginMetaData() const;

Q_SIGNALS:
   void pluginMetaDataChanged();

private:
   QJsonArray _pluginMetaData;
};

#endif // PLUGINCONTROLLER_H
