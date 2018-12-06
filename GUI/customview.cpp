.#include "customview.h"
#include <iostream>

CustomView::CustomView(QGraphicsScene *parent): QGraphicsView(parent)
{

}

void CustomView::wheelEvent(QWheelEvent *event)
{
   setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
   double scaleFactor = 1.03;

   if (event->delta() > 0)
   {
       scale(scaleFactor,scaleFactor);
   }
   else
   {
       scale(1/scaleFactor,1/scaleFactor);
   }
}

void CustomView::keyPressEvent(QKeyEvent *k)
{
    if(k->key() == 0x44){           //If the input key is the right arrow which has code 0x01000014, then give force to the right to the rigid body.
      this->active_worm->addForce(QPair<double, double>(500, 0));
      this->active_worm->setstable(false);
      if(k->isAutoRepeat() == true && k->key() == 0x44){      // If the user stays on the right arrow, repeatedly give 5 speed to the right.
        this->active_worm->addForce(QPair<double, double>(500, 0));                                             // The way int QKeyEvent::key() const and bool QKeyEvent::isAutoRepeat() const work are explained in the text under.
        }
    }

    // MOVE TO THE LEFT
    if (k->key() == 0x41){ // To move to the left just take out 5 velocity.
      qDebug() << "debug left";
      this->active_worm->addForce(QPair<double, double>(-500, 0));
      this->active_worm->setstable(false);
      }
      if(k->isAutoRepeat() == true && k->key() == 0x41){
        this->active_worm->addForce(QPair<double, double>(-500, 0));
      }
    // JUMP
    if (k->key() == 0x57){ // To move jump give a negative force to the y-axis (recall
      this->active_worm->addForce(QPair<double, double>(0, -1000));
      this->active_worm->setstable(false);
      }
      if( k->isAutoRepeat() == true && k->key() == 0x57){
        this->active_worm->addForce(QPair<double, double>(0, -1000));
        }
    // QUIT
    if (k->key() == 0x50) { //press key p
      this->has_quitted = true;        //exit while loop
    }
}
