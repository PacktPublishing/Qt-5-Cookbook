#ifndef MYCOORDINATE_H
#define MYCOORDINATE_H

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(component1)

class MyCoordinate
{
public:
   explicit MyCoordinate(qreal x, qreal y);
   qreal x() const;
   qreal y() const;
private:
   qreal _x;
   qreal _y;
};

QDebug operator<<(QDebug dbg, MyCoordinate myCoordinate); // NOLINT(fuchsia-overloaded-operator)

#endif // MYCOORDINATE_H
