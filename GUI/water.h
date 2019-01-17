#pragma once

#ifndef WATER_H
#define WATER_H

#include "../FastNoise-master/FastNoise.h"
#include "QColor"
#include "QImage"
#include "QGraphicsPixmapItem"
#include "QPixmap"
#include "QVector"

/*This class represents the water in the game. It is going to live in the animation thread*/

class Water
{
public:
    //Constructors
    Water();
    Water(QColor color, int width, int base_level);
    //Methods
    void rise(double amount);
    void animate(double T);
    //Paramters
    double base_level;
    QImage* image;
    double wave_size = 100;

private:
    //Parameters
    double freq = 0.1;
    QColor color;
    int width;
    FastNoise generator;
};

#endif // WATER_H
