#include "RigidBody.h"
#include <iostream>
#include <cmath>


#me and camillo need to add comments here 



RigidBody::RigidBody(double imass, double ix, double iy, double vx0, double vy0, double ax0, double ay0, int iid, QPixmap map) : Collider(ix, iy, map, iid){
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

void addForce(QPair<double, double> F)
{
    currentForce.first += F.first;
    currentForce.second += F.second;
}





double RigidBody::distance(RigidBody other){
	xo=getx(other);
	yo=gety(other);
	distance= std::sqrt((x-xo)*(x-xo) + (y-yo) * (y-yo));
	return distance;
}


void RigidBody::simulate(double dt){

	dt /= 1000;
        ax = currentForce.first/mass;
        ay = currentForce.second/mass;
	vx=vx+ax*dt;
	vy=vy+ay*dt;
	x=x+vx*dt;
	y=y+vy*dt;

}


       
void RigidBody::setBounciness(double b){
	bounciness=b;
}

void Rigidody::setm(double m){
	mass=m;
}

void Rigidody::setx(double x0) {
	x=x0;
}

void Rigidody::sety(double y0) {
	y=y0;
}

void Rigidody::setvx(double vx0) {
	vx=vx0;
}

void Rigidody::setvy(double vy0) {
	vy=vy0;
}

void Rigidody::setay(double ay0){
	ay=ay0;
}

void Rigidody::setax(double ax0){
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

void RigidBody::addForce(QVector F){
	currentForce=currentForce+F;
}


