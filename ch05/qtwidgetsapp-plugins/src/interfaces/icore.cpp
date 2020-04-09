#include "icore.h"

namespace MyApp
{

ICore *ICore::_self = nullptr;

ICore *ICore::self()
{
   return _self;
}

ICore::ICore(QObject *parent) : QObject {parent}
{
}

} // namespace MyApp
