#include <iostream>
#include <string>
using namespace std;

#include "crates.h"

Crate::Crate() : RigidBody()
{

}

Crate::Crate(double m, double x, double y, int weaponID, int amountAmmo, QPixmap isprite): RigidBody(m, x, y){
    this->mass = mass;
    this->x = x;
    this->y = y;
    this->weaponID = weaponID;
    this->sprite->setPixmap(isprite);
}

bool Crate::on_collision_do(Collider &other){
    if(other.isWorm()){
        other.addAmmo(weaponID, amountAmmo);
        return true;
    }
    return false;
}