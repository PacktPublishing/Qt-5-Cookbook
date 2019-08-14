#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMovie>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   _movie (new QMovie(QStringLiteral(":/icons/running.gif"))),
   _parallel (new QParallelAnimationGroup { this })
{
   createStandardWidgets(tr("State Machine Example Application"));

   auto scene = new QGraphicsScene;
   _sky = scene->addPixmap(QStringLiteral(":/icons/sky.png"));
   scene->setSceneRect(_sky->boundingRect());
   auto graphicsView = new QGraphicsView { scene };
   auto boundingRect = _sky->boundingRect();
   graphicsView->setFixedSize(boundingRect.size().toSize());
   graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setCentralWidget(graphicsView);

   std::array<QGraphicsItem *, 6> items = {
      scene->addPixmap(QStringLiteral(":/icons/clouds_1.png")),
      scene->addPixmap(QStringLiteral(":/icons/clouds_2.png")),
      scene->addPixmap(QStringLiteral(":/icons/clouds_3.png")),
      scene->addPixmap(QStringLiteral(":/icons/rocks_1.png")),
      scene->addPixmap(QStringLiteral(":/icons/clouds_4.png")),
      scene->addPixmap(QStringLiteral(":/icons/rocks_2.png"))
   };

   _movie->start();
   auto frameRect = _movie->frameRect();
   auto movieLabel = new QLabel;
   movieLabel->setMovie(_movie);
   movieLabel->setAttribute(Qt::WA_TranslucentBackground);
   _player = scene->addWidget(movieLabel);
   _player->setTransformOriginPoint(frameRect.center());
   _player->setPos(boundingRect.width()/2.-frameRect.width()/2.,
                   boundingRect.height()-frameRect.height());
   _parallel->addAnimation(_jump = new QPropertyAnimation {
         _player, "pos", this });
   _jump->setDuration(250);
   _parallel->addAnimation(_rotate = new QPropertyAnimation {
         _player, "rotation", this });
   _rotate->setDuration(128);
   _rotate->setStartValue(0);

   connect(&_timer, &QTimer::timeout, this, [items, boundingRect](){
      for (quint64 i = 0; i < 6; ++i) {
         items[i]->setX(items[i]->x() > -boundingRect.width() ?
                           items[i]->x()-static_cast<qreal>((i+1)):0.);
      }
   });
   _timer.start(1000 / 33);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_Space) {
      _parallel->stop();
      auto oldPos = _player->pos();
      _jump->setStartValue(oldPos);
      _jump->setEndValue(QPointF(oldPos.x(), oldPos.y()-100));
      _rotate->setEndValue(
               event->modifiers().testFlag(Qt::ControlModifier) ?
                  360:0);
      _parallel->setDirection(QAbstractAnimation::Forward);
      _parallel->start();
      connect(_parallel, &QPropertyAnimation::finished,
              this, [this](){
         if (_parallel->direction() == QAbstractAnimation::Forward) {
            _parallel->setDirection(QAbstractAnimation::Backward);
            _jump->setStartValue(QPointF(_sky->boundingRect().width()/2.-_movie->frameRect().width()/2.,
                                _sky->boundingRect().height()-_movie->frameRect().height()));
            _parallel->start();
         }
      });
   }
}

void MainWindow::createStandardWidgets(const QString &title)
{
   // Set window title
   setWindowTitle(title);

   // Menu with simple menu item
   auto fileMenu = menuBar()->addMenu(tr("&File"));
   auto exitAction = fileMenu->addAction(
            QIcon(QLatin1String(":/icons/exit.svg")),
            tr("E&xit"),
            QApplication::instance(), &QApplication::exit,
            Qt::CTRL + Qt::Key_Q
            );

   // Main toolbar with simple action
   auto mainToolBar = addToolBar(tr("Main toolbar"));
   mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   mainToolBar->addAction(exitAction);

   // Central widget
   auto label = new QLabel { title };
   label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
   setCentralWidget(label);
}
