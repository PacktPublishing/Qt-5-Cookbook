#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QLabel>
#include <QMovie>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QRandomGenerator>

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
   _playerMovie = qobject_cast<QLabel *>(_player->widget())->movie();
   _ground = QPointF{_view->width()/2.-_player->geometry().width()/2.,
                     _view->height()-_player->geometry().height()-20};
   _player->setPos(_ground);

   // Player jump/rotate animation
   _jump = new QPropertyAnimation { _player, "pos" };
   _jump->setDuration(1000);
   _jump->setEndValue(_ground);
   _rotate = new QPropertyAnimation { _player, "rotation" };
   _rotate->setDuration(1000);
   _rotate->setStartValue(0);
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
   _enemyAnim->setEndValue(QPointF { -_enemy->geometry().width(),
                                     _ground.y() });
   _enemyAnim->setDuration(2000);
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

   // Step timer
   connect(&_stepTimer, &QTimer::timeout, this, [this, items](){
      if (_scene->collidingItems(_player).contains(_enemy)) {
         if (_playerAnim->state() == QAbstractAnimation::Running) {
            _playerAnim->setPaused(true);
         }
         _playerMovie->stop();
         _enemyAnim->stop();
         _enemyMovie->stop();
         _stepTimer.stop();
      }
      for (quint64 i = 0; i < 6; ++i) {
         items[i]->setX(items[i]->x() > -width() ?   // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                           items[i]->x()-(i+1.):0.); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
      }
   });
   _stepTimer.start(1000 / 33);

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
         setItemMovieFileName(_player,
                              QStringLiteral(":/icons/running.gif"));
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
