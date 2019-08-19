#include "mycoordinate.h"

Q_LOGGING_CATEGORY(component1, "myapp.component1")

// NOLINTNEXTLINE(fuchsia-overloaded-operator)
QDebug operator<<(QDebug dbg, MyCoordinate myCoordinate)
{
   QDebugStateSaver saver(dbg);
   dbg.nospace() << "(" <<
                    myCoordinate.x() << ", " << myCoordinate.y() <<
                    ")";
   return dbg;
}

MyCoordinate::MyCoordinate(qreal x, qreal y) :
   _x(x),
   _y(y)
{
}

qreal MyCoordinate::x() const
{
   return _x;
}

qreal MyCoordinate::y() const
{
   return _y;
}
