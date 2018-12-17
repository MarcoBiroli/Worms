#include <iostream>
#include <string>
using namespace std;

#include "Barrel.h"

Barrel::Barrel() : RigidBody()
{

}

Barrel::Barrel(double m, double x, double y, QPixmap isprite): RigidBody(m, x, y){
    this->mass = mass;
    this->x = x;
    this->y = y;
    this->sprite->setPixmap(isprite);
}

void Barrel::explode(PhysicsEngine &engine, QVector<Projectile*> &projectiles) {
    /*Projectile* current_projectile = new Projectile("Barrel", 100, 0, false, 0, 50, 10, 2, this->x, this->y, QPixmap::fromImage("://Images/barrel.png"));

    engine.delete_rigidbody(this->getId());

    engine.add_RigidBody(current_projectile); //add projectile to projectile vector to be handle by physics engine
    projectiles.append(current_projectile);*/
}
