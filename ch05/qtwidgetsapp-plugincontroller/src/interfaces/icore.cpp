#include "icore.h"

namespace MyApp
{

ICore *ICore::_self = nullptr;

ICore::ICore(QObject *parent) : QObject {parent}
{
}

ICore *ICore::self()
{
   return _self;
}

} // namespace MyApp
