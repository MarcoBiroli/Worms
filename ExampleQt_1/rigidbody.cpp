#include "rigidbody.h"



RigidBody::RigidBody()
{
    pressed = false;
}

QRectF RigidBody::boundingRect() const
{
    return QRectF(0,0,40,40);
}

void RigidBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    if (pressed){
        painter -> drawEllipse(rec);
    }
}

void RigidBody::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;

}

void RigidBody::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
}
