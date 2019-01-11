#pragma once

#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <QVector>
#include <QList>
#include <vector>
#include <QRandomGenerator64>
#include <qmath.h>
#include <QHash>
#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>
#include <QDebug>
#include <QDateTime>

class PerlinNoise {
    public:
        // Initialize with the reference values for the permutation vector
        PerlinNoise(int width, int height);
        ~PerlinNoise(){
            grid.clear();
        }
        // Generate a new permutation vector based on the value of seed
        PerlinNoise(unsigned int seed, int width, int height);
        // Get a noise value, for 2D images z can have any value
        double noise(double x, double y, double z);
    private:
        QHash<QPair<int, int>, QPair<double, double>> grid;
        double lerp(double t, double a, double b);
        double cerp(double a, double b, double w);
        double dotGrid(int i, int j, double x, double y);
        void generateGrid(quint32 seed, int width, int height);
};
#endif // PERLINNOISE_H
