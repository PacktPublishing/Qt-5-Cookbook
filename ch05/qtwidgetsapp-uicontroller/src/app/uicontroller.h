#ifndef _UICONTROLLER_H_
#define _UICONTROLLER_H_

#include <interfaces/iuicontroller.h>

#include <QMainWindow>

namespace MyApp
{

class UIController : public IUIController
{
   Q_OBJECT

public:
   explicit UIController(QObject *parent = nullptr);
   ~UIController() Q_DECL_OVERRIDE = default;

   bool initialize() Q_DECL_OVERRIDE;

   void addMenuItem(const QString &menu, QAction *action)
        Q_DECL_OVERRIDE;
   void addToolButton(const QString &toolbar, QAction *action,
                            Qt::ToolBarArea area = Qt::TopToolBarArea)
        Q_DECL_OVERRIDE;
   void addDockWidget(QWidget *widget,
                    Qt::DockWidgetArea area = Qt::RightDockWidgetArea)
        Q_DECL_OVERRIDE;

private:
   QMainWindow _mainWindow;
   QAction *_helpAction;
   QHash<QString, QAction *> _menuSeparators;
};

} // namespace MyApp

#endif // _UICONTROLLER_H_
