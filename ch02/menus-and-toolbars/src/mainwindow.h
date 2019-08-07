#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QActionGroup;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);

private:
   QActionGroup *createActionGroup(const QVector<QPair<QString, QString>> &data);
};

#endif // MAINWINDOW_H
