#pragma once
#include "math.h"
#include "QPixmap"

class Collider{
    private:
        int id;
        double x = 0, y = 0;
        QPixmap colliding_map;
    public:
        Collider(double ix, double iy, QPixmap map, int iid);
        void set_map(QPixmap map);
        QPair<int, bool> check_collision(QMap<int, Collider> others);
};