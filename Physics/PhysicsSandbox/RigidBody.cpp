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
    // v' = v + f/m * dt => F = (v' - v)/dt * m
    double Fe = this->mass*(n_ve - ve)/dt;
    double Fu = this->mass*(n_vu - vu)/dt;
    double M2[4] = {qCos(theta), -qSin(theta), qSin(theta), qCos(theta)};
    double Fx = M2[0]*Fe + M2[1]*Fu;
    double Fy = M2[2]*Fe + M2[3]*Fu;
    this->addForce(QPair<double, double>(Fx, Fy));
    return;
}


/*void RigidBody::bounce(QPair<double, double> normal, double dt)
{
    dt /= 1000;
    double n = qSqrt(qPow(normal.first, 2) + qPow(normal.second, 2));
    double Tx = normal.first / n;
    double Ty = normal.second / n;
    double phi = qAtan2(qFabs(Tx),qFabs(Ty));
    double theta = qAtan2(qFabs(this->vy), qFabs(this->vx));
    double vx2 = qSqrt(qPow(this->vx,2) + qPow(this->vy, 2)) * qCos(theta+ phi);
    double vy2 = qSqrt(qPow(this->vx,2) + qPow(this->vy, 2)) * qSin(theta+ phi);

    double v = qSqrt(qPow(this->vx, 2) + qPow(this->vy, 2));

    //double Fx = (2*v*qCos(M_PI/2 + phi)/dt)*bounciness_f;
    //double Fy = (2*v*qSin(M_PI/2 +phi)/dt)*bounciness_f;

    //double Fx = (2*qFabs(vx2)/dt * qCos(phi) - 2*qFabs(vy2)/dt * qSin(phi))*bounciness_f;
    //double Fy = (2*qFabs(vx2)/dt * qSin(phi) - 2*qFabs(vy2)/dt * qCos(phi))*bounciness_f;
    double Fe = vx2*(this->bounciness_f-1);
    double Fu = vy2*(this->bounciness_f+1);
    double Fx = ;
    double Fy = ;
    currentForce.first += Fx;
    currentForce.second += Fy;
    this->setX(this->getX() + normal.first/n);
    this->setY(this->getY() + normal.second/n);

}*/

void RigidBody::addForce(QPair<double, double> F) //(fx , fy)
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
    ax = currentForce.first/mass;
    ay = currentForce.second/mass;
    vx=vx+ax*dt;
    vy=vy+ay*dt;
    this->setX(this->getX()+vx*dt);
    this->setY(this->getY()+vy*dt);
    if (qFabs(vx) <= 5 && qFabs(vy) <= 5 && qFabs(currentForce.first) <= 1 && qFabs(currentForce.second) <= 1){ this->stable = true;}
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

