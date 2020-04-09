#include "uicontroller.h"

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDockWidget>
#include <QHeaderView>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QTableWidget>
#include <QToolBar>
#include <QVBoxLayout>

#include <interfaces/icore.h>
#include <interfaces/iplugin.h>
#include <interfaces/iplugincontroller.h>

namespace MyApp
{

class AboutPluginsDialog : public QDialog
{
    Q_OBJECT

public:
   explicit AboutPluginsDialog(QWidget *parent = nullptr)
        : QDialog {parent}
   {
      setWindowTitle(QStringLiteral("Loaded Plugins"));
      auto layout = new QVBoxLayout {this};
      QTableWidget *tableWidget = nullptr;
      layout->addWidget(tableWidget = new QTableWidget {this});
      tableWidget->setColumnCount(3);
      tableWidget->horizontalHeader()->setStretchLastSection(true);
      tableWidget->setRowCount(
           ICore::self()->pluginController()->loadedPlugins().size());
      tableWidget->setHorizontalHeaderLabels(
                  QStringList {} << QStringLiteral("Name")
                                 << QStringLiteral("Version")
                                 << QStringLiteral("Description")
                  );
      int i = 0;
      const QList<QJsonObject> &pluginsMetaData =
          ICore::self()->pluginController()->loadedPlugins().values();
      for (const auto &pluginMetaData : pluginsMetaData) {
         auto metaDataObject =
                pluginMetaData[QStringLiteral("MetaData")].toObject();
         tableWidget->setItem(i, 0,
             new QTableWidgetItem {
               metaDataObject[QStringLiteral("name")].toString()});
         tableWidget->setItem(i, 1,
             new QTableWidgetItem {
               metaDataObject[QStringLiteral("version")].toString()});
         tableWidget->setItem(i, 2,
             new QTableWidgetItem {
               metaDataObject[QStringLiteral("description")].
                              toString()});
         ++i;
      }
      tableWidget->resizeColumnsToContents();

      auto dialogButtonBox =
              new QDialogButtonBox {QDialogButtonBox::Ok, this};
      connect(dialogButtonBox, &QDialogButtonBox::accepted,
              this, &QDialog::accept);
      layout->addWidget(dialogButtonBox);
   }
    QSize sizeHint() const Q_DECL_OVERRIDE { return {800,400}; }
};

UIController::UIController(QObject *parent) : IUIController {parent}
{
}

bool UIController::initialize()
{
   qDebug() << "Initializing UIController";

   QMenu *fileMenu = nullptr;
   _mainWindow.menuBar()->addMenu(
               fileMenu = new QMenu {QStringLiteral("&File"),
                                    _mainWindow.menuBar()}
           );
   fileMenu->setObjectName(QStringLiteral("&File"));
   _menuSeparators[QStringLiteral("&File")] =
           fileMenu->addSeparator();
   auto exitAction = fileMenu->addAction(
              QIcon {QStringLiteral(":/icons/exit.svg")}, tr("E&xit"),
              QApplication::instance(), &QApplication::exit,
              Qt::CTRL + Qt::Key_Q);
   auto mainToolBar = _mainWindow.addToolBar(
               QStringLiteral("main-toolbar"));
   mainToolBar->setObjectName(QStringLiteral("main-toolbar"));
   mainToolBar->addAction(exitAction);

   QMenu *helpMenu = nullptr;
   _helpAction = _mainWindow.menuBar()->addMenu(
               helpMenu = new QMenu {QStringLiteral("&Help"),
                                    _mainWindow.menuBar()});
   helpMenu->setObjectName(QStringLiteral("&Help"));
   _menuSeparators[QStringLiteral("&Help")] =
           helpMenu->addSeparator();
   auto aboutPluginsAction =
           new QAction {QIcon {QStringLiteral(":/icons/plugins.svg")},
                        QStringLiteral("About &Plugins")};
   helpMenu->addAction(aboutPluginsAction);
   connect(aboutPluginsAction, &QAction::triggered, this, [=]() {
      (new AboutPluginsDialog {&_mainWindow})->exec();
   });

   auto label = new QLabel {
       QStringLiteral("Hello from microkernel QtWidgets application!")
   };
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   _mainWindow.setCentralWidget(label);
   _mainWindow.showMaximized();

   // We'll move the following sentences into a plugin in next recipe
   auto editAction =
           new QAction {QIcon {QStringLiteral(":/icons/item.svg")},
                        QStringLiteral("Edit item")};
   addMenuItem(QStringLiteral("&Edit"), editAction);
   addToolButton(QStringLiteral("main-toolbar"), editAction);
   connect (editAction, &QAction::triggered, this, []() {
       qDebug() << "Action triggered!";
   });

   addToolButton(QStringLiteral("secondary-toolbar"),
     new QAction {QIcon {QStringLiteral(":/icons/item.svg")},
                         QStringLiteral("Action in another toolbar")},
     Qt::RightToolBarArea);
   addMenuItem(QStringLiteral("&File"),
              new QAction {QIcon {QStringLiteral(":/icons/item.svg")},
                           QStringLiteral("Another file item")});
   addMenuItem(QStringLiteral("&Help"),
              new QAction {QIcon {QStringLiteral(":/icons/item.svg")},
                           QStringLiteral("Another help item")});

   return true;
}

void UIController::addMenuItem(const QString &menu, QAction *action)
{
   auto myMenu = _mainWindow.menuBar()->findChild<QMenu *>(menu);
   if (!myMenu) {
      _mainWindow.menuBar()->insertMenu(_helpAction,
                    myMenu = new QMenu {menu, _mainWindow.menuBar()});
      myMenu->setObjectName(menu);
   }
   if (_menuSeparators.value(menu)) {
      myMenu->insertAction(_menuSeparators.value(menu), action);
   } else {
      myMenu->addAction(action);
   }
}

void UIController::addToolButton(const QString &toolbar,
                                 QAction *action,
                                 Qt::ToolBarArea area)
{
   auto myToolBar = _mainWindow.findChild<QToolBar *>(toolbar);
   if (!myToolBar) {
      _mainWindow.addToolBar(area, myToolBar =
              new QToolBar {toolbar});
      myToolBar->setObjectName(toolbar);
   }
   myToolBar->addAction(action);
}

void UIController::addDockWidget(QWidget *widget,
                                 Qt::DockWidgetArea area)
{
   auto dockWidget = new QDockWidget;
   dockWidget->setWidget(widget);
   _mainWindow.addDockWidget(area, dockWidget);
}

} // namespace MyApp

#include "uicontroller.moc"
