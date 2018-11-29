#ifndef GROUND_H
#define GROUND_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QCursor>
#include <QGraphicsPixmapItem>
#include <QtCore>
#include <QtGui>

class Ground
{
private:
    QImage* map; //This is the image in which we store the information about the ground
    QRgb white = qRgb(255, 255, 255);   //I define colors here so later in the code i can just us "black" or "white"
    QRgb black = qRgb(0, 0, 0); //insted of having to write the full rgb code each time.
    QRgb green = qRgb(0,255,0);
    QRgb blue = qRgb(0,0,255);
    QRgb brown = qRgb(173,79,9);
    QGraphicsPixmapItem *item; //This is a QGraphicsItem, its an item that can be given to the screen to display.

public:
    Ground();
    Ground(const int width, const int height); //Creates a ground of a given size.
    QGraphicsPixmapItem* getPixmap() const; //This returns the Displayable Version of the Ground.
    QImage* getMap() const; //This returns the ground itself.
    void delete_ground(int x, int y); //This deletes the ground at one point of coordinate (x,y).
    void circ_delete(int x, int y, double radius); //This deletes all points in a circle of center (x,y) and radius "radius".
};

#endif // GROUND_H
