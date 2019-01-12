#pragma once

#ifndef WATER_H
#define WATER_H

#include "../FastNoise-master/FastNoise.h"
#include "QColor"
#include "QImage"
#include "QGraphicsPixmapItem"
#include "QPixmap"
#include "QVector"

class Water
{
public:
    Water();
    Water(QColor color, int width, int base_level);
    void rise(double amount);
    void animate(double T);
    double base_level;
    QImage* image;
    double wave_size = 100;

private:
    double freq = 0.1;
    QColor color;
    int width;
    FastNoise generator;
};

#endif // WATER_H
