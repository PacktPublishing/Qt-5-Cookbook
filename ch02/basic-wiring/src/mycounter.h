#ifndef MYCOUNTER_H
#define MYCOUNTER_H

#include <QObject>

class MyCounter : public QObject
{
   Q_OBJECT

public:
   MyCounter(int value = 0, QObject *parent = nullptr);

public Q_SLOTS:
   void setValue(int value);

Q_SIGNALS:
   void valueChanged(int value);

private:
   int _value;
};

#endif // MYCOUNTER_H
