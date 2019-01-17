#include "customview.h"

//Constructors / Destructors
CustomView::CustomView(QGraphicsScene *parent): QGraphicsView(parent)
{

}

CustomView::~CustomView(){
    game = NULL;
}

//Method
void CustomView::setup_menu(){
    QPointF pointf = this->mapToScene(QPoint(this->viewport()->pos()));
    QPoint point = QPoint(pointf.rx(), pointf.ry());
    this->game->changemenupos(point);
}

//User Methods
void CustomView::wheelEvent(QWheelEvent *event)
{
   setTransformationAnchor(QGraphicsView::AnchorViewCenter);
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
   QPointF pointf = this->mapToScene(QPoint(this->viewport()->pos()));
   QPoint point = QPoint(pointf.rx(), pointf.ry());
   this->game->changemenupos(point);
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

void CustomView::keyPressEvent(QKeyEvent *k)
{
    game->handleEvents(k);
}

void CustomView::keyReleaseEvent(QKeyEvent *k){
    game->handleReleaseEvent(k);
}

void CustomView::mouseDoubleClickEvent(QMouseEvent *event){
    game->handleMouseDoubleClickEvent(event);
}




