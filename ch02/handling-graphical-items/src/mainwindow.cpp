#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QMenuBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   createStandardWidgets(
      tr("Handling Graphical Items Example Application")
   );

   // GraphicsScene and GraphicsView
   auto graphicsScene = new QGraphicsScene { this };
   _graphicsView = new QGraphicsView { graphicsScene };
   _graphicsView->setRenderHints(QPainter::Antialiasing |
                                 QPainter::SmoothPixmapTransform);
   graphicsScene->setSceneRect(-5000, -5000, 10000, 10000);
   setCentralWidget(_graphicsView);

   // Axis
   graphicsScene->addLine(-250, 0, 250, 0);
   graphicsScene->addLine(0, -250, 0, 250);

   // Central rectangle
   graphicsScene->addRect(-50, -50, 100, 100,
                          QPen(), QBrush { Qt::green });

   // Polygon
   auto polygon = graphicsScene->addPolygon(QVector<QPointF> {
         {-50, -50}, { 50,  50}, { 50, -50}, {-50,  50}, {-50, -50}
      },
      QPen(QBrush(Qt::darkGreen), 3),
      QPixmap(QStringLiteral(":/icons/qtlogo.png")));
   polygon->setPos(0, 150);

   // Circle
   auto ellipse = graphicsScene->addEllipse(
      -50, -50, 100, 100,
      QPen(), QBrush { Qt::red, Qt::Dense2Pattern });
   ellipse->setPos(0, -150);

   // Second rectangle (with marks)
   auto rect2 = graphicsScene->addRect(
      -25, -25, 50, 50,
      QPen(), QBrush { Qt::darkRed });
   constexpr int markSize = 10;
   for (int i : { -1, 1}) {
      for (int j : { -1, 1}) {
         auto mark = new QGraphicsEllipseItem(
            -markSize/2., -markSize/2., markSize, markSize, rect2);
         mark->setBrush(QColor({ 0, 128, 128, 128 }));
         mark->setPen(Qt::NoPen);
         mark->setPos(i*rect2->rect().width()/2,
                      j*rect2->rect().height()/2);
      }
   }
   rect2->setTransform({ 1, 0, 0, -0.25, 2, 0, 150, 150, 1 });
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
   _graphicsView->centerOn(0, 0);
   QMainWindow::resizeEvent(event);
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
}
