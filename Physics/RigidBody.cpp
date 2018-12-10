#include "RigidBody.h"
#include <iostream>
#include <QtMath>

#define update_time 10

//Constructors.
RigidBody::RigidBody()
{

}

RigidBody::RigidBody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, QImage map) : Collider(ix, iy, map){
    this->mass = imass;
    this->vx = vx0;
    this->vy = vy0;
    this->ax = ax0;
    this->ay = ay0;
}

RigidBody::RigidBody(double imass, double ix, double iy) : Collider(ix, iy){
    this->mass = imass;
    this->vx = 0;
    this->vy = 0;
    this->ax = 0;
    this->ay = 0;
}

//Physics methods.

//This method computes the impulsive force that makes the RigidBody bounce when a collision is detected.
//The physical idea is that the force acting on the body in a collision is F=dp/dt with dp the istantaneous 
//change in the linear momentum of the RigidBody.

void RigidBody::revert(){
    if(this->bckp_x == -1){return;}
    this->x = this->bckp_x;
    this->y = this->bckp_y;
    /*
    this->vx = this->bckp_vx;
    this->vy = this->bckp_vy;
    this->ax = this->bckp_ax;
    this->ay = this->bckp_ay;
    */
    this->bckp_x = -1;
}

void RigidBody::bounce(QPair<double, double> normal, double dt) 
    
{
    dt /= 1000; //dt in milliseconds
    //this->revert();
    double theta = qAtan2(-normal.first, normal.second); //angle that the normal vector to the ground forms with the y-aixs
    double M[4] = {qCos(theta), qSin(theta), -qSin(theta), qCos(theta)}; //rotational matrix of angle theta.
    double ve = (M[0]*this->vx + M[1]*this->vy); // component of the velocity parallel to the tangent line at the collision point.
    double vu = (M[2]*this->vx + M[3]*this->vy); // component of the velocity perpendicular to the tangent line at the collision point.

    double n_ve, n_vu;
    if(vu > 0){
        n_ve = ve;// reduction of v_e  by the bouncing factor
        n_vu = vu;
    }
    else{
        n_ve = ve*this->bounciness_f;// reduction of v_e  by the bouncing factor.
        n_vu = -vu*this->bounciness_f;// reduction of v_u by the bouncing factor.
    }
    double Fe = this->mass*(n_ve - ve)/dt;// component of the impulsive force parallel to the tangent at the collision point.
    double SFu = (M[2]*this->currentForce.first + M[3]*this->currentForce.second);
    double Fu;
    if(SFu <= 0){
        Fu = this->mass*(fabs(n_vu - vu))/dt - SFu;
    }
    else{
        Fu = this->mass*(fabs(n_vu - vu))/dt;
    }
    //Fe = 0;
    double M2[4] = {qCos(theta), -qSin(theta), qSin(theta), qCos(theta)};//rotational matrix of angle -theta.
    double Fx = M2[0]*Fe + M2[1]*Fu; //x component of the impulsive force.
    double Fy = M2[2]*Fe + M2[3]*Fu; //y component of the impulsive force.
    this->addForce(QPair<double, double>(Fx, Fy)); //adding this impulsive force to the current force acting on the RigidBody.
    //this->currentForce = QPair<double, double>(Fx, Fy);
    return;
}

//This method adds a new force to the current force acting on the RigidBody.

void RigidBody::addForce(QPair<double, double> F) //(fx , fy)
{
    currentForce.first += F.first;
    currentForce.second += F.second;
}


//this method computes the distance between the centers of masses of two RigidBodies.

double RigidBody::distance(RigidBody other){
    double xo=other.cmx;
    double yo=other.cmy;
    double distance= std::sqrt((this->cmx-xo)*(this->cmx-xo) + (this->cmy-yo) * (this->cmy-yo));
    return distance;
}


//this method uses simple kinematic laws to compute the new position, velocity, acceleration of the RigidBody after an interval dt.

void RigidBody::simulate(double dt){
    //if (this->stable){return;}
    dt /= 1000;
    double friction = 0.1;
    this->bckp_ax = ax;
    ax = currentForce.first/mass;
    if(this->is_grounded.first){
        ax -= vx*friction;
    }
    this->bckp_ay = ay;
    ay = currentForce.second/mass;
    if(this->is_grounded.first){
        ay -= vy*friction;
    }
    this->bckp_vx = vx;
    vx=vx+ax*dt;
    this->bckp_vy = vy;
    vy=vy+ay*dt;
    this->bckp_x = x;
    this->x = this->x+vx*dt;
    this->bckp_y = y;
    this->y = this->y+vy*dt;
    if (qFabs(vx) <= 1 && qFabs(vy) <= 1 && qFabs(currentForce.first) <= 0.4 && qFabs(currentForce.second) <= 0.4){ this->stable = true;}
        //the RigidBody is stable when both the velocity of the rigidBody and the froce acting on it are small enough.
    currentForce.first = 0;
    currentForce.second = 0;
}



//Set methods.
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


//Get methods.

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

