#include "customview.h"
#include "../Core/Game.h"
#include <iostream>

CustomView::CustomView(QGraphicsScene *parent): QGraphicsView(parent)
{

}

CustomView::~CustomView(){
    game = NULL;
}

void CustomView::wheelEvent(QWheelEvent *event)
{
   qInfo()<<currentScale;
   if(this->is_paused){
       setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
   }
   else{
       setTransformationAnchor(QGraphicsView::AnchorViewCenter);
   }
   double scaleFactor = 1.03;
   double increasescale = 1.03;
   if (event->delta() > 0 && currentScale*scaleFactor < scaleMax)
   {
       scale(scaleFactor,scaleFactor);
       currentScale *= scaleFactor;

       this->game->changemenusize(1/increasescale,1/increasescale);
   }
   else if (currentScale/scaleFactor > scaleMin) {
       scale(1/scaleFactor,1/scaleFactor);
       currentScale /= scaleFactor;

       this->game->changemenusize(increasescale,increasescale);
   }
   QPointF pointf = mapToScene(0.0,0.0);
   QPoint point = QPoint(pointf.rx(), pointf.ry());
   this->game->changemenupos(point);
}

void CustomView::setup_menu(){
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    QPointF pointf = mapToScene(0.0,0.0);
    QPoint point = QPoint(pointf.rx(), pointf.ry());
    this->game->changemenupos(point);
}


void CustomView::keyPressEvent(QKeyEvent *k)
{
    //if (k->key() == 0x01000023){   //press alt key to stop the loop and then F4 to close the window
        // Alt = 0x01000023 and F4 = 0x01000033
    //    this->has_quitted = true;  //exit while loop
    //}
    game->handleEvents(k);
}

void CustomView::mouseMoveEvent(QMouseEvent *event){
    if(!this->is_paused){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() + (event->x() - this->width()/2));
        verticalScrollBar()->setValue(verticalScrollBar()->value() + (event->y() - this->height()/2));
        event->accept();
        this->prev_mouse_x = event->x();
        this->prev_mouse_y = event->y();
        QCursor c = cursor();
        c.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
        c.setShape(Qt::BlankCursor);
        setCursor(c);
    }
    else{
        event->ignore();
    }
    return;

}
