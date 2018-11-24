#include "RigidBody.h"
#include <iostream>
#include <Qtmath>


//me and camillo need to add comments here



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
    this -> vx = -(this->vx - k* normal.first)*this->bounciness_f*this->bounciness_f;
    this -> vy = -(this->vy - k*normal.second)*this->bounciness_f*this->bounciness_f;
}

void RigidBody::addForce(QPair<double, double> F)
{
    currentForce.first += F.first;
    currentForce.second += F.second;
}





double RigidBody::distance(RigidBody other){
    //double xo=getx(other.x);
    //double yo=gety(other.y);
    //distance= std::sqrt((x-xo)*(x-xo) + (y-yo) * (y-yo));
    //return distance;
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
    
}



/*void RigidBody::setBounciness(double b){
    bounciness=b;
}

void RigidBody::setm(double m){
    mass=m;
}

void RigidBody::setx(double x0) {
    x=x0;
}

void RigidBody::sety(double y0) {
    y=y0;
}

void RigidBody::setvx(double vx0) {
    vx=vx0;
}

void RigidBody::setvy(double vy0) {
    vy=vy0;
}

void RigidBody::setay(double ay0){
    ay=ay0;
}

void RigidBody::setax(double ax0){
    ax=ax0;
}

void RigidBody::setstable(bool B){
    stable=B;
}

double RigidBody::getBounciness(){
    return bounciness;
}

bool RigidBody::getstable(){
    return stable;
}

double RigidBody::getm(){
    return m;
}

double RigidBody::getx(){
    return x;
}

double RigidBody::gety(){
    return y;
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
*/
