#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QCheckBox;
class QGraphicsScene;
class QGraphicsTextItem;
class QGraphicsView;
class QGroupBox;
class QPropertyAnimation;
class QRadioButton;
class QSlider;

class MainWindow : public QMainWindow // clazy:excludeall=connect-by-name
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);

protected:
   void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private Q_SLOTS:
   void on_rotateSlider_valueChanged();
   void on_graphicsScene_selectionChanged();
   void on_scaleSpinBox_valueChanged(double value);
   void on_centerSelected_clicked(bool checked);
   void on_centerSceneCenter_clicked(bool checked);

private:
   void createStandardWidgets(const QString &title);
   void createGraphicsItems();

   QGraphicsScene *_scene;
   QGraphicsView *_view;
   QGroupBox *_selectedGroupBox;
   QSlider *_rotateSlider;
   QRadioButton *_centerSelected;
   QCheckBox *_fit;
   QGraphicsTextItem *_textItem;
   QPropertyAnimation *_animation;
};

#endif // MAINWINDOW_H
