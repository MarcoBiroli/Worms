#pragma once
#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>
#include <QObject>
#include "../Core/Game.h"

class Game;


#define CUSTOMVIEW

#ifdef CUSTOMVIEW

class CustomView : public QGraphicsView
{
public:
    CustomView(QGraphicsScene *parent);
    ~CustomView();
    Game* game;
    bool has_quitted = false;
    double currentScale = 1.0;  // stores the current scale value.
    const double scaleMin = 0.5; // defines the min scale limit. if you want limit to increase, - scaleMin,
    const double scaleMax = 3; //defines the max scale limit. if you want limit to increase, + scaleMin,
    void setup_menu();
    double prev_mouse_x = -1;
    double prev_mouse_y = -1;
    bool is_paused = false;

protected:
     void wheelEvent(QWheelEvent *event);
     void keyPressEvent(QKeyEvent *k);
     void mouseMoveEvent(QMouseEvent *event);
     void keyReleaseEvent(QKeyEvent *k);
     void mousePressEvent(QMouseEvent *event);
};

#endif




/*
class SceneView : public QGraphicsView
{
public:
    SceneView(QGraphicsScene* parent);
protected:
    virtual void wheelEvent(QWheelEvent *event);
};

---------------------------------

class Graphics_view_zoom : public QObject {
  Q_OBJECT
public:
  Graphics_view_zoom(QGraphicsView* view);
  void gentle_zoom(double factor);
  void set_modifiers(Qt::KeyboardModifiers modifiers);
  void set_zoom_factor_base(double value);

private:
  QGraphicsView* _view;
  Qt::KeyboardModifiers _modifiers;
  double _zoom_factor_base;
  QPointF target_scene_pos, target_viewport_pos;
  bool eventFilter(QObject* object, QEvent* event);

signals:
  void zoomed();
};

#endif // CUSTOMVIEW_H
*/
