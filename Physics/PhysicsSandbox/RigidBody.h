#pragma once
#include <QPair>
#include "Collider.h"
#include <QDebug>

class RigidBody:public Collider{
    private:
        double mass = 0, vx = 0, vy = 0, ax = 0, ay = 0;
        double bouciness_f = 0;
        QPair<double, double> currentForce = QPair<double, double>(0, 0);
        bool stable = false;
    
    public:
        RigidBody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, int iid, QPixmap map) : Collider(ix, iy, map, iid);
        RigidBody(double imass, double ix, double iy) : Collider(ix, iy, -1);

        void addForce(QPair<double, double> F);
        double distance(RigidBody other);
        void simulate(double dt)
            
        void setbounciness();
        void setm(); 
        void setx(); 
        void sety(); 
        void setvx(); 
        void setvy(); 
        void setax();
        void setay();
        bool getstable();
       
};
