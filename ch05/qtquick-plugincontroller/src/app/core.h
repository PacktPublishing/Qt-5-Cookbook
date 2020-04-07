#ifndef CORE_H
#define CORE_H

#include <QObject>

class PluginController;

class Core : public QObject
{
   Q_OBJECT
   Q_PROPERTY(PluginController * pluginController
              READ pluginController CONSTANT)

public:
   static Core *self();

   PluginController *pluginController() const;

Q_SIGNALS:

private:
   explicit Core(QObject *parent = nullptr);
   static Core *_self;

   PluginController *_pluginController;
};

#endif // CORE_H
