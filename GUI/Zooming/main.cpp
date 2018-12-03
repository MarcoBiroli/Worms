#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "ground.h"
#include "customview.h"



int main(int argc, char *argv[])
{
    //This is the main function of the main file, this is what is run as soon as the program is launched.
    QApplication a(argc, argv);

    //Initialize the window
    QGraphicsScene *scene = new QGraphicsScene();

    //Put a graphics view inside of the window
    QGraphicsView *view = new CustomView(scene);

    //Create a Ground of size (500x500)
    Ground *ground = new Ground(5000, 3000);

    //Delete everything in the ground in radius of 100px aroud (250,250)
    ground->circ_delete(2500, 600, 200);

    //Add the ground image to the window so it gets displayed
    scene->addItem(ground->getPixmap());

    //Show the window
    view->showNormal();
    return a.exec();
}
