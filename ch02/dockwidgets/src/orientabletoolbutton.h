#ifndef ORIENTABLETOOLBUTTON_H
#define ORIENTABLETOOLBUTTON_H

#include <QToolButton>

class OrientableToolButton : public QToolButton
{
    Q_OBJECT

public:
    enum Orientation {
        Horizontal,
        VerticalTopToBottom,
        VerticalBottomToTop
    };

    OrientableToolButton(QWidget *parent = nullptr);
    OrientableToolButton(const QString &text, QWidget *parent = nullptr);
    OrientableToolButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);

    QSize sizeHint() const;

    OrientableToolButton::Orientation orientation() const;
    void setOrientation(const OrientableToolButton::Orientation &orientation);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Orientation mOrientation = Horizontal;
};

#endif // ORIENTABLETOOLBUTTON_H
