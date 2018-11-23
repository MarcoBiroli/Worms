#include "RigidBody.h"
#include <iostream>
#include <cmath>

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

double distance(RigidBody other){
	xo=getx(other);
	yo=gety(other);
	distance= std::sqrt((x-xo)*(x-xo) + (y-yo) * (y-yo));
	return distance;
}


void RigidBody::simulate(double dt){

	ax=F.value(0)/m;
	ay=F.value(1)/m;
	vx=vx+ax*dt;
	vy=vy+ay*dt;
	x=x+vx*dt;
	y=y+vy*dt;

}
