#include "Collider.h"

//Constructors
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
                this->cmx += i;
                this->cmy += j;
                countblack += 1;
            }
        }
    }
    this->cmx = cmx / countblack;
    this->cmy = cmy / countblack;
    this->skin_depth_pixels = this->skin_depth_percent*countblack;
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
                this->cmx += i;
                this->cmy += j;
                countblack += 1;
            }
        }
    }
    this->cmx = cmx / countblack;
    this->cmy = cmy / countblack;
    this->skin_depth_pixels = this->skin_depth_percent*countblack;
}

//get and set private variables

double Collider::getId() { return this->id;}
void Collider::setId(int iid) {this->id = iid;}

double Collider::getX() {return this->x;}
double Collider::getY() {return this->y;}

void Collider::setX(double x1) {this->x = x1;}
void Collider::setY(double y1) {this->y = y1;}


double Collider::getcmX() {return this->cmx;}
double Collider::getcmY() {return this->cmy;}

void Collider::setcmX(double cx) {this->cmx = cx;}
void Collider::setcmY(double cy) {this->cmy = cy;}


QImage Collider::get_map() {return this->colliding_map;}
void Collider::set_map(QImage map) {this->colliding_map = map;}


//Collision check method

QPair<bool, QPair<double, double> > Collider::check_collision(Collider &other)
{
    bool colliding = false;
    double cm_otherx = 0, cm_othery = 0;
    int nb_colliding_pixels = 0;

    for (int i = 0; i < this->colliding_map.width(); i++) {
        for (int j = 0; j < this->colliding_map.height(); j++){
            if (this->colliding_map.pixelColor(i,j) == Qt::black){
                if (other.x <= x+i <= other.x + other.colliding_map.width() && other.y <= y + j <= other.y + other.colliding_map.height()){
                    if (other.colliding_map.pixelColor(x+i-other.x, y+j - other.y) == Qt::black){
                        colliding = true;
                        cm_otherx += i; cm_othery += j; nb_colliding_pixels++;
                    }
                }
            }
        }
    }
    cm_otherx = cm_otherx / nb_colliding_pixels;
    cm_othery = cm_othery / nb_colliding_pixels;
    if(nb_colliding_pixels <= this->skin_depth_pixels){
        return QPair<bool, QPair<double, double>>(false, QPair<double, double>());
    }
    return QPair<bool, QPair<double, double>> (colliding, QPair<double, double> (cmx-cm_otherx,cmy-cm_othery));
}

