#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Collider.h"

#include <QPair>
#include <QDebug>



class RigidBody:public Collider{
private:
    //Parameters of Rigid Body.
    double mass = 0, vx = 0, vy = 0, ax = 0, ay = 0;
    
    //total force applied, (Fx,Fy).
    QPair<double, double> currentForce = QPair<double, double>(0, 0);
    
    //parameter by which the velocity is reduced in a collision.
    double bounciness_f = 0; //0 means complete loss of linear momentum and 1 no loss of it.
    
    //by defalut the object is not stable.
    bool stable = false; 
    
public:
    //Constructors
    RigidBody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, int iid, QImage map);
    RigidBody(double imass, double ix, double iy);
    
    //Physics methods:
    
    void bounce(QPair<double, double> normal, double dt); //

    void addForce(QPair<double, double> F);
    double distance(RigidBody other);
    void simulate(double dt);
    
    //Set methods.
    void setbounciness(double b);
    void setm(double m);
    void setvx(double v_x);
    void setvy(double v_y);
    void setax(double a_x);
    void setay(double a_y);
    void setstable(bool a);
    
    //Get methods.
    bool getstable();
    double getbounciness();
    double getm();
    double getvx();
    double getvy();
    double getax();
    double getay();
    
};

#endif //RIGIDBODY_H
