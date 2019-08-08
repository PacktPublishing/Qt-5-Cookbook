#include "mainwindow.h"

#include <QApplication>
#include <QCheckBox>
#include <QDockWidget>
#include <QDoubleSpinBox>
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

#include <QDebug>

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
   auto centerWholeScene = new QRadioButton { tr("Whole Scene") };
   centerLayout->addWidget(centerSelected);
   centerLayout->addWidget(centerWholeScene);
   centerLayout->addWidget(fit);
   dockerLayout->addWidget(fitGroupBox);
   dockerLayout->addItem(new QSpacerItem(0, 0,
                                         QSizePolicy::Minimum,
                                         QSizePolicy::Expanding));

   // GraphicsScene and GraphicsView
   auto graphicsScene = new QGraphicsScene { this };
   auto graphicsView = new QGraphicsView { graphicsScene };
   graphicsScene->setSceneRect(-5000, -5000, 10000, 10000);
   graphicsScene->addRect(-250, 0, 500, 0);
   graphicsScene->addRect(0, -250, 0, 500);
   QGraphicsRectItem *rectItem = graphicsScene->addRect(
      -50, -50, 100, 100,
      QPen(), QBrush { Qt::green });
   rectItem->setFlags(QGraphicsItem::ItemIsMovable |
                      QGraphicsItem::ItemIsSelectable);
   QGraphicsRectItem *rectItem2 = graphicsScene->addRect(
      -50, -50, 100, 100,
      QPen(), QBrush { Qt::red });
   rectItem2->setPos(0, -150);
   rectItem2->setFlags(QGraphicsItem::ItemIsMovable |
                      QGraphicsItem::ItemIsSelectable);

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
           this, [graphicsView, graphicsScene, fit](bool checked) {
      if (checked && !graphicsScene->selectedItems().isEmpty()) {
         if (fit->isChecked()) {
            QRectF selectedRect;
            const QList<QGraphicsItem *> &items =
               graphicsScene->selectedItems();
            for(auto selected : items) {
               selectedRect = selectedRect.united(
                  selected->sceneBoundingRect()
               );
            }
            graphicsView->fitInView(
                     selectedRect,
                     Qt::KeepAspectRatio
                     );
         } else {
            QRectF selectedRect;
            const QList<QGraphicsItem *> &items =
               graphicsScene->selectedItems();
            for(auto selected : items) {
               selectedRect = selectedRect.united(
                  selected->sceneBoundingRect()
               );
            }
            graphicsView->centerOn(selectedRect.center());
         }
      }
   });
   connect(centerWholeScene, &QRadioButton::clicked,
           this, [graphicsView, graphicsScene, fit](bool checked) {
      if (checked) {
         if (fit->isChecked()) {
            graphicsView->fitInView(
                     graphicsScene->itemsBoundingRect(),
                     Qt::KeepAspectRatio
                     );
         } else {
            graphicsView->centerOn(graphicsScene->itemsBoundingRect().center());
         }
      }
   });

   centerWholeScene->setChecked(true);
   setCentralWidget(graphicsView);
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
