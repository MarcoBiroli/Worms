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
    this -> vy = -(this->vy - k*normal.second)*this->bounciness_f*this->bounciness_f;
}

void RigidBody::addForce(QPair<double, double> F)
{
    currentForce.first += F.first;
    currentForce.second += F.second;
}





double RigidBody::distance(RigidBody other){
    double xo=other.getX();
    double yo=other.getY();
    double distance= std::sqrt((this->x-xo)*(this->x-xo) + (this->y-yo) * (this->y-yo));
    return distance;
}


void RigidBody::simulate(double dt){

    if (this->stable){return;}
    dt /= 1000;
    ax = currentForce.first/mass;
    ay = currentForce.second/mass;
    vx=vx+ax*dt;
    vy=vy+ay*dt;
    x=x+vx*dt;
    y=y+vy*dt;
    currentForce.first = 0;
    currentForce.second = 0;
    //if (qFabs(vx) <= 0.1 && qFabs(vy) <= 0.1){ this->stable = true;}
    //decide how to handle the fact that the body must be stable on the ground when it has no velocity
    //problem: if I set that it is stable when the velocity is zero then it will stop on the top
    //while bouncing.
    // if I impose also that it has to have no forces applyed than problem on the ground: collision
    //is not seen as a force.
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

