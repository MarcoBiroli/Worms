#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "ground.h"
#include "rigidbody.h"

int main(int argc, char *argv[])
{
    //This is the main function of the main file, this is what is run as soon as the program is launched.
    QApplication a(argc, argv);

    //Initialize the window
    QGraphicsScene *scene = new QGraphicsScene();
    //Put a graphics view inside of the window
    QGraphicsView *view = new QGraphicsView(scene);
    //Create a Ground of size (500x500)
    Ground *ground = new Ground(500, 500);
    QGraphicsEllipseItem *elipse;

    //Delete everything in the ground in radius of 100px aroud (250,250)
    ground->circ_delete(250, 250, 100);

    //Add the ground image to the window so it gets displayed
    scene->addItem(ground->getPixmap());
    QRectF rec = QRectF(0,0,50,50);

    bool pressed = false;
    if (mousePressEvent(event)) {
        pressed = true;
        scene->addEllipse(rec); }

    //Show the window
    view->show();
    return a.exec();
}

