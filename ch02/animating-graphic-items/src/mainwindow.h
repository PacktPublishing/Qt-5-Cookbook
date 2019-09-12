#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class QGraphicsScene;
class QGraphicsTextItem;
class QGraphicsView;
class QPropertyAnimation;
class QVariantAnimation;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);

protected:
   void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private Q_SLOTS:
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
