#include "perlinnoise.h"

PerlinNoise::PerlinNoise(int width, int height){
    this->generateGrid(QDateTime::currentMSecsSinceEpoch() / 1000, width, height);
}

PerlinNoise::PerlinNoise(unsigned int seed, int width, int height){
    this->generateGrid(seed, width, height);
}

double PerlinNoise::noise(double x, double y, double z){
    int x0 = ((x < 0) ? (int) x-1 : (int) x);
    int y0 = ((y < 0) ? (int) y-1 : (int) y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    double tx = x - (double)x0;
    double ty = y - (double)y0;
    double wx = tx*tx*(3-2*tx);
    double wy = ty*ty*(3-2*ty);

    double l0, l1, ix, iy, p;
    l0 = dotGrid(x0, y0, x, y);
    l1 = dotGrid(x1, y0, x, y);
    ix = cerp(l0, l1, wx);
    l0 = dotGrid(x0, y1, x, y);
    l1 = dotGrid(x1, y1, x, y);
    iy = cerp(l0, l1, wx);
    p = cerp(ix, iy, wy);

    return p;
}

double PerlinNoise::lerp(double a, double b, double w){
    return (1.0 - w)*a + w*b;
}

double PerlinNoise::cerp(double a, double b, double w)
{
    double ft = w * 3.1415927;
    double f = (1 - qCos(ft)) * 0.5;
    return  a*(1-f) + b*f;
}

double PerlinNoise::dotGrid(int i, int j, double x, double y){
    double dx = x - i;
    double dy = y - j;
    QPair<double, double> cur = this->grid[QPair<int, int>(i, j)];
    return (dx*cur.first + dy*cur.second);
}

void  PerlinNoise::generateGrid(quint32 seed, int width, int height){
    QRandomGenerator64 r(seed);
    this->grid = QHash<QPair<int, int>, QPair<double, double>>();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            double x = r.generateDouble() * 2 - 1;
            double y = r.generateDouble() * 2 - 1;
            double v = qSqrt((x*x) + (y*y));
            this->grid[QPair<int, int>(i, j)] = QPair<double, double>(x/v, y/v);
        }
    }
}
