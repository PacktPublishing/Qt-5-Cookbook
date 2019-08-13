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
            tr("Handling Graphical Items Example Application"));

   // Docker widget
   auto dockerWidget = new QDockWidget { tr("Controls") };
   dockerWidget->setWidget(new QWidget);
   auto dockerLayout = new QVBoxLayout { dockerWidget->widget() };
   addDockWidget(Qt::LeftDockWidgetArea, dockerWidget);

   // Docker widget - selected items
   _selectedGroupBox = new QGroupBox { tr("Selected Items") };
   _selectedGroupBox->setEnabled(false);
   auto selectedItemLayout = new QVBoxLayout { _selectedGroupBox };
   _rotateSlider = new QSlider { Qt::Horizontal };
   _rotateSlider->setObjectName(QStringLiteral("rotateSlider"));
   _rotateSlider->setRange(-360, 360);
   auto scaleSpinBox = new QDoubleSpinBox;
   scaleSpinBox->setObjectName(QStringLiteral("scaleSpinBox"));
   scaleSpinBox->setRange(0.25, 4);
   scaleSpinBox->setSingleStep(0.25);
   scaleSpinBox->setValue(1.0);
   selectedItemLayout->addWidget(new QLabel { tr("Rotate") });
   selectedItemLayout->addWidget(_rotateSlider);
   selectedItemLayout->addWidget(new QLabel { tr("Scale") });
   selectedItemLayout->addWidget(scaleSpinBox);
   dockerLayout->addWidget(_selectedGroupBox);

   // Docker widget - fit
   auto fitGroupBox = new QGroupBox { tr("Center On") };
   auto centerLayout = new QVBoxLayout { fitGroupBox };
   _fit = new QCheckBox { tr("Fit") };
   _centerSelected = new QRadioButton { tr("Selected") };
   _centerSelected->setObjectName(QStringLiteral("centerSelected"));
   _centerSelected->setEnabled(false);
   auto centerSceneCenter = new QRadioButton { tr("Scene Center") };
   centerSceneCenter->setObjectName(
            QStringLiteral("centerSceneCenter"));
   centerLayout->addWidget(_centerSelected);
   centerLayout->addWidget(centerSceneCenter);
   centerLayout->addWidget(_fit);
   dockerLayout->addWidget(fitGroupBox);
   dockerLayout->addItem(new QSpacerItem(0, 0,
                                         QSizePolicy::Minimum,
                                         QSizePolicy::Expanding));

   // GraphicsScene and GraphicsView
   _scene = new QGraphicsScene { this };
   _scene->setObjectName(QStringLiteral("graphicsScene"));
   _view = new QGraphicsView { _scene };
   _view->setRenderHints(QPainter::Antialiasing |
                         QPainter::SmoothPixmapTransform);
   _scene->setSceneRect(-5000, -5000, 10000, 10000);
   setCentralWidget(_view);

   // Axis
   _scene->addLine(-250, 0, 250, 0);
   _scene->addLine(0, -250, 0, 250);

   createGraphicsItems();

   centerSceneCenter->setChecked(true);

   QMetaObject::connectSlotsByName(this);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
   _view->centerOn(0, 0);
   QMainWindow::resizeEvent(event);
}

void MainWindow::on_rotateSlider_valueChanged()
{
   const QList<QGraphicsItem *> &items =
         _view->scene()->selectedItems();
   for (auto item : items) {
      item->setRotation(_rotateSlider->value());
   }
}

void MainWindow::on_graphicsScene_selectionChanged()
{
   _selectedGroupBox->setEnabled(!_scene->selectedItems().isEmpty());
   _centerSelected->setEnabled(_selectedGroupBox->isEnabled());
   auto items = _scene->items();
   for (auto item : items) {
      item->setScale(item->isSelected() ? 1.2:1);
      item->setGraphicsEffect(
               item->isSelected() | _scene->selectedItems().isEmpty()
               ? nullptr:new QGraphicsBlurEffect(this));
   }
}

void MainWindow::on_scaleSpinBox_valueChanged(double value)
{
   const QList<QGraphicsItem *> &items =
         _view->scene()->selectedItems();
   for (auto item : items) {
      item->setScale(value);
   }
}

void MainWindow::on_centerSelected_clicked(bool checked)
{
   if (checked && !_scene->selectedItems().isEmpty()) {
      auto items = _scene->selectedItems();
      QRectF selectedRect;
      for(auto selected : items) {
         selectedRect = selectedRect.united(
                  selected->sceneBoundingRect()
                  );
      }
      if (_fit->isChecked()) {
         _view->fitInView( selectedRect, Qt::KeepAspectRatio);
      } else {
         _view->centerOn(selectedRect.center());
      }
   }
}

void MainWindow::on_centerSceneCenter_clicked(bool checked)
{
   if (checked) {
      if (_fit->isChecked()) {
         _view->fitInView(
                  _scene->itemsBoundingRect(),Qt::KeepAspectRatio
                  );
      } else {
         _view->centerOn(_scene->itemsBoundingRect().center());
      }
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
}

void MainWindow::createGraphicsItems()
{
   auto graphicsScene = _view->scene();
   // Central rectangle
   graphicsScene->addRect(-50, -50, 100, 100,
                          QPen(), QBrush { Qt::green })->setFlags(
      QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

   // Polygon
   auto polygon = graphicsScene->addPolygon(QVector<QPointF> {
           {-50, -50}, { 50,  50}, { 50, -50}, {-50,  50}, {-50, -50}
        }, QPen(QBrush(Qt::darkGreen), 3),
        QPixmap(QStringLiteral(":/icons/qtlogo.png")));
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
            -markSize/2., -markSize/2., markSize, markSize, rect2);
         mark->setBrush(QColor({ 0, 128, 128, 128 }));
         mark->setPen(Qt::NoPen);
         mark->setPos(i*rect2->rect().width()/2,
                      j*rect2->rect().height()/2);
      }
   }
   rect2->setTransform({ 1, 0, 0, -0.25, 2, 0, 150, 150, 1 });
}
