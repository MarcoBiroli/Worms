#pragma once
#include "math.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

/*The collider class which takes care of the collision of two or more rigid bodies*/

class Collider{
    private:
        int id; //Collider ID
        double skin_depth_percent = 0.1; //percentage of the body that is allowed to overlap with another collider
        int skin_depth_pixels = 0; //same thing as the skin_depth_percent but it is in pixels

    protected:
        double x = 0, y = 0; //default position of x and y
        double cmx, cmy; //Central of mass x and y
        QImage colliding_map = QImage(32,32,QImage::Format_RGB32); //default colliding map

    public:
        //Constructors

        Collider();
        Collider(double ix, double iy, QImage map, int iid);
        Collider(double ix, double iy, int iid);

        //get and set private variables

        double getId();
        void setId(int iid);

        double getX();
        double getY();

        void setX(double x1);
        void setY(double y1);

        double getcmX();
        double getcmY();

        void setcmX(double cx);
        void setcmY(double cy);

        QImage get_map();
        void set_map(QImage map);

        //check_collision method returns (bool is_colliding, Normal_Force); Normal_Force = (norm_x, norm_y)

        QPair<bool, QPair<double, double>> check_collision(Collider &other);

        //--------Destructor function do!!---------- Thomas?


};
