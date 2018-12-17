#pragma once

#ifndef GROUND_H
#define GROUND_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QCursor>
#include <QGraphicsPixmapItem>
#include "../Physics/Collider.h"
#include <qmath.h>
#include "QDebug"

class Ground : public Collider
{
private:
    QImage* map; //This is the image in which we store the information about the ground
    QRgb white = qRgb(255, 255, 255);   //I define colors here so later in the code i can just us "black" or "white"
    QRgb black = qRgb(0, 0, 0);         //insted of having to write the full rgb code each time.
    QRgb blue_sky = qRgb(32, 187, 255);  //bright blue for the sky
    QRgb blue_sea = qRgb(17, 62, 228);   //dark blue for the sea
    QGraphicsPixmapItem *item; //This is a QGraphicsItem, its an item that can be given to the screen to display.

public:
    Ground() : Collider (){ //Creates an undefined Ground
        this->map = new QImage();
        item = new QGraphicsPixmapItem();
        this->set_map(*this->map);
    }
    Ground(const int width, const int height);

    void randomize();

    QGraphicsPixmapItem* getPixmap() const; //This returns the Displayable Version of the Ground.

    QImage* getMap() const; //This returns the ground itself.

    void delete_ground(int x, int y); //This deletes the ground at one point of coordinate (x,y).

    void circ_delete(int x, int y, double radius); //This deletes all points in a circle of center (x,y) and radius "radius".

};

#endif // GROUND_H
