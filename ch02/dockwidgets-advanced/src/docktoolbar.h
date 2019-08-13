#ifndef DOCKTOOLBAR_H
#define DOCKTOOLBAR_H

#include <QToolBar>
#include <QButtonGroup>

#include "orientabletoolbutton.h"

class QDockWidget;

class DockToolBar : public QToolBar
{
    Q_OBJECT

public:
   DockToolBar(QWidget *parent = nullptr);
   DockToolBar(const QString &title, QWidget *parent = nullptr);

   void addDockWidget(const QIcon &icon,
                      const QString &title,
                      QWidget *widget);

private Q_SLOT:
   void buttonToggled(QAbstractButton *button, bool checked);

private:
   QButtonGroup _buttonGroup;
   OrientableToolButton *_currentButton;
   QMap<OrientableToolButton *, QDockWidget *> _toolButtonDock;
};

#endif // DOCKTOOLBAR_H
