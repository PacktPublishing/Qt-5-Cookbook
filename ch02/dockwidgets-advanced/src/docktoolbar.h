#ifndef DOCKTOOLBAR_H
#define DOCKTOOLBAR_H

#include <QButtonGroup>
#include <QToolBar>

class QDockWidget;

class OrientableToolButton;

class DockToolBar : public QToolBar
{
   Q_OBJECT

public:
   explicit DockToolBar(const QString &title = QString {},
                        QWidget *parent = nullptr);

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
