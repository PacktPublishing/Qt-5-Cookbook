#ifndef PLUGINCONTROLLER_H
#define PLUGINCONTROLLER_H

#include <QObject>

class PluginController : public QObject
{
   Q_OBJECT

public:
   explicit PluginController(QObject *parent = nullptr);

};

#endif // PLUGINCONTROLLER_H
