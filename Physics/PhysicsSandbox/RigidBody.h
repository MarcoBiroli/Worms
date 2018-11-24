#pragma once
#include <QPair>
#include "Collider.h"
#include <QDebug>


//me and camillo need to add comments here

class RigidBody:public Collider{
private:
    QPair<double, double> currentForce = QPair<double, double>(0, 0);
    bool stable = false;
    
public:
    double bounciness_f = 0;
    double mass = 0, vx = 0, vy = 0, ax = 0, ay = 0;
    RigidBody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, int iid, QImage map);
    RigidBody(double imass, double ix, double iy);
    
    void bounce(QPair<double, double> normal);

    void addForce(QPair<double, double> F);
    double distance(RigidBody other);
    void simulate(double dt);
    
    /*void setbounciness();
    void setm();
    void setx();
    void sety();
    void setvx();
    void setvy();
    void setax();
    void setay();
    bool getstable();*/
    
};
