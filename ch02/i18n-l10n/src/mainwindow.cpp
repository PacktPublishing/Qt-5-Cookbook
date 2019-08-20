#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QMenuBar>
#include <QToolBar>

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   createStandardWidgets(tr("i18n/l10n Example Application"));
}

void MainWindow::createStandardWidgets(const QString &title)
{
   // Set window title
   setWindowTitle(title);

   // Menu with simple menu item
   auto fileMenu = menuBar()->addMenu(tr("&File"));
   auto exitAction = fileMenu->addAction(
            QIcon(QStringLiteral(":/icons/exit.svg")),
            tr("E&xit"),
            QApplication::instance(), &QApplication::exit,
            tr("Ctrl+A, Ctrl+Q") // Enabling translation for shortcuts
            );

   // Main toolbar with simple action
   auto mainToolBar = addToolBar(tr("Main toolbar"));
   mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   mainToolBar->addAction(exitAction);

   // Central widget
   auto label = new QLabel { title };
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);

   tr("TESTE", "contexto");
   tr("TESTE45", "contexto45");

   //: This is a comment for the translator.
   //= qtn_foo_bar
   //~ loc-layout_id foo_dialog
   tr("TESTE2");

   // Alternative way of passing comments for translators
   tr("TESTE3", "This is also a comment for the translator.");

   int i = 1;
   qDebug() << tr("%n message(s) saved", "", i++);
   qDebug() << tr("%n message(s) saved", "", i++);
}
