#include "orientabletoolbutton.h"

#include <QButtonGroup>
#include <QMainWindow>
#include <QStyleOptionToolButton>
#include <QStylePainter>
#include <QToolBar>

OrientableToolButton::OrientableToolButton(const QIcon &icon,
                                           const QString &text,
                                           QWidget *parent)
   : QToolButton {parent}
{
   setIcon(icon);
   setText(text);
   setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   setCheckable(true);
}

QSize OrientableToolButton::sizeHint() const
{
   QSize sizeHint = QToolButton::sizeHint();
   auto toolBar = qobject_cast<QToolBar *>(parent());
   if (toolBar && toolBar->orientation() != Qt::Horizontal) {
      sizeHint.transpose();
   }

   return sizeHint;
}

void OrientableToolButton::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event)
   QStylePainter painter {this};
   QStyleOptionToolButton option;
   initStyleOption(&option);

   auto toolBar = qobject_cast<QToolBar *>(parent());
   if (toolBar) {
      auto mainWindow = qobject_cast<QMainWindow *>(
               toolBar->parent());
      if (mainWindow && toolBar->orientation() == Qt::Vertical) {
         if (mainWindow->toolBarArea(toolBar) == Qt::RightToolBarArea)
         {
            painter.rotate(90);
            painter.translate(0, -1 * width());
         }
         if (mainWindow->toolBarArea(toolBar) == Qt::LeftToolBarArea)
         {
            painter.rotate(-90);
            painter.translate(-1 * height(), 0);
         }
         option.rect = option.rect.transposed();
      }
   }

   painter.drawComplexControl(QStyle::CC_ToolButton, option);
}

void OrientableToolButton::mouseReleaseEvent(QMouseEvent *event) {
   QButtonGroup *buttonGroup = group();
   if (buttonGroup &&
       buttonGroup->checkedId() == buttonGroup->id(this) &&
       isDown()) {
      buttonGroup->setExclusive(false);
   }
   QToolButton::mouseReleaseEvent(event);
   if (buttonGroup) {
      buttonGroup->setExclusive(true);
   }
}
