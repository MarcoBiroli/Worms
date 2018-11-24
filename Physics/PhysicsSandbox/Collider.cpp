#include "Collider.h"

Collider::Collider()
{

}

Collider::Collider(double ix, double iy, QImage map, int iid)
{
    this->x = ix;
    this->y = iy;
    this->colliding_map = map;
    this->id = iid;
    this->cmx = 0;
    this ->cmy = 0;
    int countblack = 0;
    for (int i = 0; i< this->colliding_map.width(); i++){
        for (int j = 0; j< this-> colliding_map.height(); j++){
            if (this->colliding_map.pixelColor(i,j) == Qt::black) {
                this->cmx += 1;
                this->cmy += 1;
                countblack += 1;
            }
        }
    }
    this->cmx = cmx / countblack;
    this->cmy = cmy / countblack;
}

Collider::Collider(double ix, double iy, int iid)
{
    this->x = ix;
    this->y = iy;
    this->colliding_map.fill(QColor(0, 0, 0));
    this->id = iid;
    this->cmx = 0;
    this ->cmy = 0;
    int countblack = 0;
    for (int i = 0; i< this->colliding_map.width(); i++){
        for (int j = 0; j< this-> colliding_map.height(); j++){
            if (this->colliding_map.pixelColor(i,j) == Qt::black) {
                this->cmx += 1;
                this->cmy += 1;
                countblack += 1;
            }
        }
    }
    this->cmx = cmx / countblack;
    this->cmy = cmy / countblack;
}

void Collider::set_map(QImage map)
{
}

/*QPair<int, bool> Collider::check_collision(QMap<int, Collider> others)
{

}*/

