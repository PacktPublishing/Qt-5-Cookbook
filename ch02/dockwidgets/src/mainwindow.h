#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);

private Q_SLOTS:
   void topLevelChanged(bool topLevel);

private:
   void createStandardWidgets(const QString &title);

   QAction *_tabifyAction;
};

#endif // MAINWINDOW_H
