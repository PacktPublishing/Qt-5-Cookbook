#ifndef _IUICONTROLLER_H_
#define _IUICONTROLLER_H_

#include <interfaces/qtwidgetsappinterfacesexport.h>

#include <QObject>

class QAction;

namespace MyApp
{

class QTWIDGETSAPPINTERFACES_EXPORT IUIController : public QObject
{
   Q_OBJECT

public:
   ~IUIController() Q_DECL_OVERRIDE = default;

   virtual bool initialize() = 0;
   virtual void addMenuItem(const QString &menu, QAction *action) = 0;
   virtual void addToolButton(const QString &toolbar, QAction *action,
               Qt::ToolBarArea area = Qt::TopToolBarArea) = 0;
   virtual void addDockWidget(QWidget *widget,
               Qt::DockWidgetArea area = Qt::RightDockWidgetArea) = 0;

protected:
   explicit IUIController(QObject *parent = nullptr);
};

} // namespace MyApp

#endif // _IUICONTROLLER_H_
