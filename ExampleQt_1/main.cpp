#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "ground.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    MainWindow w;
    w.show();
    */

    //Initialize the window
    QGraphicsScene *scene = new QGraphicsScene();
    //Put a graphics view inside of the window
    QGraphicsView *view = new QGraphicsView(scene);
    //Create a Ground of size (500x500)
    Ground *ground = new Ground(500, 500);

    //Delete everything in the ground in radius of 100px aroud (250,250)
    ground->circ_delete(250, 250, 100);

    //Add the ground image to the window so it gets displayed
    scene->addItem(ground->getPixmap());

    //Show the window
    view->show();
    return a.exec();
}
