#include "icore.h"

namespace QtWidgetsApp
{

ICore *ICore::_self = nullptr;

ICore::~ICore()
{
}

ICore *ICore::self()
{
   return _self;
}

ICore::ICore(QObject *parent)
   : QObject(parent)
{
}

}
