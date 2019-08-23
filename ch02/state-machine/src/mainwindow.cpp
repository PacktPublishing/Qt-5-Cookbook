#include "mainwindow.h"

#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QLabel>
#include <QMovie>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QStateMachine>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   _scene (new QGraphicsScene),
   _view (new QGraphicsView { _scene })
{
   setWindowTitle(tr("State Machine Example Application"));

   // Configure graphics view
   auto sky = _scene->addPixmap(QStringLiteral(":/icons/sky.png"));
   _scene->setSceneRect(sky->boundingRect());
   _view->setFixedSize(_scene->sceneRect().size().toSize());
   _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setCentralWidget(_view);

   // Parallax
   std::array<QGraphicsItem *, 6> items = {
      _scene->addPixmap(QStringLiteral(":/icons/clouds_1.png")),
      _scene->addPixmap(QStringLiteral(":/icons/clouds_2.png")),
      _scene->addPixmap(QStringLiteral(":/icons/clouds_3.png")),
      _scene->addPixmap(QStringLiteral(":/icons/rocks_1.png")),
      _scene->addPixmap(QStringLiteral(":/icons/clouds_4.png")),
      _scene->addPixmap(QStringLiteral(":/icons/rocks_2.png"))
   };

   // Player
   _player = createMovieItem();
   setItemMovieFileName(_player,
                        QStringLiteral(":/icons/running.gif"));
   _ground = QPointF{_view->width()/2.-_player->geometry().width()/2.,
                     _view->height()-_player->geometry().height()-20};

   // Player jump and rotate animation
   _jump = new QPropertyAnimation { _player, "pos" };
   _jump->setDuration(1000);
   _jump->setEndValue(_ground);
   _rotate = new QPropertyAnimation { _player, "rotation" };
   _rotate->setKeyValues({ {0., 0.}, {1., 360.} });
   _rotate->setDuration(1000);

   // Enemy
   _enemy = createMovieItem();
   setItemMovieFileName(_enemy, QStringLiteral(":/icons/enemy.gif"));

   // Enemy move animation
   _enemyAnim = new QPropertyAnimation { _enemy, "pos" , this };
   _enemyAnim->setStartValue(QPointF { _view->width()*1.,
                                       _ground.y() });
   _enemyAnim->setDuration(2000);
   _enemyAnim->setEndValue(QPointF { -_enemy->geometry().width(),
                                     _ground.y() });
   connect(_enemyAnim, &QPropertyAnimation::finished,
           this, &MainWindow::scheduleEnemyAppearance);

   // Enemy appearance timer
   _enemyTimer.setSingleShot(true);
   connect(&_enemyTimer, &QTimer::timeout,
           _enemyAnim, [this](){ _enemyAnim->start(); });

   // Message text and rectangle
   _message = _scene->addText(QStringLiteral("default\nvalue"),
                 { QStringLiteral("DejaVu Sans"), 18, 100 });
   _message->setTextWidth(420);
   _message->setDefaultTextColor(Qt::white);
   QPainterPath path;
   constexpr int margin = 10;
   path.addRoundedRect(_message->boundingRect().marginsAdded(
      {margin, margin, margin, margin}), 15, 15);
   auto rect = _scene->addPath(path, Qt::NoPen,
                               QColor(89, 60, 81, 192));
   rect->setPos(_scene->sceneRect().width()/2-rect->boundingRect(
      ).width()/2+margin, 45);
   rect->setTransformOriginPoint(rect->boundingRect().center());
   rect->setScale(0);
   _message->setParentItem(rect);

   // Message animation
   _messageAnim = new QVariantAnimation { this };
   _messageAnim->setKeyValues({ {0., 0.}, {1., 1.} });
   _messageAnim->setDuration(1000);
   _messageAnim->setEasingCurve(QEasingCurve::OutElastic);
   connect(_messageAnim, &QVariantAnimation::valueChanged,
   this, [rect](const QVariant &value){
      rect->setScale(value.toReal());});

   // Message removal timer
   _bannerTimer.setSingleShot(true);
   connect(&_bannerTimer, &QTimer::timeout,
           this, [this]() {
      _messageAnim->setDirection(QAbstractAnimation::Backward);
      _messageAnim->start();
   });

   // Step timer
   connect(&_stepTimer, &QTimer::timeout, this, [this, items](){
      if (_scene->collidingItems(_player).contains(_enemy)) {
         Q_EMIT dye();
      }
      for (quint64 i = 0; i < 6; ++i) {
         items[i]->setX(items[i]->x() > -width() ?   // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                           items[i]->x()-(i+1.):0.); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
      }
   });

   // State machine
   _stateMachine = new QStateMachine { this };
   auto parallel = new QState { QState::ParallelStates };

   auto status = new QState { parallel };
   auto running = new QState { status };
   running->setObjectName(QStringLiteral("running"));
   auto jumping = new QState { status };
   jumping->setObjectName(QStringLiteral("jumping"));
   auto dead = new QState { status };
   dead->setObjectName(QStringLiteral("dead"));
   status->setInitialState(running);
   running->addTransition(this, &MainWindow::spacePressed, jumping);
   running->addTransition(this, &MainWindow::dye, dead);
   jumping->addTransition(this, &MainWindow::spacePressed, jumping);
   jumping->addTransition(_jump, &QAbstractAnimation::finished,
                          running);
   jumping->addTransition(this, &MainWindow::dye, dead);
   dead->addTransition(this, &MainWindow::spacePressed, running);

   auto rotation = new QState { parallel };
   auto notRotating = new QState { rotation };
   notRotating->setObjectName(QStringLiteral("notRotating"));
   auto rotating = new QState { rotation };
   rotating->setObjectName(QStringLiteral("rotating"));
   rotation->setInitialState(notRotating);
   notRotating->addTransition(this, &MainWindow::rPressed, rotating);
   rotating->addTransition(this, &MainWindow::rPressed, rotating);
   rotating->addTransition(_rotate, &QAbstractAnimation::finished,
                           notRotating);
   connect(rotating, &QAbstractState::entered,
           _rotate, [this](){ _rotate->start(); });

   _stateMachine->addState(parallel);
   _stateMachine->setInitialState(parallel);

   // Display controls message
   displayMessage(tr(
      "<center>&lt;space&gt; = jump<br/>&lt;r&gt; = rotate</center>"),
      5000);
   _stateMachine->start();

   // Fix mainwindow size
   setFixedSize(sizeHint());

   QMetaObject::connectSlotsByName(this);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
   switch (event->key()) {
      case Qt::Key_Space:
         Q_EMIT spacePressed();
         break;
   case Qt::Key_R:
         Q_EMIT rPressed();
         break;
   }
}

void MainWindow::on_running_entered()
{
   _player->setPos(_ground);

   // Adjust player's animation to running
   setItemMovieFileName(_player,
                        QStringLiteral(":/icons/running.gif"));

   // Schedule enemy's appearance
   _enemy->setPos(_enemyAnim->startValue().toPointF());
   if (!_enemyTimer.isActive()) {
      _enemyTimer.start(QRandomGenerator::global()->bounded(5000));
   }

   // Start step timer
   _stepTimer.start(1000/33);
}

void MainWindow::on_jumping_entered()
{
   // Change movie to jumping
   setItemMovieFileName(_player,
                        QStringLiteral(":/icons/jumping.gif"));

   // Reconfigure and start jump animation
   _jump->stop();
   _jump->setStartValue(_player->pos());
   _jump->setKeyValueAt(0.5, QPointF(_player->pos().x(),
                                     _player->pos().y()-200));
   _jump->start();
}

void MainWindow::on_dead_entered()
{
   // Stop enemy
   _enemyAnim->stop();
   (qobject_cast<QLabel *>(_enemy->widget()))->movie()->stop();

   // Stop step timer
   _stepTimer.stop();

   // Stop player
   _jump->stop();
   _rotate->stop();
   _player->setRotation(0);
   _player->setY(_ground.y()-16);

   // Change movie to dying
   setItemMovieFileName(_player, QStringLiteral(":/icons/dying.gif"));

   // Display GAME OVER message
   displayMessage(QStringLiteral(
      "<center>GAME OVER<br/>press &lt;space&gt; to restart</center>"
   ));
}

void MainWindow::on_dead_exited()
{
   // Display controls message
   displayMessage(tr(
      "<center>&lt;space&gt; = jump<br/>&lt;r&gt; = rotate</center>"),
      5000);

   // Reset enemy animation duration
   _enemyAnim->setDuration(2000);
   (qobject_cast<QLabel *>(_enemy->widget()))->movie()->start();
}

void MainWindow::scheduleEnemyAppearance()
{
   // Make enemy appear faster
   _enemyAnim->setDuration(_enemyAnim->duration() > 0 ?
                              _enemyAnim->duration()-200:2000);
   // Schedule appearance
   _enemyTimer.start(QRandomGenerator::global()->bounded(5000));
}

QGraphicsProxyWidget *MainWindow::createMovieItem() const
{
   auto movieLabel = new QLabel;
   movieLabel->setMovie(new QMovie { movieLabel });
   movieLabel->setAttribute(Qt::WA_TranslucentBackground);

   return _scene->addWidget(movieLabel);
}

void MainWindow::setItemMovieFileName(QGraphicsProxyWidget *item,
                                      const QString &movieFile)
{
   auto movie = qobject_cast<QLabel *>(item->widget())->movie();
   movie->stop();
   movie->setFileName(movieFile);
   movie->start();
   item->resize(movie->frameRect().size());
   item->setTransformOriginPoint(item->boundingRect().center());
}

void MainWindow::displayMessage(const QString &message, int timeout)
{
   _bannerTimer.stop();
   _messageAnim->setDirection(QAbstractAnimation::Forward);
   _message->setHtml(message);
   _messageAnim->start();
   if (timeout >= 0) {
      _bannerTimer.start(timeout);
   }
}
