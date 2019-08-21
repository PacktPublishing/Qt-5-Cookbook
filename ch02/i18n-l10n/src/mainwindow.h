#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocale>

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(const QLocale &locale, QWidget *parent = nullptr);

private:
   QLocale _locale;
   int _messagesSent;
};

#endif // MAINWINDOW_H
