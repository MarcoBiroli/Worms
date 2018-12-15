#include "customview.h"
#include <iostream>

CustomView::CustomView(QGraphicsScene *parent): QGraphicsView(parent)
{

}

void CustomView::wheelEvent(QWheelEvent *event)
{
   setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
   double scaleFactor = 1.03;
   static double currentScale = 1.0;  // stores the current scale value.
   static const double scaleMin = .25; // defines the min scale limit. if you want limit to increase, - scaleMin,
   static const double scaleMax = 1.45; //defines the max scale limit. if you want limit to increase, + scaleMin,
   if (event->delta() > 0 && currentScale < scaleMax)
   {
       scale(scaleFactor,scaleFactor);
       currentScale *= scaleFactor;
   }
   else if (currentScale > scaleMin) {
           scale(1/scaleFactor,1/scaleFactor);
           currentScale /= scaleFactor;
   }
}


void CustomView::keyPressEvent(QKeyEvent *k)
{
    if (k->key() == 0x01000023){//press alt key to stop the loop and then F4 to close the window
        // Alt = 0x01000023 and F4 = 0x01000033
        this->has_quitted = true;//exit while loop
    }
    Game->handleEvents(k);
}


    //Do not yet work
    /*if (k->key() == 0x51){ //key == Q
        if (this->active_worm->getstable()){
            if (this->active_worm->get_direction()){
                this->active_worm->addForce(QPair<double, double> (-1000,-4000));
                this->active_worm->setstable(false);
            }
            else{
              this->active_worm->addForce(QPair<double, double> (-4000,-2000));
              this->active_worm->setstable(false);
          }
      }
      }
    if (k->key()==0x45){ //key == E
        if (this->active_worm->getstable()){
            if (this->active_worm->get_direction()){
                this->active_worm->addForce(QPair<double, double> (4000,-2000));
                this->active_worm->setstable(false);
            }
            else{
              this->active_worm->addForce(QPair<double, double> (1000,-4000));
              this->active_worm->setstable(false);
            }
        }
    }*/


      /*change direction to the left
      if (k->key()==0x01000012 && active_worm->getstable()){
          this->active_worm->change_direction(false);
      }

      //change direction to the right
      if (k->key()==0x01000014 && active_worm->getstable()){
          this->active_worm->change_direction(true);
      }*/

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
