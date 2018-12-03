#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>
#include <QObject>

#define CUSTOMVIEW

#ifdef CUSTOMVIEW



class CustomView : public QGraphicsView
{
public:
    CustomView(QGraphicsScene *parent): QGraphicsView(parent) {

    }

protected:
     void wheelEvent(QWheelEvent *event);
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
