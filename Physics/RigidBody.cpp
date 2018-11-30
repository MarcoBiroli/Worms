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

void RigidBody::bounce(QPair<double, double> normal, double dt)
{
    dt /= 1000;
    double theta = qAtan2(-normal.first, normal.second);
    double M[4] = {qCos(theta), qSin(theta), -qSin(theta), qCos(theta)};
    double ve = (M[0]*this->vx + M[1]*this->vy);
    double vu = (M[2]*this->vx + M[3]*this->vy);
    double n_ve = (M[0]*this->vx + M[1]*this->vy)*this->bounciness_f;
    double n_vu = -(M[2]*this->vx + M[3]*this->vy)*this->bounciness_f;
    double Fe = this->mass*(n_ve - ve)/dt;
    double Fu = this->mass*(n_vu - vu)/dt;
    double M2[4] = {qCos(theta), -qSin(theta), qSin(theta), qCos(theta)};
    double Fx = M2[0]*Fe + M2[1]*Fu;
    double Fy = M2[2]*Fe + M2[3]*Fu;
    this->addForce(QPair<double, double>(Fx, Fy));
    return;
}


void RigidBody::addForce(QPair<double, double> F) //(fx , fy)
{
    currentForce.first += F.first;
    currentForce.second += F.second;
}



double RigidBody::distance(RigidBody other){
    double xo=other.cmx;
    double yo=other.cmy;
    double distance= std::sqrt((this->cmx-xo)*(this->cmx-xo) + (this->cmy-yo) * (this->cmy-yo));
    return distance;
}


void RigidBody::simulate(double dt){

    if (this->stable){return;}
    dt /= 1000;
    ax = currentForce.first/mass;
    ay = currentForce.second/mass;
    vx=vx+ax*dt;
    vy=vy+ay*dt;
    this->x = this->x+vx*dt;
    this->y = this->y+vy*dt;
    if (qFabs(vx) <= 1 && qFabs(vy) <= 1 && qFabs(currentForce.first) <= 0.4 && qFabs(currentForce.second) <= 0.4){ this->stable = true;}
    currentForce.first = 0;
    currentForce.second = 0;
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

