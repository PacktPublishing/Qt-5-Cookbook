#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class QGraphicsScene;
class QGraphicsTextItem;
class QGraphicsView;
class QPropertyAnimation;
class QStateMachine;
class QVariantAnimation;

// clazy:excludeall=connect-by-name
class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);

protected:
   void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

Q_SIGNALS:
   void run();
   void spacePressed();
   void dye();
   void rPressed();

private Q_SLOTS:
   void on_running_entered();
   void on_jumping_entered();
   void on_dead_entered();
   void on_dead_exited();
   void scheduleEnemyAppearance();

private:
   QGraphicsProxyWidget *createMovieItem() const;
   void setItemMovieFileName(QGraphicsProxyWidget *item,
                             const QString &movieFile);
   void displayMessage(const QString &message, int timeout = -1);

   QGraphicsScene *_scene;
   QGraphicsView *_view;
   QTimer _stepTimer;
   QTimer _enemyTimer;
   QTimer _bannerTimer;
   QStateMachine *_stateMachine;
   QGraphicsProxyWidget *_player;
   QGraphicsProxyWidget *_enemy;
   QGraphicsTextItem *_message;
   QPropertyAnimation *_jump;
   QPropertyAnimation *_rotate;
   QPropertyAnimation *_enemyAnim;
   QVariantAnimation *_messageAnim;
   QPointF _ground;
};

#endif // MAINWINDOW_H
