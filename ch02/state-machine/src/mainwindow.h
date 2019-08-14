#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class QGraphicsPixmapItem;
class QMovie;
class QParallelAnimationGroup;
class QPropertyAnimation;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);

protected:
   void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
   QTimer _timer;
   QGraphicsProxyWidget *_player;
   QGraphicsPixmapItem *_sky;
   QMovie *_movie;
   QParallelAnimationGroup *_parallel;
   QPropertyAnimation *_jump;
   QPropertyAnimation *_rotate;

   void createStandardWidgets(const QString &title);
};

#endif // MAINWINDOW_H
