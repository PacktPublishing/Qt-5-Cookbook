#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class QGraphicsScene;
class QGraphicsView;
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
   QGraphicsProxyWidget *createMovieItem(const QString &movieFile) const;
   void setItemMovieFileName(QGraphicsProxyWidget *item, const QString &movieFile);

   QGraphicsScene *_scene;
   QGraphicsView *_view;
   QTimer _stepTimer;
   QGraphicsProxyWidget *_player;
   QGraphicsProxyWidget *_enemy;
   QPropertyAnimation *_jump;
   QPropertyAnimation *_rotate;
   QPropertyAnimation *_enemyAnim;
   QParallelAnimationGroup *_playerAnim;
   QPointF _ground;
   QMovie *_playerMovie;
   QMovie *_enemyMovie;
};

#endif // MAINWINDOW_H
