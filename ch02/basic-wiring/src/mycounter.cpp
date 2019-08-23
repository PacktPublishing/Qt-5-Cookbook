#include "mycounter.h"

MyCounter::MyCounter(int value, QObject *parent)
   : QObject {parent}, _value {value}
{
}

void MyCounter::setValue(int value)
{
   if (_value != value) {
      _value = value;
      Q_EMIT valueChanged(_value);
   }
}
