#ifndef RIGIDBODY_H
#define RIGIDBODY_H

using namespace std;
#include <QPointF>
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>



class RigidBody
{
public:
    RigidBody();
    float x = 0.0;
    float y = 0.0;
    float vx = 0.0;
    float vy = 0.0;
    float ax = 0.0;
    float ay = 0.0;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool pressed;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // RIGIDBODY_H
