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
{
    if (k->key() == 0x01000023){    //press alt key to stop the loop and then F4 to close the window
 //       if (k->key() == 0x50) { //press key p
        // Alt = 0x01000023 and F4 = 0x01000033
        this->has_quitted = true;        //exit while loop
    }
    if(!this->active_worm->is_grounded.first){
        return;
    }
    double speed = 30;
    double theta = qAtan2(-this->active_worm->is_grounded.second.first, this->active_worm->is_grounded.second.second);
    double M[4] = {qCos(theta), qSin(theta), -qSin(theta), qCos(theta)}; //rotational matrix of angle theta.
    double ve = (M[0]*speed); // component of the velocity parallel to the tangent line at the collision point.
    double vu = 0; // component of the velocity perpendicular to the tangent line at the collision point.
    double M2[4] = {qCos(theta), -qSin(theta), qSin(theta), qCos(theta)};
    double vx, vy;
    if(k->key() == 0x41){
        ve *= -1;
        vx = M2[0]*ve + M2[1]*vu;
        vy = M2[2]*ve + M2[3]*vu;
        this->active_worm->setvx(vx);
        this->active_worm->setvy(vy);
        if(k->isAutoRepeat() == true && k->key() == 0x41){
            this->active_worm->setvx(vx);
            this->active_worm->setvy(vy);
        }
        /*
        this->active_worm->addForce(QPair<double, double>(this->active_worm->is_grounded.second.second*speed, -this->active_worm->is_grounded.second.first*speed));
        if(k->isAutoRepeat() == true && k->key() == 0x41){      // If the user stays on the right arrow, repeatedly give 5 speed to the right.
          this->active_worm->addForce(QPair<double, double>(this->active_worm->is_grounded.second.second*speed, -this->active_worm->is_grounded.second.first*speed));                                            // The way int QKeyEvent::key() const and bool QKeyEvent::isAutoRepeat() const work are explained in the text under.
          }
        */
    }
    if(k->key() == 0x44){
        vx = M2[0]*ve + M2[1]*vu;
        vy = M2[2]*ve + M2[3]*vu;
        this->active_worm->setvx(vx);
        this->active_worm->setvy(vy);
        if(k->isAutoRepeat() == true && k->key() == 0x44){
            this->active_worm->setvx(vx);
            this->active_worm->setvy(vy);
        }
        /*
        this->active_worm->addForce(QPair<double, double>(-this->active_worm->is_grounded.second.second*speed, this->active_worm->is_grounded.second.first*speed));
        if(k->isAutoRepeat() == true && k->key() == 0x44){      // If the user stays on the right arrow, repeatedly give 5 speed to the right.
          this->active_worm->addForce(QPair<double, double>(-this->active_worm->is_grounded.second.second*speed, this->active_worm->is_grounded.second.first*speed));                                            // The way int QKeyEvent::key() const and bool QKeyEvent::isAutoRepeat() const work are explained in the text under.
          }
        */
    }
    if (k->key() == 0x57){ // To move jump give a negative force to the y-axis (recall
      this->active_worm->addForce(QPair<double, double>(0, -5000));
      this->active_worm->setstable(false);
      }
      if( k->isAutoRepeat() == true && k->key() == 0x57){
        this->active_worm->addForce(QPair<double, double>(0, -5000));
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
}
