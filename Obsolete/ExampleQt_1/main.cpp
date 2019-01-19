#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QSize>
#include <QGraphicsItem>
#include <QPainter>
#include "ground.h"

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

    //Delete everything in the ground in radius of 100px aroud (250,250)
    ground->circ_delete(250, 250, 100);

    //Add the ground image to the window so it gets displayed
    scene->addItem(ground->getPixmap());

    QGraphicsPixmapItem item1(QPixmap("/Users/louis-maeljean/Desktop/Worms/Images/Clipart_worm_right.png").scaled(QSize(25,25)));
    QGraphicsPixmapItem item2(QPixmap("/Users/louis-maeljean/Desktop/Worms/Images/Clipart_worm_left.png").scaled(QSize(25,25)));
    item1.setOffset(260,260);
    item1.setFlag(QGraphicsItem::ItemIsMovable);
    if (item1.x() > 250) {
        int x = item1.x();
        int y = item1.y();
        scene -> removeItem(&item1);
        scene -> addItem(&item2);
        item2.setOffset(x,y);
    }
    float dx = 0.01;
    for (int x = item1.x(); x < 500; x+dx) {
        item1.setX(x);

    }
    //QGraphicsPixmapItem background(QPixmap("/Users/louis-maeljean/Desktop/Worms/Images/game_background"));
    //scene -> addItem(&background);
    scene -> addItem(&item1);
    QRectF r1(0, 0, 500, 500);
    QPen blackpen(Qt::black);
    blackpen.setWidth(15);
    scene ->addRect(r1,blackpen);

    QRectF target(10.0, 20.0, 80.0, 60.0);
    QRectF source(0.0, 0.0, 70.0, 40.0);
    QImage image("/Users/louis-maeljean/Desktop/Worms/Images/game_background");

    QPainter painter;
    painter.drawImage(target, image, source);


    //Show the window
    view->show();
    return a.exec();
}


