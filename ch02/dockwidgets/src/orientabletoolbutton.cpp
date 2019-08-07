#include "orientabletoolbutton.h"

#include <QStylePainter>
#include <QStyleOptionToolButton>

OrientableToolButton::OrientableToolButton(QWidget *parent)
    : QToolButton(parent)
{
   setOrientation(OrientableToolButton::VerticalTopToBottom);
   setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

OrientableToolButton::OrientableToolButton(const QString &text, QWidget *parent)
    : OrientableToolButton(parent)
{
   setText(text);
}

OrientableToolButton::OrientableToolButton(const QIcon &icon, const QString &text, QWidget *parent)
    : OrientableToolButton(text, parent)
{
   setIcon(icon);
}

QSize OrientableToolButton::sizeHint() const
{
    QSize sh = QToolButton::sizeHint();
    if (mOrientation != OrientableToolButton::Horizontal)
        sh.transpose();

    return sh;
}

void OrientableToolButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStylePainter painter(this);
    QStyleOptionToolButton option;
    initStyleOption(&option);

    if (mOrientation == OrientableToolButton::VerticalTopToBottom)
    {
        painter.rotate(90);
        painter.translate(0, -1 * width());
        option.rect = option.rect.transposed();
    }

    else if (mOrientation == OrientableToolButton::VerticalBottomToTop)
    {
        painter.rotate(-90);
        painter.translate(-1 * height(), 0);
        option.rect = option.rect.transposed();
    }

    painter.drawComplexControl(QStyle::CC_ToolButton, option);
}

OrientableToolButton::Orientation OrientableToolButton::orientation() const
{
    return mOrientation;
}

void OrientableToolButton::setOrientation(const OrientableToolButton::Orientation &orientation)
{
    mOrientation = orientation;
}
