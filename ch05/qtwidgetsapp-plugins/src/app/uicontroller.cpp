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

namespace QtWidgetsApp
{

class AboutPluginsDialog : public QDialog
{
public:
   AboutPluginsDialog(QWidget *parent = nullptr) : QDialog(parent)
   {
      setWindowTitle(QStringLiteral("Loaded Plugins"));
      QVBoxLayout* layout = new QVBoxLayout(this);
      QTableWidget *tableWidget = nullptr;
      layout->addWidget(tableWidget = new QTableWidget(this));
      tableWidget->setColumnCount(3);
      tableWidget->horizontalHeader()->setStretchLastSection(true);
      tableWidget->setRowCount(
           ICore::self()->pluginController()->loadedPlugins().size());
      tableWidget->setHorizontalHeaderLabels(
               QStringList() << "Name" << "Version" << "Description");
      int i = 0;
      for (const auto &pluginMetaData :
        ICore::self()->pluginController()->loadedPlugins().values()) {
         auto metaDataObject = pluginMetaData["MetaData"].toObject();
         tableWidget->setItem(i, 0,
            new QTableWidgetItem(metaDataObject["name"].toString()));
         tableWidget->setItem(i, 1,
            new QTableWidgetItem(
                               metaDataObject["version"].toString()));
         tableWidget->setItem(i, 2,
            new QTableWidgetItem(
                           metaDataObject["description"].toString()));
         ++i;
      }
      tableWidget->resizeColumnsToContents();

      auto dialogButtonBox = new QDialogButtonBox(
                                    QDialogButtonBox::Ok, this);
      connect(dialogButtonBox, &QDialogButtonBox::accepted, this,
              &QDialog::accept);
      layout->addWidget(dialogButtonBox);
   }
   virtual QSize sizeHint() const { return QSize(800,400); }
};

UIController::UIController(QObject *parent)
   : IUIController(parent)
{
}

UIController::~UIController()
{
}

bool UIController::initialize()
{
   qDebug() << "Initializing UIController";

   QMenu *fileMenu = nullptr;
   _mainWindow.menuBar()->addMenu(
               fileMenu = new QMenu("&File", _mainWindow.menuBar()));
   fileMenu->setObjectName("&File");
   _menuSeparators[QStringLiteral("&File")] =
           fileMenu->addSeparator();
   auto exitAction = fileMenu->addAction(
            QIcon {QStringLiteral(":/icons/exit.svg")}, tr("E&xit"),
            QApplication::instance(), &QApplication::exit,
            Qt::CTRL + Qt::Key_Q);
   auto mainToolBar =
           _mainWindow.addToolBar(QStringLiteral("main-toolbar"));
   mainToolBar->setObjectName(QStringLiteral("main-toolbar"));
   mainToolBar->addAction(exitAction);

   QMenu *helpMenu = nullptr;
   _helpAction = _mainWindow.menuBar()->addMenu(
               helpMenu = new QMenu("&Help", _mainWindow.menuBar()));
   helpMenu->setObjectName("&Help");
   _menuSeparators[QStringLiteral("&Help")] =
           helpMenu->addSeparator();
   auto aboutPluginsAction = new QAction {
           QIcon {":/icons/plugins.svg"}, "About &Plugins"};
   helpMenu->addAction(aboutPluginsAction);
   connect(aboutPluginsAction, &QAction::triggered, this, [=]() {
      (new AboutPluginsDialog(&_mainWindow))->exec();
   });

   auto label = new QLabel {
    QStringLiteral("Hello from microkernel QtWidgets application!") };
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   _mainWindow.setCentralWidget(label);
   _mainWindow.showMaximized();

   return true;
}

void UIController::addMenuItem(const QString &menu, QAction *action)
{
   auto myMenu = _mainWindow.menuBar()->findChild<QMenu *>(menu);
   if (!myMenu) {
      _mainWindow.menuBar()->insertMenu(_helpAction,
                     myMenu = new QMenu(menu, _mainWindow.menuBar()));
      myMenu->setObjectName(menu);
   }
   if (_menuSeparators.value(menu))
      myMenu->insertAction(_menuSeparators.value(menu), action);
   else
      myMenu->addAction(action);
}

void UIController::addToolButton(const QString &toolbar,
                                 QAction *action,
                                 Qt::ToolBarArea area)
{
   auto myToolBar = _mainWindow.findChild<QToolBar *>(toolbar);
   if (!myToolBar) {
      _mainWindow.addToolBar(area, myToolBar = new QToolBar(toolbar));
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

}
