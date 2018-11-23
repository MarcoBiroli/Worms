#pragma once
#include "math.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

class Collider{
    private:
        int id;
    public:
        double x = 0, y = 0; //change to private and write their get functions
        QImage colliding_map = QImage(64,64,QImage::Format_RGB32); //change to black
        Collider(double ix, double iy, QPixmap map, int iid);
        Collider(double ix, double iy, int iid);
        void set_map(QPixmap map);
        QPair<bool, QPair<double, double>> check_collision(Collider &other) //return type iscolliding , normal vector
        {
            QPair <double, double> normal = QPair <double, double> (0,0);
            bool colliding = false;
            for (int i = 0; i < this->colliding_map.width(); i++) {
                for (int j = 0; j < this->colliding_map.height(); j++){
                    if (this->colliding_map.pixelColor(i,j) == Qt::black){
                        if (other.x <= x+i <= other.x + other.colliding_map.width() && other.y <= y + j <= other.y + other.colliding_map.height()){
                            if (other.colliding_map.pixelColor(x+i-other.x, y+j - other.y) == Qt::black){
                                colliding = true;
                                normal += //calculate normal
                            }
                        }
                    }
                }
            }
        }
        double getX(){return this->x;}
        double getY(){return this->y;}
};
