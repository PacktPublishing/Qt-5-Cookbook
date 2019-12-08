#include "mycoordinate.h"

Q_LOGGING_CATEGORY(component1, "myapp.component1")

QDebug operator<<(QDebug dbg, MyCoordinate myCoordinate) // NOLINT(fuchsia-overloaded-operator)
{
   QDebugStateSaver saver(dbg);
   dbg.resetFormat();
   dbg.nospace() << "(" <<
                    myCoordinate.x() << ", " << myCoordinate.y() <<
                    ")";
   return dbg;
}

MyCoordinate::MyCoordinate(qreal x, qreal y) : _x(x), _y(y)
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
