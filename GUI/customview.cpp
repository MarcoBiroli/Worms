#include "customview.h"
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
   // MOVE TO THE RIGHT
{
    if(!this->active_worm->is_grounded.first){
        return;
    }
    double speed = 100;
    if(k->key() == 0x41){
        this->active_worm->addForce(QPair<double, double>(this->active_worm->is_grounded.second.second*speed, -this->active_worm->is_grounded.second.first*speed));
        if(k->isAutoRepeat() == true && k->key() == 0x44){      // If the user stays on the right arrow, repeatedly give 5 speed to the right.
          this->active_worm->addForce(QPair<double, double>(this->active_worm->is_grounded.second.second*speed, -this->active_worm->is_grounded.second.first*speed));                                            // The way int QKeyEvent::key() const and bool QKeyEvent::isAutoRepeat() const work are explained in the text under.
          }
    }
    if(k->key() == 0x44){
        this->active_worm->addForce(QPair<double, double>(-this->active_worm->is_grounded.second.second*speed, this->active_worm->is_grounded.second.first*speed));
        if(k->isAutoRepeat() == true && k->key() == 0x44){      // If the user stays on the right arrow, repeatedly give 5 speed to the right.
          this->active_worm->addForce(QPair<double, double>(-this->active_worm->is_grounded.second.second*speed, this->active_worm->is_grounded.second.first*speed));                                            // The way int QKeyEvent::key() const and bool QKeyEvent::isAutoRepeat() const work are explained in the text under.
          }
    }
    /*
    if(k->key() == 0x44){           //If the input key is the right arrow which has code 0x01000014, then give force to the right to the rigid body.
      this->worms[worms_playing[team_playing]]->addForce(QPair<double, double>(500, 0));
      this->worms[worms_playing[team_playing]]->setstable(false);
      if(k->isAutoRepeat() == true && k->key() == 0x44){      // If the user stays on the right arrow, repeatedly give 5 speed to the right.
        this->worms[worms_playing[team_playing]]->addForce(QPair<double, double>(500, 0));
        }
    }

    // MOVE TO THE LEFT
    if (k->key() == 0x41){
      this->active_worm->addForce(QPair<double, double>(-5000, 0));
      this->active_worm->setstable(false);
      }
      if(k->isAutoRepeat() == true && k->key() == 0x41){
        this->active_worm->addForce(QPair<double, double>(-5000, 0));
      }
    // JUMP
    if (k->key() == 0x57){ // To move jump give a negative force to the y-axis (recall
      this->active_worm->addForce(QPair<double, double>(0, -100000));
      this->active_worm->setstable(false);
      }
      if( k->isAutoRepeat() == true && k->key() == 0x57){
        this->active_worm->addForce(QPair<double, double>(0, -100000));
        }
    */
    // QUIT
    if (k->key() == 0x50) { //press key p
      this->has_quitted = true;        //exit while loop
    }

    // NONE DISPLACEMENT KEY EVENTS:
        // Pause the game by hitting the space bar.

}
