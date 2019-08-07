#include "docktoolbar.h"

#include "orientabletoolbutton.h"

#include <QDockWidget>
#include <QMainWindow>

DockToolBar::DockToolBar(QWidget *parent)
   : QToolBar(parent),
     _currentButton(nullptr)
{
   setMovable(false);
   connect(&_buttonGroup, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),
           this, &DockToolBar::buttonToggled);
}

DockToolBar::DockToolBar(const QString &title, QWidget *parent)
   : DockToolBar(parent)
{
   setWindowTitle(title);
}

void DockToolBar::addDockWidget(const QIcon &icon, const QString &title, QWidget *widget)
{
   auto mainWindow = qobject_cast<QMainWindow *>(parent());
   if (!mainWindow || !widget) {
      return;
   }

   auto toolButton = new OrientableToolButton { icon, title, this };
   _buttonGroup.addButton(toolButton);
   addWidget(toolButton);

   QDockWidget *dockWidget = new QDockWidget { title };
   dockWidget->setWidget(widget);
   dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

   if (_toolButtonDock.isEmpty()) {
      _currentButton = toolButton;
   }

   _toolButtonDock[toolButton] = dockWidget;
   _currentButton->setChecked(true);
}

void DockToolBar::buttonToggled(QAbstractButton *button, bool checked)
{
   auto mainWindow = qobject_cast<QMainWindow *>(parent());
   auto orientableButton = qobject_cast<OrientableToolButton *>(button);
   auto dockWidget = _toolButtonDock.value(orientableButton);
   if (!mainWindow || !orientableButton || !dockWidget) {
      return;
   }

   if (checked) {
      _currentButton = orientableButton;
      mainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(mainWindow->toolBarArea(this)), dockWidget);
      dockWidget->show();
   }
   else {
      mainWindow->removeDockWidget(dockWidget);
   }
}
