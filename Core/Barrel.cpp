#include <iostream>
#include <string>
using namespace std;

#include "Barrel.h"

Barrel::Barrel() : RigidBody()
{

}

Barrel::Barrel(double m, double x, double y): RigidBody(m, x, y){
    this->mass = mass;
    this->x = x;
    this->y = y;
}

void Barrel::explode(PhysicsEngine &engine, QVector<Projectile*> &projectiles) {

    Projectile* current_projectile = new Projectile(false, 0.01, 1, 50, 60, 1, 2, this->x, this->y);

    engine.delete_rigidbody(this->getId());

    engine.add_RigidBody(current_projectile); //add projectile to projectile vector to be handle by physics engine
    projectiles.append(current_projectile);
}
