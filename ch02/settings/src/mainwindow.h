#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);

protected:
   void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private Q_SLOTS:
   void topLevelChanged(bool topLevel);
   void tabifyActionToogled(bool checked);

private:
   void createStandardWidgets(const QString &title);
   void writeSettings();
   void readSettings();

   QDockWidget *_leftDockWidget1;
   QDockWidget *_leftDockWidget2;
   QDockWidget *_rightDockWidget;
   QAction *_tabifyAction;
};

#endif // MAINWINDOW_H
