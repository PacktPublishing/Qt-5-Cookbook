#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QLabel>
#include <QMovie>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QRandomGenerator>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   setWindowTitle(tr("Animating Graphical Item Example Application"));

   // Configure graphics view
   _scene = new QGraphicsScene;
   auto sky = _scene->addPixmap(QStringLiteral(":/icons/sky.png"));
   _scene->setSceneRect(sky->boundingRect());
   _view = new QGraphicsView { _scene };
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
   _player = createMovieItem(QStringLiteral(":/icons/running.gif"));
   _ground = QPointF{_view->width()/2.-_player->geometry().width()/2.,
                     _view->height()-_player->geometry().height()-20};
   _player->setPos(_ground);

   // Player jump/rotate animation
   _jump = new QPropertyAnimation { _player, "pos" };
   _jump->setDuration(1000);
   _jump->setEndValue(_ground);
   _rotate = new QPropertyAnimation { _player, "rotation" };
   _rotate->setStartValue(0);
   _rotate->setDuration(1000);
   _playerAnim = new QParallelAnimationGroup { this };
   _playerAnim->addAnimation(_jump);
   _playerAnim->addAnimation(_rotate);

   // Enemy
   _enemy = createMovieItem(QStringLiteral(":/icons/enemy.gif"));
   _enemyMovie = qobject_cast<QLabel *>(_enemy->widget())->movie();

   // Enemy move animation
   _enemyAnim = new QPropertyAnimation { _enemy, "pos" , this };
   _enemyAnim->setStartValue(QPointF { _view->width()*1.,
                                       _ground.y() });
   _enemyAnim->setDuration(2000);
   _enemyAnim->setEndValue(QPointF { -_enemy->geometry().width(),
                                     _ground.y() });
   _enemy->setPos(_enemyAnim->startValue().toPointF());

   // Enemy's appearance
   QTimer::singleShot(QRandomGenerator::global()->bounded(5000), // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)
      _enemyAnim, [this](){ _enemyAnim->start(); });
   connect(_enemyAnim, &QPropertyAnimation::finished, this, [this](){
      _enemyAnim->setDuration(_enemyAnim->duration() > 0 ?
                                 _enemyAnim->duration()-200:2000);
      QTimer::singleShot(QRandomGenerator::global()->bounded(5000),
         _enemyAnim, [this](){ _enemyAnim->start(); });
   });

   // Message text and rectangle
   _message = _scene->addText(QStringLiteral("default\nvalue"), { QStringLiteral("DejaVu Sans"), 18, 100 });
   _message->setTextWidth(420);
   _message->setDefaultTextColor(Qt::white);
   QPainterPath path;
   constexpr int margin = 10;
   path.addRoundedRect(_message->boundingRect().marginsAdded({margin, margin, margin, margin}), 15, 15);
   auto rect = _scene->addPath(path, Qt::NoPen, QColor(89, 60, 81, 192));
   rect->setPos(_scene->sceneRect().width()/2-rect->boundingRect().width()/2+margin, 45);
   rect->setTransformOriginPoint(rect->boundingRect().center());
   rect->setScale(0);
   _message->setParentItem(rect);

   // Message animation
   _messageAnim = new QVariantAnimation { this };
   _messageAnim->setStartValue(0.0);
   _messageAnim->setDuration(1000);
   _messageAnim->setEndValue(1.0);
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

   displayMessage(tr("&lt;space&gt; = jump\n&lt;ctrl+space&gt; = jump+rotate"), 5000);

   // Step timer
   connect(&_stepTimer, &QTimer::timeout, this, [this, items, rect](){
      if (_scene->collidingItems(_player).contains(_enemy)) {
         rect->setScale(0);
         _bannerTimer.stop();
         _messageAnim->stop();
         _enemyAnim->stop();
         _enemyMovie->stop();
         _stepTimer.stop();
         _playerAnim->stop();
         _player->setRotation(0);
         _player->setY(_ground.y()-16);
         setItemMovieFileName(_player,
                              QStringLiteral(":/icons/dying.gif"));
         displayMessage(QStringLiteral("<center>GAME OVER<br/>press &lt;space&gt; to restart</center>"));
      }
      for (quint64 i = 0; i < 6; ++i) {
         items[i]->setX(items[i]->x() > -width() ?   // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                           items[i]->x()-(i+1.):0.); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
      }
   });
   _stepTimer.start(1000/33);

   // Fix mainwindow size
   setFixedSize(sizeHint());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_Space) {
      if (_stepTimer.isActive()) {
         setItemMovieFileName(_player,
                              QStringLiteral(":/icons/jumping.gif"));
         _playerAnim->stop();
         _jump->setStartValue(_player->pos());
         _jump->setKeyValueAt(0.5, QPointF(_player->pos().x(),
                                           _player->pos().y()-200));
         _rotate->setEndValue(
            event->modifiers().testFlag(Qt::ControlModifier) ? 360:0);
         _playerAnim->start();
         connect(_playerAnim, &QPropertyAnimation::finished,
                 this, [this](){
            setItemMovieFileName(_player,
               QStringLiteral(":/icons/running.gif"));
         });
      } else {
         displayMessage(QLatin1String(""), 0);
         setItemMovieFileName(_player,
                              QStringLiteral(":/icons/running.gif"));
         _player->setPos(_ground);
         if (_playerAnim->state() == QAbstractAnimation::Paused) {
            _playerAnim->setPaused(false);
         }
         _enemy->setPos(_enemyAnim->startValue().toPointF());
         _enemyAnim->setDuration(2000);
         _enemyMovie->start();
         _stepTimer.start();
         QTimer::singleShot(QRandomGenerator::global()->bounded(5000),
            _enemyAnim, [this](){ _enemyAnim->start(); });
      }
   }
}

QGraphicsProxyWidget *MainWindow::createMovieItem(
      const QString &movieFile) const
{
   auto movieLabel = new QLabel;
   movieLabel->setMovie(
            new QMovie { movieFile, QByteArray(), movieLabel });
   movieLabel->setAttribute(Qt::WA_TranslucentBackground);
   movieLabel->movie()->start();
   auto item = _scene->addWidget(movieLabel);
   item->resize(movieLabel->movie()->frameRect().size());
   item->setTransformOriginPoint(item->boundingRect().center());

   return item;
}

void MainWindow::setItemMovieFileName(QGraphicsProxyWidget *item,
                                      const QString &movieFile)
{
   auto movie = qobject_cast<QLabel *>(item->widget())->movie();
   movie->stop();
   movie->setFileName(movieFile);
   movie->start();
   item->resize(movie->frameRect().size());
}

void MainWindow::displayMessage(const QString &message, int timeout)
{
   _messageAnim->setDirection(QAbstractAnimation::Forward);
   _message->setHtml(message);
   _messageAnim->start();
   if (timeout >= 0) {
      _bannerTimer.start(timeout);
   }
}
