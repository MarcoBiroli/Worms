#pragma once
#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>
#include <QObject>
#include "../Physics/RigidBody.h"
#include "../Core/worms.h"

#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

extern bool quitGame;

#endif

#define CUSTOMVIEW

#ifdef CUSTOMVIEW

class CustomView : public QGraphicsView
{
public:
    CustomView(QGraphicsScene *parent);
    Worm* active_worm;
    bool has_quitted = false;


protected:
     void wheelEvent(QWheelEvent *event);
     void keyPressEvent(QKeyEvent *k);
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
