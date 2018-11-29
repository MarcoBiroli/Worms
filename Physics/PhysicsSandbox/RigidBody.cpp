#include "RigidBody.h"
#include <iostream>
#include <QtMath>





RigidBody::RigidBody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, int iid, QImage map) : Collider(ix, iy, map, iid){
    this->mass = imass;
    this->vx = vx0;
    this->vy = vy0;
    this->ax = ax0;
    this->ay = ay0;
}

RigidBody::RigidBody(double imass, double ix, double iy) : Collider(ix, iy, -1){
    this->mass = imass;
    this->vx = 0;
    this->vy = 0;
    this->ax = 0;
    this->ay = 0;
}

void RigidBody::bounce(QPair<double, double> normal)
{
    double k = 2.0*(this->vx* normal.first + this->vy*normal.second);
    this -> vx = (this->vx - k* normal.first)*this->bounciness_f*this->bounciness_f;
    this -> vy = (this->vy - k*normal.second)*this->bounciness_f*this->bounciness_f;
}

void RigidBody::bounce(QPair<double, double> normal, double dt){
    dt /= 1000;
    double scale_factory = -((this->vy * (bounciness_f + 1) * this->mass)/(dt) - this->currentForce.second)/normal.second;
    double scale_factorx = -((this->vx * (bounciness_f + 1) * this->mass)/(dt) - this->currentForce.first)/normal.first;
    double scale_factor = std::max({scale_factorx, scale_factory});
    this->addForce(QPair<double, double>(scale_factor*normal.first, scale_factor*normal.second));

    /*
     * (F_G + N) = m a => -v*bounciness = v + (F_G + N)/m * dt
     * => -v*(bounciness + 1) * m/dt - F_G = N
     */
}

void RigidBody::addForce(QPair<double, double> F)
{
    currentForce.first += F.first;
    currentForce.second += F.second;
}

double RigidBody::distance(RigidBody other){
    double xo=other.getX();
    double yo=other.getY();
    double distance= std::sqrt((this->cmx-xo)*(this->cmx-xo) + (this->cmy-yo) * (this->cmy-yo));
    return distance;
}

void RigidBody::simulate(double dt){

    if (this->stable){return;}
    dt /= 1000;
    this->addForce(QPair<double, double>(-0.005*this->vx*fabs(this->vx), -0.005*this->vy*fabs(this->vy)));
    ax = currentForce.first/mass;
    ay = currentForce.second/mass;
    vx=vx+ax*dt;
    vy=vy+ay*dt;
    if(this->is_grounded){
        vx *= 0.8;
    }
    this -> setX(this ->getX()+vx*dt);
    this -> setY(this ->getY() +vy*dt);
    currentForce.first = 0;
    currentForce.second = 0;
    //if (qFabs(vx) <= 0.1 && qFabs(vy) <= 0.1){ this->stable = true;}
    //decide how to handle the fact that the body must be stable on the ground when it has no velocity
    //problem: if I set that it is stable when the velocity is zero then it will stop on the top
    //while bouncing.
    // if I impose also that it has to have no forces applyed than problem on the ground: collision
    //is not seen as a force.
    //if (qFabs(vx) <= 0.1 && qFabs(vy) <= 0.1 && this->is_grounded){ this->stable = true;}
}





void RigidBody::setbounciness(double b){
    bounciness_f=b;
}

void RigidBody::setm(double m){
    mass=m;
}

void RigidBody::setvx(double v_x) {
    vx=v_x;
}

void RigidBody::setvy(double v_y) {
    vy=v_y;
}

void RigidBody::setay(double a_y){
    ay=a_y;
}

void RigidBody::setax(double a_x){
    ax=a_x;
}

void RigidBody::setstable(bool a){
    stable = a;

}


double RigidBody::getbounciness(){
    return bounciness_f;
}

bool RigidBody::getstable(){
    return stable;
}

double RigidBody::getm(){
    return mass;
}

double RigidBody::getvx(){
    return vx;
}

double RigidBody::getvy(){
    return vy;
}

double RigidBody::getax(){
    return ax;
}

double RigidBody::getay(){
    return ay;
}

