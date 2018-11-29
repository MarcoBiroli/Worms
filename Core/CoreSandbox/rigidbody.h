#pragma once
#include <QPair>
#include "Collider.h"
#include <QDebug>



class RigidBody:public Collider{
private:
    double mass = 0, vx = 0, vy = 0, ax = 0, ay = 0;
    QPair<double, double> currentForce = QPair<double, double>(0, 0);
    double bounciness_f = 0;
    bool stable = false;
    
public:
    RigidBody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, int iid, QImage map);
    RigidBody(double imass, double ix, double iy);
    
    void bounce(QPair<double, double> normal, double dt);

    void addForce(QPair<double, double> F);
    double distance(RigidBody other);
    void simulate(double dt);
    
    void setbounciness(double b);
    void setm(double m);
    void setvx(double v_x);
    void setvy(double v_y);
    void setax(double a_x);
    void setay(double a_y);
    void setstable(bool a);

    bool getstable();
    double getbounciness();
    double getm();
    double getvx();
    double getvy();
    double getax();
    double getay();
    
};
