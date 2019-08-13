#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// clazy:excludeall=connect-by-name

class QCheckBox;
class QGraphicsScene;
class QGraphicsView;
class QGroupBox;
class QRadioButton;
class QSlider;

class MainWindow : public QMainWindow
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
   QGraphicsView *_view;
   QGraphicsScene *_scene;
   QSlider *_rotateSlider;
   QGroupBox *_selectedGroupBox;
   QRadioButton *_centerSelected;
   QCheckBox *_fit;

   void createStandardWidgets(const QString &title);
   void createGraphicsItems();
};

#endif // MAINWINDOW_H
