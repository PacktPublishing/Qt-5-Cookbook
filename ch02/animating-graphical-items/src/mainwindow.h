#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class QGraphicsScene;
class QGraphicsTextItem;
class QGraphicsView;
class QParallelAnimationGroup;
class QPropertyAnimation;
class QVariantAnimation;

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
   void displayMessage(const QString &message, int timeout = -1);

   QGraphicsScene *_scene;
   QGraphicsView *_view;
   QTimer _stepTimer;
   QTimer _bannerTimer;
   QGraphicsProxyWidget *_player;
   QGraphicsProxyWidget *_enemy;
   QGraphicsTextItem *_message;
   QPropertyAnimation *_jump;
   QPropertyAnimation *_rotate;
   QPropertyAnimation *_enemyAnim;
   QParallelAnimationGroup *_playerAnim;
   QVariantAnimation *_messageAnim;
   QPointF _ground;
   QMovie *_enemyMovie;
};

#endif // MAINWINDOW_H
