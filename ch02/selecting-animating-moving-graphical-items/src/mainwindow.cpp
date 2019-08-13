#include "mainwindow.h"

#include <QApplication>
#include <QCheckBox>
#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QGraphicsBlurEffect>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGroupBox>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollBar>
#include <QSlider>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   createStandardWidgets(
      tr("Handling Graphical Items Example Application")
   );

   // Docker widget
   auto dockerWidget = new QDockWidget { tr("Controls") };
   dockerWidget->setWidget(new QWidget);
   auto dockerLayout = new QVBoxLayout { dockerWidget->widget() };
   addDockWidget(Qt::LeftDockWidgetArea, dockerWidget);

   // Docker widget - selected items
   auto selectedGroupBox = new QGroupBox { tr("Selected Items") };
   selectedGroupBox->setEnabled(false);
   auto selectedItemLayout = new QVBoxLayout { selectedGroupBox };
   auto rotateSlider = new QSlider { Qt::Horizontal };
   rotateSlider->setRange(-360, 360);
   auto scaleSpinBox = new QDoubleSpinBox;
   scaleSpinBox->setRange(0.25, 4);
   scaleSpinBox->setSingleStep(0.25);
   scaleSpinBox->setValue(1.0);
   selectedItemLayout->addWidget(new QLabel { tr("Rotate") });
   selectedItemLayout->addWidget(rotateSlider);
   selectedItemLayout->addWidget(new QLabel { tr("Scale") });
   selectedItemLayout->addWidget(scaleSpinBox);
   dockerLayout->addWidget(selectedGroupBox);

   // Docker widget - fit
   auto fitGroupBox = new QGroupBox { tr("Center On") };
   auto centerLayout = new QVBoxLayout { fitGroupBox };
   auto fit = new QCheckBox { tr("Fit") };
   auto centerSelected = new QRadioButton { tr("Selected") };
   centerSelected->setEnabled(false);
   auto centerWholeScene = new QRadioButton { tr("Scene Center") };
   centerLayout->addWidget(centerSelected);
   centerLayout->addWidget(centerWholeScene);
   centerLayout->addWidget(fit);
   dockerLayout->addWidget(fitGroupBox);
   dockerLayout->addItem(new QSpacerItem(0, 0,
                                         QSizePolicy::Minimum,
                                         QSizePolicy::Expanding));

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

   createGraphicsItems();

   // Connections
   connect(rotateSlider, &QSlider::valueChanged,
           this, [graphicsScene, rotateSlider]() {
              const QList<QGraphicsItem *> &items =
                 graphicsScene->selectedItems();
              for (auto item : items) {
                 item->setRotation(rotateSlider->value());
              }
           }
   );

   connect(graphicsScene, &QGraphicsScene::selectionChanged,
           this, [this, selectedGroupBox, centerSelected,
                  graphicsScene]() {
      selectedGroupBox->setEnabled(
         !graphicsScene->selectedItems().isEmpty()
      );
      centerSelected->setEnabled(selectedGroupBox->isEnabled());
      for (auto item : graphicsScene->items()) {
         item->setScale(item->isSelected() ? 1.2:1);
         if (item->isSelected()) {
            item->setGraphicsEffect(nullptr);
         }
         else {
            item->setGraphicsEffect(
               graphicsScene->selectedItems().isEmpty() ?
                  nullptr:new QGraphicsBlurEffect(this));
         }
      }
   });

   connect(scaleSpinBox, QOverload<double>::of(
              &QDoubleSpinBox::valueChanged
           ),
           this, [graphicsScene, scaleSpinBox]() {
              const QList<QGraphicsItem *> &items =
                 graphicsScene->selectedItems();
              for (auto item : items) {
                 item->setScale(scaleSpinBox->value());
              }
           }
   );

   connect(centerSelected, &QRadioButton::clicked,
           this, [this, graphicsScene, fit](bool checked) {
      if (checked && !graphicsScene->selectedItems().isEmpty()) {
         QRectF selectedRect;
         const QList<QGraphicsItem *> &items =
            graphicsScene->selectedItems();
         if (fit->isChecked()) {
            for(auto selected : items) {
               selectedRect = selectedRect.united(
                  selected->sceneBoundingRect()
               );
            }
            _graphicsView->fitInView(
                     selectedRect,
                     Qt::KeepAspectRatio
                     );
         } else {
            for(auto selected : items) {
               selectedRect = selectedRect.united(
                  selected->sceneBoundingRect()
               );
            }
            _graphicsView->centerOn(selectedRect.center());
         }
      }
   });
   connect(centerWholeScene, &QRadioButton::clicked,
           this, [this, graphicsScene, fit](bool checked) {
      if (checked) {
         if (fit->isChecked()) {
            _graphicsView->fitInView(
                     graphicsScene->itemsBoundingRect(),
                     Qt::KeepAspectRatio
                     );
         } else {
            _graphicsView->centerOn(
               graphicsScene->itemsBoundingRect().center()
            );
         }
      }
   });

   centerWholeScene->setChecked(true);
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

void MainWindow::createGraphicsItems()
{
   auto graphicsScene = _graphicsView->scene();
   // Central rectangle
   graphicsScene->addRect(-50, -50, 100, 100,
                          QPen(), QBrush { Qt::green })->setFlags(
      QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

   // Polygon
   auto polygon = graphicsScene->addPolygon(QVector<QPointF> {
      {-50, -50}, { 50,  50}, { 50, -50}, {-50,  50}, {-50, -50}
   }, QPen(QBrush(Qt::darkGreen), 3), QPixmap(":/icons/qtlogo.png"));
   polygon->setPos(0, 150);
   polygon->setFlags(QGraphicsItem::ItemIsMovable |
                      QGraphicsItem::ItemIsSelectable);

   // Circle
   auto ellipse = graphicsScene->addEllipse(
      -50, -50, 100, 100,
      QPen(), QBrush { Qt::red, Qt::Dense2Pattern });
   ellipse->setPos(0, -150);
   ellipse->setFlags(QGraphicsItem::ItemIsMovable |
                       QGraphicsItem::ItemIsSelectable);

   // Second rectangle (with marks)
   auto rect2 = graphicsScene->addRect(
      -25, -25, 50, 50,
      QPen(), QBrush { Qt::darkRed });
   rect2->setFlags(QGraphicsItem::ItemIsMovable |
                   QGraphicsItem::ItemIsSelectable);
   constexpr int markSize = 10;
   for (int i : { -1, 1}) {
      for (int j : { -1, 1}) {
         auto mark = new QGraphicsEllipseItem(
            -markSize/2, -markSize/2, markSize, markSize, rect2);
         mark->setBrush(QColor({ 0, 128, 128, 128 }));
         mark->setPen(Qt::NoPen);
         mark->setPos(i*rect2->rect().width()/2,
                      j*rect2->rect().height()/2);
      }
   }
   rect2->setTransform({ 1, 0, 0, -0.25, 2, 0, 150, 150, 1 });
}
