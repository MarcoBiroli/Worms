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
    this->should_explode = false;
}

void Barrel::explode(PhysicsEngine &engine, QVector<Projectile*> &projectiles,  QVector<Projectile*> &weapons) {
    Projectile* current_projectile = weapons[7]->clone();
    current_projectile->set_inital_position(this->x, this->y-25);

    engine.add_RigidBody(current_projectile); //add projectile to projectile vector to be handle by physics engine
    projectiles.append(current_projectile);

    this->sprite->hide();
}

void Barrel::setExplode(bool exp){
    should_explode = exp;
}

bool Barrel::getExplode(){
    return should_explode;
}
