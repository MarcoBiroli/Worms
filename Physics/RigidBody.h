#pragma once
#include <QPair>
#include "Collider.h"
#include <QDebug>



class RigidBody: public Collider{

protected:
    double mass = 0, vx = 0, vy = 0, ax = 0, ay = 0;
    double bckp_x = -1, bckp_y = 0, bckp_vx = 0, bckp_vy = 0, bckp_ax = 0, bckp_ay = 0;

private:
    QPair<double, double> currentForce = QPair<double, double>(0, 0);
    double bounciness_f = 0;
    bool stable = false;
    double static_coef = 0.5;
    
public:
    bool is_on_top_of_rigidbody = false;
    bool is_colliding = false;
    bool tangent_bouncing = false;
    QPair<bool, QPair<double, double>> is_grounded = QPair<bool, QPair<double, double>>(false, QPair<double, double>(0, 0));
    QGraphicsPixmapItem* sprite;

    //Constructors.
    RigidBody();
    RigidBody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, QImage map, QPixmap isprite);
    RigidBody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, QImage map);
    RigidBody(double imass, double ix, double iy);
    virtual ~RigidBody();
    
    //Physics methods.
    void bounce(QPair<double, double> normal, double dt);
    void addForce(QPair<double, double> F);
    double distance(RigidBody &other);
    void simulate(double dt);
    
    
    //Set methods.
    void setbounciness(double b);
    void setm(double m);
    void setvx(double v_x);
    void setvy(double v_y);
    void setax(double a_x);
    void setay(double a_y);
    void setstable(bool a);
    void setforce(QPair<double, double>forces);

    //Get methods.
    bool getstable() const;
    double getbounciness() const;
    double getm() const;
    double getvx() const;
    double getvy() const;
    double getax() const;
    double getay() const;
    QPair<double,double> getforce() const;
    
};
