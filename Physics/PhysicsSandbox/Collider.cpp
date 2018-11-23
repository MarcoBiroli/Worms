#include "Collider.h"

Collider::Collider(double ix, double iy, QPixmap map, int iid)
{
    this->x = ix;
    this->y = iy;
    this->colliding_map = map;
    this->id = iid;
}

Collider::Collider(double ix, double iy, int iid)
{
    this->x = ix;
    this->y = iy;
    this->colliding_map.fill(QColor(0, 0, 0));
    this->id = iid;
}

void Collider::set_map(QPixmap map)
{
}

/*QPair<int, bool> Collider::check_collision(QMap<int, Collider> others)
{

}*/

