#pragma once
#ifndef CRATES_H
#define CRATES_H

#include <QVector>
#include <iostream>
#include <string>
using namespace std;

#include "../Physics/RigidBody.h"
#include "Projectile.h"

/*This class inherits Rigidbody. WHAT DOES IT DO??????*/

class Projectile;

class Crate : public RigidBody {
    protected:
        int weaponID;
        int amountAmmo; //<- WHY DO WE HAVE AMMO??
    public :
        //Constructors
        Crate();
        Crate(double m, double x, double y, int weaponID, int amountAmmo, QPixmap isprite);
        //If type = 0, the crate is a health pack that restores health to the worm that pick it up
        //Else, the integer type corresponds to the integer of the weapon which ammos are in the crate

        //Methods
        virtual bool on_collision_do(Collider &other);

        void explode(PhysicsEngine &engine, QVector<Projectile*> &projectiles); //<- DO YOU DO THIS IN THE END? NOT IN CPP
        //Call this function when the crate is caught in an explosion
        //The function does the following:
        //Remove the crate from the game
        //Generate a projectile with delay 0.01 at the position of the crate
        //The explosion of the crate is in fact the explosion of this new projectile
};

#endif // CRATES_H
