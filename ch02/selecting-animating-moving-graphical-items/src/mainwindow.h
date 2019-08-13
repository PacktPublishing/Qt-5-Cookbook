#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsView;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);

protected:
   void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
   QGraphicsView *_graphicsView;

   void createStandardWidgets(const QString &title);
   void createGraphicsItems();
};

#endif // MAINWINDOW_H
