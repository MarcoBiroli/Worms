#include "customview.h"
#include <iostream>

CustomView::CustomView(QGraphicsScene *parent): QGraphicsView(parent)
{

}

CustomView::~CustomView(){
    game = NULL;
}

void CustomView::wheelEvent(QWheelEvent *event)
{
   setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
   double scaleFactor = 1.03;
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
    if (k->key() == 0x01000023){   //press alt key to stop the loop and then F4 to close the window
        // Alt = 0x01000023 and F4 = 0x01000033
        this->has_quitted = true;  //exit while loop
    }
    game->handleEvents(k);
}
