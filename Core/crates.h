#ifndef CRATES_H
#define CRATES_H

#endif // CRATES_H

#pragma once

#include <QVector>

#include "../Physics/RigidBody.h"
#include "Projectile.h"

class Projectile;

class Crate : public RigidBody {
    //Class for the health and ammo crates
    protected:
    int weaponID;
    int amountAmmo;
    public :
        virtual bool on_collision_do(Collider &other);
        Crate();
        Crate(double m, double x, double y, int weaponID, int amountAmmo, QPixmap isprite);
        //If type = 0, the crate is a health pack that restores health to the worm that pick it up
        //Else, the integer type corresponds to the integer of the weapon which ammos are in the crate

        void explode(PhysicsEngine &engine, QVector<Projectile*> &projectiles);
        //Call this function when the crate is caught in an explosion
        //The function does the following:
        //Remove the crate from the game
        //Generate a projectile with delay 0.01 at the position of the crate
        //The explosion of the crate is in fact the explosion of this new projectile

        void pickup(PhysicsEngine &engine);
        //Call this function when a worm collides with the crate
        //The function does the following:
        //Remove the crate from the game
        //Give health/ammos to the worm that picked it up
};
