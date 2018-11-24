#pragma once
#include "math.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

class Collider{
    private:
        int id;
        double cmx, cmy;
    public:
        double x = 0, y = 0; //change to private and write their get functions
        QImage colliding_map = QImage(64,64,QImage::Format_RGB32); //change to black
        Collider();
        Collider(double ix, double iy, QImage map, int iid);
        Collider(double ix, double iy, int iid);
        void set_map(QImage map);


        QPair<bool, QPair<double, double>> check_collision(Collider &other) //return type iscolliding , normal vector
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
                                cm_otherx ++; cm_othery++; nb_colliding_pixels++;
                            }
                        }
                    }
                }
            }
            cm_otherx = cm_otherx / nb_colliding_pixels;
            cm_othery = cm_othery / nb_colliding_pixels;
            return QPair<bool, QPair<double, double>> (colliding, QPair<double, double> (cmx-cm_otherx,cmy-cm_othery));
        }
        double getX(){return this->x;}
        double getY(){return this->y;}
};
