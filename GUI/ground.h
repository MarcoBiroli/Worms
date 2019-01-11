#pragma once

#ifndef GROUND_H
#define GROUND_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QCursor>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "../Physics/Collider.h"
#include <perlinnoise.h>
#include <qmath.h>
#include "QDebug"
#include <QtGui>

class Ground : public Collider
{
private:
    QImage* map; // colors colliding_map //This is the image in which we store the information about the ground
    QRgb white = qRgb(255, 255, 255);   //I define colors here so later in the code i can just us "black" or "white"
    QRgb black = qRgb(0, 0, 0);         //insted of having to write the full rgb code each time.
    QRgb blue_sky = qRgb(32, 187, 255);  //bright blue for the sky
    QRgb blue_sea = qRgb(17, 62, 228);   //dark blue for the sea
    QColor transparent = qRgba(0,0,0,0);
    QColor brown = qRgba(125,65,6, 255);
    QColor green = qRgba(121,178,51, 255);

    QGraphicsPixmapItem *item; //This is a QGraphicsItem, its an item that can be given to the screen to display.
    QVector<QPair<int, int> > getNeighbors(QPair<int, int> source);
    void dilate(QImage kernel);
    void dilate2(QColor color);
    int height;
    int width;
    void dilate3(QColor color, int depth);
    int **manhattan();
    void dilate4(QColor color, int depth);
    //int water_height;
    //double T = 0;
    //PerlinNoise* pn;

public:
    //Constructors
    Ground();
    Ground(const int width, const int height); //const QImage background);
    Ground(const QImage background);
    int WaterHeight(const int counter);
    void Water(const int water_height);
    void randomize();
    void randomize2();

    QGraphicsPixmapItem* getPixmap() const; //This returns the Displayable Version of the Ground.
    void fillup(int i, int j, QImage& perlin);
    QImage* getMap() const; //This returns the ground itself.

    void delete_ground(int x, int y); //This deletes the ground at one point of coordinate (x,y).

    virtual void circ_delete(int x, int y, double radius); //This deletes all points in a circle of center (x,y) and radius "radius".
    void AnimateWater(double dt);
};

#endif // GROUND_H
